env = Environment(CXX='/usr/gcc-5.1.0/bin/g++-5.1.0',
                  CXXFLAGS=['-Wall', '-Wextra', '-fopenmp'],
                  LINKFLAGS=['-fopenmp'])

src_cube = ['cube/cube.cpp']
lib_cube = []

tgt = 'nbody'
src = ['main.cpp'] + src_cube
lib = [] + lib_cube

nbody = env.Program(target=tgt, 
                    source=src,
                    LIBS=lib)
