def beginModule():
    str = \
    '''
    module(L)
    [
    '''
    return str

def endModule():
    str = \
    '''
    ];
    '''
    return str

def defClass(name):
    str = '\tclass_<' + name + '>("' + name + '")\n'
    return str

def defConstructor(params):
    str = '\t\t.def(constructor<'
    i = 0
    l = len(params)
    while i < l:
        str += params[i]
        if i < l - 1:
            str += ', '
        i += 1
    str += '>())\n'
    return str

def defMemberFunc(className, funcName, retType, params):
    #print className
    #print funcName
    #print retType
    #print params
    str = '\t\t.def('
    str += '"' + funcName + '", '
    str += '(' + retType + '(' + className + '::*)' + '('
    i = 0
    l = len(params)
    while i < l:
        str += params[i]
        if i < l - 1:
            str += ', '
        i += 1
    str += '))'
    str += '&' + className + '::' + funcName
    str += ')\n'
    return str
