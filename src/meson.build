oxcart_sources = ['named_store.cpp','oxmem.cpp']

boost_dep=dependency('boost', version: '>=1.58')
thread_dep = cpp.find_library('pthread', required : true)
rt_dep = cpp.find_library('rt', required : true)
bs_dep = cpp.find_library('boost_system', required : true)
bt_dep = cpp.find_library('boost_thread', required : true)


oxlib = shared_library(
    'oxlib',
    oxcart_sources,
    include_directories : inc,
    dependencies :  [
        thread_dep,rt_dep,
        bs_dep,bt_dep
],
    install : true
)

#executable('oxcart', 'main.cpp', dependencies : [
#    thread_dep,rt_dep,
#    bs_dep,bt_dep
#],link_with : oxcartlib)

#executable('oxcart', 'main.cpp', dependencies : [
#    thread_dep,rt_dep,
#    bs_dep,bt_dep
#])
