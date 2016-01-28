# Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
# (C.I.: 1.439.390 - Paraguay)

import generators
import util

class GeneratorHolder:
    def __init__(self):
        self.generators = []

    def addGenerator(self, generator):
        if not isinstance(generator, generators.Generator):
            raise Exception
    
        self.generators.append(generator)
        
        return generator

class ArchiveLibsHolder:
    def __init__(self):
        self.archiveLibs = []
        
    def archiveLib(self, path, cond = True):
        if cond:
            parsed = util.parseEnv(self.env, path)
            if parsed:
                self.archiveLibs.append(parsed)

    def getArchiveLibs(self): 
        return archiveLibs

class CompArgsHolder:
    def __init__(self):
        self.compArgsC = []
        self.compArgsCPP = []
        self.includePaths = []
        
    def compilationArgC(self, arg, cond = True):
        if cond:
            parsed = util.parseEnv(self.env, arg)
            if parsed:
                self.compArgsC += parsed.split()

    def compilationArgCPP(self, arg, cond = True):
        if cond:
            parsed = util.parseEnv(self.env, arg)
            if parsed:
                self.compArgsCPP += parsed.split()
        
    def compilationArg(self, arg, cond = True):
        if cond:
            self.compilationArgC(arg)
            self.compilationArgCPP(arg)        

    def includePath(self, path, cond = True):
        if cond:
            parsed = util.parseEnv(self.env, path)
            if parsed:
                self.includePaths.append(parsed)

class LibHolder:
    def __init__(self):
        self.libPaths = []
        self.libs = []
    
    def libPath(self, path, cond = True):
        if cond:
            parsed = util.parseEnv(self.env, path)
            if parsed:
                self.libPaths.append(parsed)

    def lib(self, path, cond = True):
        if cond:
            parsed = util.parseEnv(self.env, path)
            if parsed:
                self.libs.append(parsed)
        
class TargetArgsHolder:
    def __init__(self):
        self.targetArgs = []
    
    def targetArg(self, arg, cond = True):
        if cond:
            parsed = util.parseEnv(self.env, arg)
            if parsed:
                self.targetArgs += parsed.split()
            
