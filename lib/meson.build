cc = meson.get_compiler('c')

deps += declare_dependency(
    dependencies : cc.find_library('anemone', dirs: [meson.current_source_dir() + '/Anemone/build']),
    include_directories : include_directories('./Anemone/public')
)