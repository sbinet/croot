#

top = '.'
out = '__build__'

def options(ctx):
    ctx.load('compiler_c')
    ctx.load('compiler_cxx')
    
def configure(ctx):

    ctx.load('compiler_c')
    ctx.load('compiler_cxx')
    
def build(ctx):

    ctx.env.append_unique(
        'LIBPATH',
        ['/usr/lib/root',
         ]
        )
    ctx(features='cxx cxxshlib',
        name    = 'croot',
        source  = 'src/croot.cxx',
        target  = 'croot',
        includes= ['/usr/include/root',
                   'include'],
        lib     = 'Core Cint Tree RIO Thread Hist Graf MathCore Matrix Net dl',
        )

    ctx.install_files('${PREFIX}/include', 'include/croot.h')
