oxcart_device_sources = [ 'BMP085.cpp', 'TCA9548A.cpp']


ox_device_lib = shared_library(
    'oxdevlib',
    oxcart_device_sources,
    include_directories : inc,
    dependencies :  [
        thread_dep,rt_dep,
        bs_dep,bt_dep,bt_log,bt_logs
    ],
    link_with : oxlib,
    install : true
)

