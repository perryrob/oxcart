
test_TCA9548A_exe = executable('TCA9548A', 'test_TCA9548A.cpp',
                                  include_directories : inc,
                                  link_with : [oxlib,ox_device_lib],
                                  dependencies :  [
                                      thread_dep,rt_dep,
                                      bs_dep,bt_dep,bt_log,bt_logs
                                  ])

test_BMP085_exe = executable('BMP085', 'test_BMP085.cpp',
                                  include_directories : inc,
                                  link_with : [oxlib,ox_device_lib],
                                  dependencies :  [
                                      thread_dep,rt_dep,
                                      bs_dep,bt_dep,bt_log,bt_logs,bt_chrono
                                  ])

test_LSM6_exe = executable('LSM6', 'test_LSM6.cpp',
                                  include_directories : inc,
                                  link_with : [oxlib,ox_device_lib],
                                  dependencies :  [
                                      thread_dep,rt_dep,
                                      bs_dep,bt_dep,bt_log,bt_logs
                                  ])

test_LIS3MDL_exe = executable('LIS3MDL', 'test_LIS3MDL.cpp',
                                  include_directories : inc,
                                  link_with : [oxlib,ox_device_lib],
                                  dependencies :  [
                                      thread_dep,rt_dep,
                                      bs_dep,bt_dep,bt_log,bt_logs
                                  ])

test_GPS_exe = executable('GPS', 'test_GPS.cpp',
                                  include_directories : inc,
                                  link_with : [oxlib,ox_device_lib],
                                  dependencies :  [
                                      thread_dep,rt_dep,
                                      bs_dep,bt_dep,bt_log,bt_logs,gpsd_dep
                                  ])

test_ALL_DEVICES_exe = executable('test_ALL_DEVICES','test_ALL_DEVICES.cpp',
                                  include_directories : inc,
                                  link_with : [oxlib,ox_device_lib],
                                  dependencies :  [
                                      thread_dep,rt_dep,
                                      bs_dep,bt_dep,bt_log,bt_logs,gpsd_dep
                                  ])

test_ARDUINO_DISP_exe = executable('test_ARDUINO_DISP','test_ARDUINO_DISP.cpp',
                                  include_directories : inc,
                                  link_with : [oxlib,ox_device_lib],
                                  dependencies :  [
                                      thread_dep,rt_dep,
                                      bs_dep,bt_dep,bt_log,bt_logs,gpsd_dep
                                  ])

test_KEYBOARD_exe = executable('test_KEYBOARD','test_KEYBOARD.cpp',
                                  include_directories : inc,
                                  link_with : [oxlib,ox_device_lib],
                                  dependencies :  [
                                      thread_dep,rt_dep,
                                      bs_dep,bt_dep,bt_log,bt_logs,gpsd_dep
                                  ])


test_NCURSES_exe = executable('test_NCURSES','test_NCURSES.cpp',
                                  include_directories : inc,
                                  link_with : [oxlib,ox_device_lib],
                                  dependencies :  [
                                      thread_dep,rt_dep,
                                      bs_dep,bt_dep,bt_log,bt_logs,gpsd_dep,
                                      ncurses_dep,ncursesw_dep 
                                  ])


test('TCA9548A', test_TCA9548A_exe)
test('BMP085', test_BMP085_exe)
test('LSM6', test_LSM6_exe)
test('LIS3MDL', test_LIS3MDL_exe)
test('GPS', test_GPS_exe)
test('ALL_DEVICES', test_ALL_DEVICES_exe)
test('ARDUINO_DISP', test_ARDUINO_DISP_exe)
test('KEYBOARD', test_KEYBOARD_exe)
