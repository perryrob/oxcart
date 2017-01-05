project(
    'oxcart', 'cpp',
     version:'1.0.0',
     license : 'BSD'
)

cpp = meson.get_compiler('cpp')
inc = include_directories('include')

add_global_arguments('-std=c++11', language : 'cpp')
add_global_arguments('-g', language : 'cpp')

subdir('include')
subdir('src')
subdir('test')




