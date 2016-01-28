# Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
# (C.I.: 1.439.390 - Paraguay)

def parseEnv(env, text):
    ret = ""
    pEnv = False
    var = ""
    
    if text:
        for c in text:
            if pEnv:
                if c == '}':
                    pEnv = False
                    value = env[var]
                    if isinstance(value, basestring) and value != "":
                        ret += value
                    else:
                        ret += catList(value)
                else:
                    var += c
            else:
                if c == '{':
                    pEnv = True
                    var = ""
                else:
                    ret += c

    return ret
    
def printList(list):
    for elem in list:
        print elem

def catList(list):
    ret = ""
    for elem in list:
        ret += (("" if elem == "" else " ") + elem)
            
    return ret

def prefixList(list, prefix):
    ret = []
    for elem in list:
        ret.append(prefix + elem)
            
    return ret

def oneOf(value, listt):
    return listt.count(value) > 0
    
    
def loadOption(opt, name, type, default, help):
    opt.add_option("--" + name, 
                   dest = name.replace("-", "_"), 
                   type = type, 
                   default = default,
                   help = help)

def saveOption(cnf, name, allowNone = False):
    val = eval("cnf.options." + name.replace("-", "_"))
    if val != None:
        cnf.env[name.replace("-", ".")] = val
    elif not allowNone:
        cnf.fatal("error: option '" + name + "' missing")
        
