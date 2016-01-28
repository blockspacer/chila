# Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
# (C.I.: 1.439.390 - Paraguay)

import os
import glob
import wafmod.util
import wafmod.gbl
import types
import ast
import importlib
from pkgutil import walk_packages
from waflib.Configure import conf
from waflib.Build import BuildContext, CleanContext, InstallContext, UninstallContext


@conf
def getEnv(ctx, name):
    value = ctx.env[name]
    if value:
        return value
    else:
        return ""

def recurseAll(ctx,  path):
    for d in os.listdir(path):
        fullPath = path + "/" + d
        if os.path.isdir(fullPath):
            file = fullPath + "/wscript"
            if os.path.isfile(file):
                ctx.recurse(fullPath)

            recurseAll(ctx, fullPath)

class ImportFinder(ast.NodeVisitor):
    def __init__(self):
        self.imports = set()

    def visit_Import(self, node):
        for i in node.names:
            module = importlib.import_module(i.name)
            try:           
                file = module.__file__
                if not file.endswith('pyc'):
                    self.imports.add(file)
            except:
                pass

    def visit_ImportFrom(self, node):
        raise "Not supported" 

def findPyDeps(path):
    try:
        tree = ast.parse(open(path).read())
    except:
        print "Error parsing: " + path
        raise

    finder = ImportFinder()
    finder.visit(tree)
    imports = finder.imports
    for imp in finder.imports:
        imports = imports | findPyDeps(imp)

    return imports

def addFGens(bld,  path):
    for d in os.listdir(path):
        fullPath = path + "/" + d
        if os.path.isdir(fullPath):
            for file in glob.glob(fullPath + "/*.fgen.py"):
                fileIn = os.path.relpath(file, bld.path.abspath())
                fileOut = fileIn.rsplit('.', 1)[0] + ".hpp"

                bld(rule   = "env PYTHONDONTWRITEBYTECODE=1 python ${SRC} > ${TGT}",
                    source = fileIn,
                    target = fileOut,
                    update_outputs = True)
                
                deps = findPyDeps(fileIn)

                for dep in deps:
                    bld.add_manual_dependency(
                        bld.path.find_node(fileIn),
                        bld.path.find_node(os.path.relpath(dep, bld.path.abspath())))

            addFGens(bld, fullPath)


for x in ['debug', 'release']:
    for y in (BuildContext, CleanContext, InstallContext, UninstallContext):
        name = y.__name__.replace('Context','').lower()
        class tmp(y):
            cmd = name + '_' + x
            variant = x

class InstallHeaders(InstallContext):
    cmd = 'install_headers'

# ------------------------------------------------------------------------------------------------------

def setVariables(glob):
    env = glob.env

    glob.setVariable(name  = "comp_args.c",
                     value = "{CFLAGS}")

    glob.setVariable(name  = "comp_args.cxx",
                     value = "{CXXFLAGS} -std=c++11 -Wno-deprecated-register")

    glob.setVariable(name  = "global.comp_args",
                     value = "-g -DBOOST_PP_VARIADICS=1 -fPIC {max_errors_flag} -Wreturn-type -Wno-mismatched-tags",
                     cond  = glob.bld.variant == 'debug')

    glob.setVariable(name  = "global.comp_args",
                     value = "-O3 -DBOOST_PP_VARIADICS=1 -fPIC {max_errors_flag} -DNDEBUG -Wreturn-type",
                     cond  = glob.bld.variant == 'release')

    glob.setVariable(name  = "target.comp_args",
                     value = "{global.comp_args}",
                     cond  = glob.bld.variant == 'debug')

    glob.setVariable(name  = "target.comp_args",
                     value = "{global.comp_args}",
                     cond  = glob.bld.variant == 'release')

    glob.setVariable(name  = "target.link_args",
                     value = "{LDFLAGS} -fPIC")

# pkg-config -------------------------------------------------------------------------------------------
class PkgConfigLib:
    def __init__(self, name, alVersion, mandatory):
        self.name = name
        self.alVersion = alVersion
        self.mandatory = mandatory

    def check(self, ctx):
        ctx.check_cfg(package=self.name,
                      args=['--cflags', '--libs'],
                      uselib_store=self.name.upper(),
                      atleast_version=self.alVersion,
                      msg="Checking for '" + self.name + "'",
                      mandatory=self.mandatory)

