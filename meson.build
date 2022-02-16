project('tracy-examples',
  ['cpp'],
  version: '0.1',
  meson_version: '>=0.60',
  default_options : ['buildtype=release', 'cpp_std=c++17', 'default_library=shared'],
  license: 'BSD')

dep_dl = meson.get_compiler('cpp').find_library('dl', required : true)

tracy_defines = ['-DTRACY_ENABLE']

lib_tracy = static_library('tracy',
              sources: ['tracy/TracyClient.cpp'],
              cpp_args: tracy_defines)

dep_tracy = declare_dependency(
              include_directories: ['tracy'],
              link_with: lib_tracy)

dep_omp = dependency('openmp')

subdir('examples')

