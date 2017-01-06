oxcart_sources = [ 'named_store.cpp',
                   'oxmem.cpp',
                   'smbus.cpp',
                   'arduino_core.cpp',
                   'arduino_wire.cpp',
                   'oxapp.cpp',
                   'oxi2cbus.cpp'
    ]

boost_dep=dependency('boost', version: '>=1.58')
thread_dep = cpp.find_library('pthread', required : true)
rt_dep = cpp.find_library('rt', required : true)
bs_dep = cpp.find_library('boost_system', required : true)
bt_dep = cpp.find_library('boost_thread', required : true)
bt_log = cpp.find_library('boost_log', required : true)
bt_logs = cpp.find_library('boost_log_setup', required : true)
bt_dt = cpp.find_library('boost_date_time', required : true)
bt_f = cpp.find_library('boost_filesystem', required : true)


oxlib = shared_library(
    'oxlib',
    oxcart_sources,
    include_directories : inc,
    dependencies :  [
        thread_dep,rt_dep,
        bs_dep,bt_dep,bt_log,bt_logs
],
    install : true
)

subdir('devices')

executable('oxcart',
           'main.cpp',
           include_directories : inc,
           dependencies : [
               thread_dep,rt_dep,
               bs_dep,bt_dep,
           ],
           link_with : oxlib
)

