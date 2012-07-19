import re
from generate import*

ignore = ['inline', 'explicit']
types = ['const',
         'void', 'bool', 'double', 'float', 'char', 'short', 'int', 'long',
         'Real', 'uchar', 'ushort', 'uint', 'ulong',
         'size_t',
         'Angle',
        'Animation',
        'AnimationState',
        'AnimationStateSet',
        'AnimationTrack',
        'Archive',
        'ArchiveFactory',
        'ArchiveManager',
        'AutoParamDataSource',
        'AxisAlignedBox',
        'AxisAlignedBoxSceneQuery',
        'Billboard',
        'BillboardChain',
        'BillboardSet',
        'Bone',
        'Camera',
        'Codec',
        'ColourValue',
        'ConfigDialog',
        'Controller',
        'ControllerFunction',
        'ControllerManager',
        'ControllerValue',
        'DefaultWorkQueue',
        'Degree',
        'DynLib',
        'DynLibManager',
        'EdgeData',
        'EdgeListBuilder',
        'Entity',
        'ErrorDialog',
        'ExternalTextureSourceManager',
        'Factory',
        'Font',
        'FontPtr',
        'FontManager',
        'FrameListener',
        'Frustum',
        'GpuProgram',
        'GpuProgramPtr',
        'GpuProgramManager',
        'GpuProgramUsage',
        'HardwareIndexBuffer',
        'HardwareOcclusionQuery',
        'HardwareVertexBuffer',
        'HardwarePixelBuffer',
        'HardwarePixelBufferSharedPtr',
        'HighLevelGpuProgram',
        'HighLevelGpuProgramPtr',
        'HighLevelGpuProgramManager',
        'HighLevelGpuProgramFactory',
        'IndexData',
        'IntersectionSceneQuery',
        'IntersectionSceneQueryListener',
        'Image',
        'KeyFrame',
        'Light',
        'Log',
        'LogManager',
        'ManualResourceLoader',
        'ManualObject',
        'Material',
        'MaterialPtr',
        'MaterialManager',
        'Math',
        'Matrix3',
        'Matrix4',
        'MemoryManager',
        'Mesh',
        'MeshPtr',
        'MeshSerializer',
        'MeshSerializerImpl',
        'MeshManager',
        'MovableObject',
        'MovablePlane',
        'Node',
        'NodeAnimationTrack',
        'NodeKeyFrame',
        'NumericAnimationTrack',
        'NumericKeyFrame',
        'Overlay',
        'OverlayContainer',
        'OverlayElement',
        'OverlayElementFactory',
        'OverlayManager',
        'Particle',
        'ParticleAffector',
        'ParticleAffectorFactory',
        'ParticleEmitter',
        'ParticleEmitterFactory',
        'ParticleSystem',
        'ParticleSystemManager',
        'ParticleSystemRenderer',
        'ParticleSystemRendererFactory',
        'ParticleVisualData',
        'Pass',
        'PatchMesh',
        'PixelBox',
        'Plane',
        'PlaneBoundedVolume',
        'Plugin',
        'Pose',
        'ProgressiveMesh',
        'Profile',
        'Profiler',
        'Quaternion',
        'Radian',
        'Ray',
        'RaySceneQuery',
        'RaySceneQueryListener',
        'Renderable',
        'RenderPriorityGroup',
        'RenderQueue',
        'RenderQueueGroup',
        'RenderQueueInvocation',
        'RenderQueueInvocationSequence',
        'RenderQueueListener',
        'RenderObjectListener',
        'RenderSystem',
        'RenderSystemCapabilities',
        'RenderSystemCapabilitiesManager',
        'RenderSystemCapabilitiesSerializer',
        'RenderTarget',
        'RenderTargetListener',
        'RenderTexture',
        'MultiRenderTarget',
        'RenderWindow',
        'RenderOperation',
        'Resource',
        'ResourceBackgroundQueue',
        'ResourceGroupManager',
        'ResourceManager',
        'RibbonTrail',
        'Root',
        'SceneManager',
        'SceneManagerEnumerator',
        'SceneNode',
        'SceneQuery',
        'SceneQueryListener',
        'ScriptCompiler',
        'ScriptCompilerManager',
        'ScriptLoader',
        'Serializer',
        'ShadowCaster',
        'ShadowRenderable',
        'ShadowTextureManager',
        'SimpleRenderable',
        'SimpleSpline',
        'Skeleton',
        'SkeletonPtr',
        'SkeletonInstance',
        'SkeletonManager',
        'Sphere',
        'SphereSceneQuery',
        'StaticGeometry',
        'StreamSerialiser',
        'StringConverter',
        'StringInterface',
        'SubEntity',
        'SubMesh',
        'TagPoint',
        'Technique',
        'TempBlendedBufferInfo',
        'ExternalTextureSource',
        'TextureUnitState',
        'Texture',
        'TexturePtr',
        'TextureManager',
        'TransformKeyFrame',
        'Timer',
        'UserObjectBindings',
        'Vector2',
        'Vector3',
        'Vector4',
        'Viewport',
        'VertexAnimationTrack',
        'VertexBufferBinding',
        'VertexData',
        'VertexDeclaration',
        'VertexMorphKeyFrame',
        'WireBoundingBox',
        'WorkQueue',
        'Compositor',
        'CompositorManager',
        'CompositorChain',
        'CompositorInstance',
        'CompositorLogic',
        'CompositionTechnique',
        'CompositionPass',
        'CompositionTargetPass',
        'CustomCompositionPass',
         '*', '&']

