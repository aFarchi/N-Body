#____________
# Environment
#____________

env = DefaultEnvironment()

# C++ compiler
env.Replace(CXX='/usr/gcc-5.1.0/bin/g++-5.1.0')

# Flags
flags = {}
flags['CCFLAGS'] = ['-Wall', '-Wextra']

env.MergeFlags(flags)

#______________
# Target N-BODY
#______________

# Main target
tgt       = 'nbody'
src       = ['main.cpp']
lib       = []
lib_path  = []
cpp_path  = []

#__________
# Libraries
#__________

# Small Patch for strings
src      += ['patch/toString.h']

# Class to use a log file
src      += ['log/logFile.cpp']

# Class cube
src      += ['cube/cube.cpp']

# FFTW library [must be the last one]
lib      += ['fftw3', 'm']
lib_path += ['/usr/local/fftw/lib/']
cpp_path += ['/usr/local/fftw/include/']

#___________________________
# Program N-BODY from target
#___________________________

nbody     = env.Program(target=tgt, 
                        source=src,
                        LIBS=lib,
                        LIBPATH=lib_path,
                        CPPPATH=cpp_path)
