
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
                                      bs_dep,bt_dep,bt_log,bt_logs
                                  ])

test('TCA9548A', test_TCA9548A_exe)
test('BMP085', test_BMP085_exe)