# 读入文件，输出去掉注释后的字符串
def rawlines(fileName):
    # 读取原始文件
    f = open(fileName)
    lines = f.read()
    f.close()

    # 消去所有注释
    lines = re.sub(r'/\*(\s|.)*?\*/', '', lines) #多行注释
    lines = re.sub(r'//.*\n', '', lines) #单行注释

    # 消去enum
    lines = re.sub(r'enum(\s|.)*?\};', '', lines)

    return lines

# 输入：原始行
# 输出：是否找到class，找到的class行，剩余的行
def findClass(lines):
    i = 0
    l = len(lines)
    s = 'ini'
    beg = 0
    end = 0
    numBrace = 0
    c = lines.find('class')
    if c != -1:
        beg = c
        c = lines.find('};')
        if c != -1:
            end = c + 2
            return True, lines[beg:end], lines[end:]        
    return False, [], []

# 输入：class行
# 输出：class名称
def findClassName(c):
    name = c[:c.find('{')]
    return name.split()[-1]

# 输入：class行
# 输出：所有的public区域行
def _findPublicArea(c):
    pubArea = []
    pubPat = re.compile(r'(public:)(\s|.)*?(\};|public:|protected:|private:)')
    r = pubPat.search(c)
    while r != None:
        g = r.group()
        g1 = r.group(1)
        g3 = r.group(3)
        g = re.sub(g1, '', g)
        g = re.sub(g3, '', g)
        pubArea.append(g)

        sub = r.group().rfind(g3)
        sub = r.group()[:sub]
        c = c.replace(sub, '')
        r = pubPat.search(c)

    out = ''
    for a in pubArea:
        out += a
    return out

# 输入：public区域行
# 输出：已消除运算符重载的行
def _eliminateOperator(pubArea):
    pubArea = re.sub(r'\n.*operator(\s|.)*?}', '', pubArea)
    pubArea = re.sub(r'.*operator.*;', '', pubArea)
    return pubArea

# 输入：public区域行, class名
# 输出：构造函数行列表, 消去了构造函数的行
def _findConstructor(pubArea, className):
    constructors = []
    #constrPat = re.compile(className+r'\s*?\((\s|.)*?(\);|\})')
    constrPat = re.compile(className+r'\s*\(.*\)')
    r = constrPat.search(pubArea)
    while r != None:
        constructors.append(r.group())
        pubArea = pubArea.replace(r.group(), '')
        r = constrPat.search(pubArea)

    return constructors, pubArea

