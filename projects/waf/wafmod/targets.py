# Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
# (C.I.: 1.439.390 - Paraguay)

import glob
import os
import holders
import util
import sys

class CompilationBase(holders.CompArgsHolder, holders.TargetArgsHolder, holders.GeneratorHolder):
    def __init__(self, bld, path):
        holders.CompArgsHolder.__init__(self)
        holders.TargetArgsHolder.__init__(self)
        holders.GeneratorHolder.__init__(self)
        self.bld = bld
        self.env = bld.env
        self.path = path 
        self.name = path.replace("/", ".")
        self.objectsStr = self.name + "_objects";    
        self.srcDir = self.env.sourceDir + "/" + self.path
        
        self.variantDir = self.env["variant_dir"]

    def pkgConfigVarsCFlags(self, name):
        return self.env["CFLAGS_" + name.upper()]

    def pkgConfigVarsCXXFlags(self, name):
        return self.env["CXXFLAGS_" + name.upper()]

    def pkgConfigVarsIncludes(self, name):
        return self.env["INCLUDES_" + name.upper()]

    def pkgConfigVarsFlags(self, name):
        return self.pkgConfigVarsCFlags(name) + \
               self.pkgConfigVarsCXXFlags(name) + \
               util.prefixList(self.pkgConfigVarsIncludes(name), "-I ")
        
    def pkgConfigVars(self, name):
        self.compArgsC += self.pkgConfigVarsCFlags(name)
        self.compArgsCPP += self.pkgConfigVarsCXXFlags(name)
        self.includePaths += self.pkgConfigVarsIncludes(name)

    def installFile(self, file):
        self.bld.install_as("${PREFIX}/share/" + self.path + '/' + file, 
                               os.path.relpath(self.srcDir + '/' + file, self.bld.path.abspath()))
        
    def getCFlags(self):
        return self.compArgsC + self.bld.getEnv("comp_args.c").split()

    def getCXXFlags(self):
        return self.compArgsCPP + self.compArgsCPP + self.bld.getEnv("comp_args.cxx").split();

    def createCompObjects(self):
        includes = [os.path.relpath(self.env.sourceDir, self.bld.path.abspath())]
        cFlags = self.getCFlags();
        cxxFlags = self.getCXXFlags();
        patterns = ["*.c", "*.cpp", "*.cc"]
        
        dirs = [self.srcDir]
        self.getDirs(dirs, self.srcDir)
        
        for include in self.includePaths:
            includes.append(os.path.relpath(include, self.bld.path.abspath()))
            
        files = ""
        for sDir in dirs:   
            for pattern in patterns:
                for file in glob.glob(sDir + "/" + pattern):
                    files += os.path.relpath(file, self.bld.path.abspath()) + " "

        self.bld.objects(source = files,
                         target = self.objectsStr,
                         cflags = cFlags,
                         cxxflags = cxxFlags,
                         includes = includes)


    def getDirsRec(self, dirs, path):
        for d in os.listdir(path):   
            fullPath = path + "/" + d
            if os.path.isdir(fullPath) and d != "tests":
                dirs.append(fullPath)
                self.getDirsRec(dirs, fullPath)
            
    def getDirs(self, dirs, path):
        self.getDirsRec(dirs, path)
        return dirs
                
    def generate(self):
        self.createCompObjects()
        
        for generator in self.generators:
            generator.generate(self.bld, self.env.sourceDir, self.path)
        
class ArchiveLib(CompilationBase):
    def __init__(self, bld, path):
        CompilationBase.__init__(self, bld, path)
        
    def generate(self):
        CompilationBase.generate(self)

        self.bld(features = "c cxx cxxstlib", 
                 use = self.objectsStr, 
                 target = self.name,
                 install_path = "${PREFIX}/lib/" + self.bld.variant) 

class Linked(CompilationBase, holders.ArchiveLibsHolder, holders.LibHolder, holders.TargetArgsHolder):
    class Type:
        executable = 0
        sharedLib = 1

    def __init__(self, bld, path, type):
        CompilationBase.__init__(self, bld, path)
        holders.ArchiveLibsHolder.__init__(self)
        holders.LibHolder.__init__(self)
        holders.TargetArgsHolder.__init__(self)
        self.type = type
        
    def pkgConfigVars(self, name):
        CompilationBase.pkgConfigVars(self, name)
        self.libPaths +=  self.env["LIBPATH_" + name.upper()]
        self.libs += self.env["LIB_" + name.upper()]
        self.targetArgs += self.env["LINKFLAGS_" + name.upper()]        
        
    def generate(self):
        CompilationBase.generate(self)
        
        if self.type == self.Type.executable:
            f = "cxxprogram"
            ex = ".bin"
            instDir = "bin"
        elif self.type == self.Type.sharedLib:
            f = "cshlib"
            ex = ""
            instDir = "lib"
        else:
            raise Exception
            
        use = [self.objectsStr]
        for libPath in self.archiveLibs:
            self.bld.recurse(self.env.projectDir + "/" + libPath)
            use.append(libPath.replace("/", "."))
            
        targetName = self.name + ex
        
        self.bld(features       = "c cxx " + f, 
                 use            = use, 
                 libpath        = self.libPaths,
                 lib            = self.libs,
                 name           = self.name,
                 linkflags      = self.targetArgs + ['-fPIC'],
                 target         = targetName,
                 install_path   = "${PREFIX}/" + instDir + "/" + self.bld.variant)   
            
        

                                   
       
       
