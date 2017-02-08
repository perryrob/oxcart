oxcart_sources = [
    'trivial_log.cpp',
    'named_store.cpp',
    'oxmem.cpp',
    'smbus.cpp',
    'arduino_core.cpp',
    'arduino_wire.cpp',
    'oxapp.cpp',
    'oxi2cbus.cpp',
    'oxGPSDbus.cpp',
    'gpsd_shm.cpp',
    'blue_comm.cpp',
    'oxbluebus.cpp',
    'oxalgothread.cpp',
    'oxalgo.cpp',
    'gpsdclient.cpp'
]

boost_dep=dependency('boost', version: '>=1.58')
thread_dep = cpp.find_library('pthread', required : true)
rt_dep = cpp.find_library('rt', required : true)
bs_dep = cpp.find_library('boost_system', required : true)
bt_dep = cpp.find_library('boost_thread', required : true)
bt_log = cpp.find_library('boost_log', required : true)
bt_logs = cpp.find_library('boost_log_setup', required : true)
bt_dt = cpp.find_library('boost_date_time', required : true)
bt_chrono = cpp.find_library('boost_chrono', required : true)
bt_f = cpp.find_library('boost_filesystem', required : true)
bt_po = cpp.find_library('boost_program_options', required : true)
gpsd_dep = cpp.find_library('gps', required : true)
bluetooth_dep = cpp.find_library('bluetooth', required : true)

oxlib = shared_library(
    'oxlib',
    oxcart_sources,
    include_directories : inc,
    dependencies :  [
        thread_dep,rt_dep,
        bs_dep,bt_dep,bt_log,bt_logs,gpsd_dep,bluetooth_dep,bt_chrono
],
    install : true
)

subdir('devices')
subdir('algo')



