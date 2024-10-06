project(
    'Student Database',
    ['c', 'cpp'],
    license: 'MIT',
    license_files: 'LICENSE',
    version: '1.0.0',
    default_options: ['warning_level=3', 'cpp_std=c++17']
)

compiler = meson.get_compiler('c')

inc = include_directories('include')
json_inc = include_directories('jsonlib')

subdir('src')
src += 'main.cpp'

sdl_deps = [
    dependency('sdl2'),
    dependency('sdl2_image'),
    dependency('sdl2_ttf'),
]

if compiler.get_id() == 'msvc'
    sdl_deps += dependency('sdl2main')
endif

executable(
    'app',
    sources: src,
    include_directories: [inc, json_inc],
    dependencies: sdl_deps,
    win_subsystem: 'console'
)
