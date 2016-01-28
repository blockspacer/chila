#!/usr/bin/python

import pygit2 
import collections
import sys

def hasParent(parents, oid):
    for p in parents:
        if p.id == oid:
            return True
            
    return False


def belongsToDirs(file, dirs):
    for dir in dirs:
        if file.startswith(dir):
            return True
            
    return False
    

CommitData = collections.namedtuple('CommitData', ['commit', 'files'])

def listCommits(commit, commonAncestorId, stopCommitId, dirs, files):
    commitsData = []
    parents = commit.parents
    
    while True:
        if parents == [] or commit.id == stopCommitId or (stopCommitId == None and hasParent(parents, commonAncestorId)):
            break

        parent = parents[0]
        parents.pop(0)
        
        if parent != commonAncestorId:
            diff = repo.diff(commit, parent.tree)
            
            newFiles = []
            for p in diff:
                if belongsToDirs(p.new_file_path, dirs) or files.count(p.new_file_path):
                    newFiles.append(p.new_file_path)
                    
            if newFiles != []:
                commitsData.insert(0, CommitData(commit, newFiles))
                    
            commit = parent
            parents += commit.parents
        
    return commitsData
    
def removeFileFromTree(index, file):
    try:
        index.remove(file)
    except IOError:
        pass
        
def createCommits(repo, commitsData, destHead, branchName):
    index = pygit2.Index()
    
    destCommit = destHead
    index.read_tree(destCommit.tree)
    
    for commitData in commitsData:
        srcCommit = commitData.commit
        tree = commitData.commit.tree
        for file in commitData.files:
            try:
                fileObject = tree[file]
                index.add(pygit2.IndexEntry(file, fileObject.id, pygit2.GIT_FILEMODE_BLOB))
            except KeyError:
                removeFileFromTree(index, file)
        
        destTree = index.write_tree(repo)
        
        diff = repo[destTree].diff_to_tree(destCommit.tree)
        
        if len(diff):
            destCommitId = repo.create_commit('refs/heads/' + branchName, srcCommit.author, srcCommit.committer, srcCommit.message, destTree, [destCommit.id])
            destCommit = repo[destCommitId]
            print srcCommit.id
            

#----------------------------------------------------------------------------------
repo = pygit2.Repository('.')

globals = { 'branch'       : None,
            'dirs'         : [], 
            'files'        : [], 
            'stopCommitId' : None }

if len(sys.argv) != 2:
    print 'usage: subProject.py <valuesFile.py> \n\n' \
          'where "valuesFile.py" should contain the following variables:\n' \
          '- branch: Destination branch.\n' \
          '- dirs: Directories to include.\n' \
          '- files: Files to include.\n' \
          '- stopCommitId: The stop commit. If none, a commit created by a merge-base will be taken.\n' 
    sys.exit()
          
execfile(sys.argv[1], globals)    

commit = repo.revparse_single('refs/heads/master')
destCommit = repo.revparse_single('refs/heads/' + globals['branch'])

lastMergeCommit = repo.merge_base(commit.id, destCommit.id)

commitsData = listCommits(commit, lastMergeCommit, globals['stopCommitId'], globals['dirs'], globals['files'])

for data in commitsData:
    print data.commit.id
    
print

createCommits(repo, commitsData, destCommit, globals['branch'])





