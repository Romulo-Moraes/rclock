project('R-clock', 'c')

includes = include_directories('include')

cc = meson.get_compiler('c')

deps = [dependency('ncurses')]
deps += cc.find_library('m', required : true)

src = files()

subdir('src')

executable('rclock', src, include_directories : includes, dependencies : deps, install : true)