class BuildOptions:
    pass

#______________
# Configuration
#______________

debug_options           = BuildOptions()
debug_options.build     = True
debug_options.directory = 'debug/'

release_options           = BuildOptions()
release_options.build     = False
release_options.directory = 'release/'

#___________________
# Common environment
#___________________

common_env = DefaultEnvironment()

# C++ compiler
common_env.Replace(CXX='/usr/local/bin/g++')

# Flags
common_flags            = {}
common_flags['CCFLAGS'] = ['-Wall', '-Wextra']
common_flags['VERSION'] = [1]

common_env.MergeFlags(common_flags)

#__________________
# Debug environment
#__________________

debug_env         = common_env.Clone()
debug_env.options = debug_options

# Flags

debug_flags               = {}
debug_flags['CPPDEFINES'] = ['DEBUG']

debug_env.MergeFlags(debug_flags)

# Building directory

debug_env.VariantDir('build/'+debug_env.options.directory, 'src', duplicate=0)

#____________________
# Release environment
#____________________

release_env         = common_env.Clone()
release_env.options = release_options

# Flags

release_flags               = {}
release_flags['CPPDEFINES'] = ['RELEASE']

release_env.MergeFlags(release_flags)

# Building directory

release_env.VariantDir('build/'+release_env.options.directory, 'src', duplicate=0)

#______________
# Build targets
#______________

for env in [debug_env, release_env]:
    if env.options.build:
        env.SConscript('build/'+env.options.directory+'SConscript', dict(env=env))

