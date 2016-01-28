# Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
# (C.I.: 1.439.390 - Paraguay)

import os
import util
import subprocess

class Generator:
    def generate(self, sourceDir, path):
        raise Exception

class QMLRccGenerator(Generator):
    def __init__(self, rccPath, name, srcFile, destFile):
        self.name = name
        self.rccPath = rccPath
        self.srcFile = srcFile
        self.destFile = destFile
    
    def generate(self, bld, sourceDir, path):
        sDir = sourceDir + "/" + path

        fIn = sDir + "/" + self.srcFile
        bldPathAbs = bld.path.abspath()

        fileIn  = os.path.relpath(fIn, bldPathAbs)
        fileOut = os.path.relpath(sDir + "/" + self.destFile, bldPathAbs)

        filePath = "rcc " if self.rccPath == '' else self.rccPath 

        filesIn = [fileIn]
        for file in subprocess.check_output([filePath, "--list", fIn]).split('\n'):
            if (file != ''):
                filesIn.append(os.path.relpath(file, bldPathAbs))

        bld(rule = filePath + " -name " + self.name + " ${SRC[0].abspath()} -o ${TGT[0].abspath()}" , 
            source = filesIn, 
            target = fileOut,
            update_outputs = True)

class QMLMocGenerator(Generator):
    def __init__(self, mocPath, srcFile, destFile, flags):
        self.mocPath = mocPath
        self.srcFile = srcFile
        self.destFile = destFile
        self.flags = flags
    
    def generate(self, bld, sourceDir, path):
        sDir = sourceDir + "/" + path

        fIn = sDir + "/" + self.srcFile
        bldPathAbs = bld.path.abspath()

        fileIn  = os.path.relpath(fIn, bldPathAbs)
        fileOut = os.path.relpath(sDir + "/" + self.destFile, bldPathAbs)

        filePath = "moc " if self.mocPath == '' else self.mocPath 

        bld(rule = filePath + util.catList(self.flags) + " -i ${SRC[0].abspath()} -o ${TGT[0].abspath()}" , 
            source = fileIn, 
            target = fileOut,
            update_outputs = True)

class ConnectionToolsGenerator(Generator):
    class PathPair:
        def __init__(self, path, isRef):
            self.path = path
            self.isRef = isRef

    def __init__(self, srcDir, destDir):
        self.srcDir = srcDir
        self.destDir = destDir
        self.connectors = []
        self.cpGens = []
        
    def addConnector(self, path, isRef = False):
        self.connectors.append(self.PathPair(path, isRef))

    def addCPerformer(self, path, isRef = False):
        self.cpGens.append(self.PathPair(path, isRef))

    def getFileOut(self, file):
        return self.destDir + "/" +os.path.splitext(file)[0] + ".hpp"

    def getOutConnFiles(self):
        ret = []
        for conn in self.connectors:
            if not conn.isRef:
                ret.append(self.getFileOut(conn.path))

        return ret

    def getOutCPFiles(self):
        ret = []
        for conn in self.cpGens:
            if not conn.isRef:
                ret.append(self.getFileOut(conn.path))

        return ret

        
    def generate(self, bld, sourceDir, path):
        cpInFiles = []
        cpOutFiles = []
        connFiles = []
        
        cpGenText = "cPerformerGenerator "
        
        srcIndex = 0
        sDir = sourceDir + "/" + path

        for conn in self.connectors:
            fileIn  = os.path.relpath(sDir + "/" + self.srcDir + "/" + conn.path,   bld.path.abspath())
            fileOut = os.path.relpath(sDir + "/" + self.getFileOut(conn.path),      bld.path.abspath())
            
            connFiles.append(fileIn)
            
            cpGenText += " -c ${SRC[" + `srcIndex` + "].abspath()}" 
            srcIndex = srcIndex + 1;
            
            if not conn.isRef:
                bld(rule   = "connectorGenerator -i ${SRC} -o ${TGT}", 
                    source = fileIn, 
                    target = fileOut,
                    update_outputs = True)
        
        if len(self.cpGens):
            tgtIndex = 0
            for cpGen in self.cpGens:
                fileIn  = os.path.relpath(sDir + "/" + self.srcDir + "/" + cpGen.path,  bld.path.abspath())
                fileOut = os.path.relpath(sDir + "/" + self.getFileOut(cpGen.path),     bld.path.abspath())
            
                cpInFiles.append(fileIn)
                cpOutFiles.append(fileOut)
                
                cpGenText += " -p ${SRC[" + `srcIndex` + "].abspath()},${TGT[" + `tgtIndex` + "].abspath()}"
                srcIndex = srcIndex + 1;
                tgtIndex = tgtIndex + 1;

            bld(rule   = cpGenText, 
                source = connFiles + cpInFiles, 
                target = cpOutFiles,
                update_outputs = True)

class ModifyFilesGenerator(Generator):
    def __init__(self, command, files):
        self.files = files
        self.command = command

    def generate(self, bld, sourceDir, path):
        sDir = sourceDir + "/" + path

        for filePair in self.files:
            fileIn  = os.path.relpath(sDir + "/" + filePair[0], bld.path.abspath())
            fileOut  = os.path.relpath(sDir + "/" + filePair[1], bld.path.abspath())

            bld(rule   = self.command + "${SRC[0].abspath()} ${TGT[0].abspath()}",
                source = fileIn,
                target = fileOut,
                update_outputs = True)
            
        
