# Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
# (C.I.: 1.439.390 - Paraguay)

import targets
import util
import subprocess
import os
import shutil

class Global:
    def __init__(self, bld):
        self.bld = bld
        self.env = bld.env

    def setVariable(self, name, value, cond = True):
        parsed = util.parseEnv(self.env, value)
        if cond and parsed:
            self.env[name] = parsed
            
    def execCmd(self, cmd):
        return subprocess.check_output(cmd, shell = True)
        
    def archiveLib(self, path = None):
        return targets.ArchiveLib(self.bld, path if path else self.projectName())
        
    def executable(self, path = None):
        return targets.Linked(self.bld, path if path else self.projectName(), targets.Linked.Type.executable)
        
    def sharedLib(self, path = None):
        return targets.Linked(self.bld, path if path else self.projectName(), targets.Linked.Type.sharedLib)
        
    def projectName(self):
        return os.path.relpath(self.bld.path.abspath(), self.env.projectDir)
        
    def parseEnv(self, text):
        return util.parseEnv(self.env, text)
        
    def installHeaders(self, dirPath):
        try:
            shutil.rmtree(self.env["PREFIX"] + "/include")
        except OSError:
            pass
    
        for file in os.listdir(dirPath):   
            fullPath = dirPath + "/" + file
            if os.path.isdir(fullPath):
                self.installHeaders(fullPath)
            else:
                ext = os.path.splitext(fullPath)[1]    
                if ext == ".h" or ext == ".hpp":
                    self.bld.install_files("${PREFIX}/include/" + os.path.relpath(dirPath, self.env.sourceDir), 
                                           os.path.relpath(fullPath, self.bld.path.abspath()))

    def getFilesRecursive(self, dirPath, relPath = None):
        files = []   
        for file in os.listdir(dirPath):   
            fullPath = dirPath + "/" + file
            if os.path.isdir(fullPath):
                files += self.getFilesRecursive(fullPath, relPath)
            else:
                files.append(os.path.relpath(fullPath, relPath) if relPath else fullPath)

        return files

            
