project('R-clock', 'c')

includes = include_directories('include', 'lib/Anemone/public')

cc = meson.get_compiler('c')

deps = [dependency('ncurses')]
deps += cc.find_library('m', required : true)

src = files()

add_project_arguments('-g', language : 'c')

dbus_dep = dependency('dbus-1') # Find the dbus-1 library

subdir('src')
subdir('lib')

executable('rclock', src, include_directories : includes, dependencies : [deps, dbus_dep], install : true)