#!/usr/bin/python

import pygit2 
import collections
import sys
import os.path
import getopt
import re

def getHeader(path, prefSuf):
    for prefSuf in prefSuf:
        prefix = prefSuf[0]
        suffixes = prefSuf[1]
        if path.startswith(prefix):
            startLen = len(prefix) + 1
            endLen = len(path)
            for suffix in suffixes:
                if path.endswith(suffix):
                    endLen = endLen - len(suffix) - 1

            return path[startLen:endLen].replace('/', '.')

    return None

class AppError(Exception):
    def __init__(self, value):
        self.value = value
    def __str__(self):
        return repr(self.value)

def getProjectList(repo, prefSuf, projectsExclude):
    diff = repo.diff(flags = pygit2.GIT_DIFF_INCLUDE_UNTRACKED)

    fileDataMap = dict()

    for patch in diff:
        filePath = patch.new_file_path
        header = getHeader(os.path.dirname(filePath), prefSuf)

        if header is None:
            raise Exception(filePath + ' does not contain a valid prefix')

        include = True
        for pEx in projectsExclude:
            if header.startswith(pEx):
                include = False
                break

        if include:
            try:
                fileDataMap[header].append(filePath)
            except KeyError:
                fileDataMap[header] = [filePath]
            
    return fileDataMap

#--------------------------------------------------------------------

try:
    globals = { 'projectsExclude' : [] }

    if len(sys.argv) != 2:
        print 'usage: gitCommentCreator.py <valuesFile.py> \n\n' \
              'where "valuesFile.py" should contain the following variables:\n' \
              '- projectsExclude: List of projects to exclude.\n' \
              '- simulate: Whether this is just a simulation or not.\n\n' \
              'the projects are in the form of "name.name.name..."'
        sys.exit()

    execfile(sys.argv[1], globals)    

    projectsExclude = globals['projectsExclude']
    prefSuf = globals['prefSuf']
    simulate = globals['simulate']

    repo = pygit2.Repository('.')
    
    head = repo.revparse_single('HEAD')
    headId = head.id

    repo.reset(head.id, pygit2.GIT_RESET_MIXED)
    
    autor = pygit2.Signature(repo.config['user.name'], repo.config['user.email'])
    committer = autor
    
    index = repo.index
    index.read()
    
    fileDataMap = getProjectList(repo, prefSuf, projectsExclude)
    
    for prj, files in fileDataMap.iteritems():
        print prj + ":"
        for file in files:
            print "- " + file 

            if not simulate:
                if os.path.exists(file):
                    index.add(file)
                else:
                    index.remove(file)
            
        if not simulate:
            index.write()
            tree = index.write_tree()
            headId = repo.create_commit('refs/heads/master', autor, committer, prj, tree, [headId])
            
        print

    if len(projectsExclude):
        print 'Excluded projects:'

    for pEx in projectsExclude:
        print '- ' + pEx

except AppError as ex:
    sys.exit("error: " + ex.value + '\n')
   
    
