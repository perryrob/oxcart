oxcart_algo_sources = [ 
    'MadgwickAHRS.cpp'
]


ox_algo_lib = shared_library(
    'oxalgolib',
    oxcart_algo_sources,
    include_directories : inc,
    dependencies :  [
        thread_dep,rt_dep,
        bs_dep,bt_dep,bt_log,bt_logs,gpsd_dep
    ],
    link_with : oxlib,
    install : true
)
