oxcart_device_sources = [ 
    'BMP085.cpp', 
    'TCA9548A.cpp',
    'LSM6.cpp',
    'GPS.cpp',
    'LIS3MDL.cpp',
    'KOBO.cpp',
    'ARDUINO_DISP.cpp',
    'KEYBOARD.cpp',
    'NCURSES.cpp'
]


ox_device_lib = shared_library(
    'oxdevlib',
    oxcart_device_sources,
    include_directories : inc,
    dependencies :  [
        thread_dep,rt_dep,
        bs_dep,bt_dep,bt_log,bt_logs,gpsd_dep,ncurses_dep,ncursesw_dep
    ],
    link_with : [oxlib,ox_algo_lib],
    install : INSTALL,
    install_dir : LIB_INSTALL_DIR
)

