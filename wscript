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
        source  = 'src/croot.cxx',
        target  = 'croot',
        includes= ['include',],
        export_includes = ['include'],
        lib = "Reflex Cintex dl",
        use = "CERN_ROOT_SYSTEM",
        )

    ctx.install_files('${PREFIX}/include', 'include/croot.h')

    #ctx.recurse('examples')
    