# 输入：public区域行
# 输出：(成员)函数行列表, 消去了(成员)函数的行
def _findFunction(pubArea):
    functions = []
    #pat = re.compile(r'\n.*? \((\s|.)*?\) \s.*? ;|\{(\s|.)*?\}')
    pat = re.compile(r'.*\((.|\n)*?\)')
    r = pat.search(pubArea)
    while r != None:
        functions.append(r.group())
        pubArea = pubArea.replace(r.group(), '')
        r = pat.search(pubArea)
    return functions, pubArea
    
        
# 输入：class行, class名
# 输出：构造函数行列表，成员函数行列表
# 注意，输出的有可能不是函数，非常粗糙，还需要继续筛选
def findMemberFunction(c, className):
    pubArea = _findPublicArea(c)
    pubArea = _eliminateOperator(pubArea)
    # 消去构造函数参数列表
    pubArea =  re.sub(r'\)\s*?:(\s|.)*?\{', ')\n{', pubArea)
    # 消去所有大括号里面的内容
    pubArea =  re.sub(r'\{(\s|.)*?\}', '', pubArea)
    cs, pubArea = _findConstructor(pubArea, className)
    fs, pubArea = _findFunction(pubArea)
    return cs, fs

# 输入：构造函数行列表
# 输出：成品字符串
def processConstructor(cs):
    out = ''
    for c in cs:
        func = c[c.find('(')+1:c.find(')')]
        func = func.split(',')
        for i in range(len(func)):
            t = ''
            for j in range(len(types)):
                if func[i].find(types[j]) != -1:
                    t += types[j] + ' '
            func[i] = t
        out += defConstructor(func)
    return out

def processFunction(fs, className):
    out = ''
    for f in fs:
        func = f
        if func.find('static') == -1:
            funcName = re.search(r'\s\w+\s*\(', func)
            if (funcName != None):
                funcName = funcName.group(0)[:-1]
                funcName = re.sub(r'\s', '', funcName)
                retType = func[:func.find(funcName)].split()
                if len(retType) > 0:
                    t = ''
                    for i in retType:
                        for j in types:
                            if i.find(j) != -1:
                                t += j + ' '
                    retType = t
                    func = func[func.find('(')+1:func.find(')')]
                    func = func.split(',')
                    #func = re.split('[, ]+', func)
                    outf = []
                    for i in range(len(func)):
                        t = ''
                        '''
                        for j in range(len(types)):
                            if func[i].find(types[j]) != -1:
                                t += types[j] + ' '
                        func[i] = t
                        '''
                        for j in types:
                            for fuck in func[i].split():
                                posfix = ''
                                if fuck.find('*') != -1:
                                    fuck = fuck.replace('*', '')
                                    posfix = '*'
                                elif fuck.find('&') != -1:
                                    fuck = fuck.replace('&', '')
                                    posfix = '&'
                                if fuck == j:
                                    t += j +  ' ' + posfix + ' '
                        func[i] = t

                    out += defMemberFunc(className, funcName, retType, func)
                
    return out
        
#------------------------------------------------------------

files = ['OgreMath.h', 'OgreVector2.h', 'OgreVector3.h', 'OgreVector4.h',
         'OgreMatrix3.h', 'OgreMatrix4.h', 'OgreQuaternion.h'
         ]

out = ''
for fi in files:
    out += '\n//---- file: ' + fi + '----\n'
    lines = rawlines(fi)
    classes = []
    f, c, l = findClass(lines)
    while f:
        classes.append(c)
        lines = l
        f, c, l = findClass(lines)
        

    out += beginModule()
    for i in range(len(classes)):
        c = classes[i]
        cn = findClassName(c)
        out += '\n\t//---- class: ' + cn + '----\n'
        #print cn
        cs, fs = findMemberFunction(c, cn)
        out += defClass(cn)
        out += processConstructor(cs)
        out += processFunction(fs, cn)
        if i < len(classes) - 1:
            out += '\t\t,\n'
    out += endModule()

print out
