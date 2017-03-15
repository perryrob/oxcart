project(
    'oxcart', 'cpp',
     version:'1.0.0',
     license : 'BSD'
)

cpp = meson.get_compiler('cpp')

LIB_DIRS=['/usr/lib','/usr/local/lib']
INCLUDE_DIRS=['include']
INSTALL=true

BIN_INSTALL_DIR='/home/perryr/oxcart/bin'
LIB_INSTALL_DIR='/home/perryr/oxcart/lib'
INCLUDE_INSTALL_DIR='/home/perryr/oxcart/include'

if meson.is_cross_build()
   INCLUDE_DIRS=['include','/usr/local/arm-linux-gnueabihf/include']
   LIB_DIRS=['/usr/lib','/usr/local/arm-linux-gnueabihf/lib']
   add_global_arguments('-Wno-deprecated',language : 'cpp')
   INSTALL=false
endif

inc = include_directories(INCLUDE_DIRS)

add_global_arguments('-std=c++11', language : 'cpp')
add_global_arguments('-g', language : 'cpp')

add_global_arguments('-DBOOST_LOG_DYN_LINK', language : 'cpp')


subdir('include')
subdir('src')
subdir('test')
subdir('apps')

# meson.set_install_script('remote_isntall.sh')

