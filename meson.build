project('R-clock', 'c')

includes = include_directories('include')

deps = dependency('ncurses')

src = files()

subdir('src')

executable('rclock', src, include_directories : includes, dependencies : deps)