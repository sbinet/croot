# -*- python -*-

top = '.'
out = '__build__'

def options(ctx):
    ctx.load('compiler_c')
    ctx.load('compiler_cxx')
    
def configure(ctx):

    ctx.load('compiler_c')
    ctx.load('compiler_cxx')

    # find root
    ctx.find_program('root',        var='ROOT-EXE', mandatory=True)
    ctx.find_program('root-config', var='ROOT-CONFIG', mandatory=True)
    root_cfg = ctx.env["ROOT-CONFIG"]
    ctx.check_cfg(path=root_cfg, package="", 
                  uselib_store="CERN_ROOT_SYSTEM",
                  args='--libs --cflags', 
                  mandatory=True)
    
def build(ctx):

    ctx(features='cxx cxxshlib',
        name    = 'croot',
        source  = 'src/croot.cxx src/croot_hist.cxx',
        target  = 'croot',
        includes= ['include',],
        export_includes = ['include'],
        cxxflags = ['-O2', '-Wall', '-W', '-Werror',],
        lib = "Reflex Cintex dl",
        use = "CERN_ROOT_SYSTEM",
        )

    hdr_dir = ctx.path.find_dir('include')
    hdrs = hdr_dir.ant_glob('**/*', dir=False)

    from os.path import join as pjoin
    ctx(rule=write_pkgcfg, target="croot.pc", install_path=pjoin(ctx.env.LIBDIR, "pkgconfig"), always=True)

    ctx.install_files(
        '${PREFIX}/include',
        hdrs,
        cwd=hdr_dir,
        relative_trick=True
        )

    if ctx.env.DO_TEST:
        ctx.recurse('examples', name='build')

def write_pkgcfg(task):
    def libstr(use):
        s = []
        if task.env["LIBPATH_"+use]:
            s.extend("-L%s"%l for l in task.env["LIBPATH_"+use])
            s.extend("-l%s"%l for l in task.env["LIB_"+use])
        return " ".join(s)

    def cppstr(use):
        s = []
        s.extend(task.env.get_flat("CPPFLAGS_"+use).split())
        s.extend("-I"+i for i in task.env.get_flat("INCLUDES_"+use).split())
        return " ".join(s)

    lines = []
    from textwrap import dedent
    lines.append(dedent("""
    prefix=%(PREFIX)s
    exec_prefix=${prefix}
    includedir=${prefix}/include
    libdir=%(LIBDIR)s
    CXX=%(CXX)s
    git_describe=%(GIT_VERSION)s

    Name: croot
    Description: a simple work-in-progress C-API binding to the C++ ROOT framework.
    URL: https://github.com/sbinet/croot
    Version: %(CROOT_VERSION)s
    Cflags: -I%(PREFIX)s/include
    Libs: -L${libdir} -lcroot
    """ % dict(
        PREFIX=task.env.PREFIX, 
        LIBDIR=task.env.LIBDIR, 
        CXX=task.env.CXX[0], 
        CROOT_VERSION='0.0.1', 
        GIT_VERSION=get_git_version(),
    )))

    task.outputs[0].write("\n".join(lines))
    return 0

def get_git_version():
    try:
        from commands import getstatusoutput
    except ImportError: # py3
        from subprocess import getstatusoutput
    status, output = getstatusoutput("git describe --dirty")
    if status: return "unknown"
    return output