class PkgConfigLibs:
    libs = []

    def add(self, name, alVersion, mandatory):
        self.libs.append(PkgConfigLib(name, alVersion, mandatory))

    def check(self, ctx):
        for lib in self.libs:
            lib.check(ctx);

libs = PkgConfigLibs()

libs.add('libxml++-2.6',   '2.30', True)
libs.add('gtkmm-2.4',      '2.18', True)
libs.add('gtkmm-3.0',      '3.10', False)

libs.add('Qt5Widgets',     '5.5',  False)
libs.add('Qt5Quick',       '5.5',  False)
libs.add('Qt5Gui',         '5.5',  False)
libs.add('Qt5Qml',         '5.5',  False)

# ------------------------------------------------------------------------------------------------------
def options(opt):
    opt.load('compiler_c')
    opt.load('compiler_cxx')

    wafmod.util.loadOption(opt, "boost-include",        "string",  None, "the include path for the boost libraries")
    wafmod.util.loadOption(opt, "boost-lib",            "string",  None, "the library path for the boost libraries")
    wafmod.util.loadOption(opt, "tut-include",          "string",  None, "the include path for the TUT unit-testing library")
    wafmod.util.loadOption(opt, "errors-max",           "int",     None, "maximum number of compilation errors")
    wafmod.util.loadOption(opt, "qt5-home",             "string",  None, "maximum number of compilation errors")
    

def configure(ctx):
    ctx.load('compiler_c')
    ctx.load('compiler_cxx')

    ctx.check_cfg(atleast_pkgconfig_version='0.0.0')

    libs.check(ctx)

    ctx.env.sourceDir = os.path.abspath(ctx.path.abspath() + "/../../src")

    wafmod.util.saveOption(ctx, "boost-include")
    wafmod.util.saveOption(ctx, "boost-lib")
    wafmod.util.saveOption(ctx, "tut-include")
    wafmod.util.saveOption(ctx, "errors-max", True)
    wafmod.util.saveOption(ctx, "qt5-home", True)

def build(bld):
    env = bld.env
    glob = wafmod.gbl.Global(bld)

    if bld.cmd == "install_headers":
        glob.installHeaders(env.sourceDir)
        return

    if not bld.variant:
        bld.fatal('call "waf [build/install/clean]_[debug/release]", and try "waf --help"')


    env.targetProjectPaths = os.environ.get("PROJECTS", None)

    bld.env.projectDir = bld.path.abspath()

    bld.GLOBAL = glob

    glob.setVariable(name  = "max_errors_flag",
                     value = "-fmax-errors=" + `env["errors.max"]`,
                     cond  = glob.bld.getEnv("CXX") == "g++" and env["errors.max"] != [])

    glob.setVariable(name  = "max_errors_flag",
                     value = "-ferror-limit=" + `env["errors.max"]`,
                     cond  = glob.bld.getEnv("CXX") == "clang++" and env["errors.max"] != [])

    qt5Home = env["qt5.home"]
    if glob.bld.getEnv("CXX") == "clang++":
        qt5Variant = "linux-clang"
    else:
        qt5Variant = "linux-gcc"

    if qt5Home != []:
        glob.setVariable(name  = "qt5.include",
                         value = "-I " + qt5Home + "/gcc_64/mkspecs/" + qt5Variant + " "\
                                 "-I " + qt5Home + "/gcc_64/include")

        glob.setVariable(name  = "qt5.lib",
                         value = "-L " + qt5Home + "/gcc_64/lib " + \
                                 "-L " + qt5Home + "/gcc_64 " + \
                                 "-lGL " + \
                                 "-Wl,-rpath," + qt5Home + "/gcc_64/lib " + \
                                 "-Wl,-rpath," + qt5Home + "/gcc_64")
    
    setVariables(glob)
    if env.targetProjectPaths:
        for path in env.targetProjectPaths.split():
            bld.recurse(path)

    addFGens(bld, env.sourceDir)

