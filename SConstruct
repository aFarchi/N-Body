env = Environment(CXX='/usr/gcc-5.1.0/bin/g++-5.1.0',
                  CXXFLAGS=['-Wall', '-Wextra', '-fopenmp'],
                  LINKFLAGS=['-fopenmp'])

tgt = 'nbody'
src = ['main.cpp']
lib = []

nbody = env.Program(target=tgt, 
                    source=src,
                    LIBS=lib)
