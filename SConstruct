env = Environment(CXX='/usr/gcc-5.1.0/bin/g++-5.1.0',
                  CXXFLAGS=['-Wall', '-Wextra', '-fopenmp'],
                  LINKFLAGS=['-fopenmp'])

src_patch = ['patch/toString.h']
lib_patch = []

src_log   = ['log/logFile.cpp']
lib_log   = []

src_cube  = ['cube/cube.cpp']
lib_cube  = []

tgt       = 'nbody'
src       = ['main.cpp'] + src_cube + src_log + src_patch
lib       = [] + lib_cube + lib_log + lib_patch

nbody    = env.Program(target=tgt, 
                       source=src,
                       LIBS=lib)
