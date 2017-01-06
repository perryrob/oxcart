
test_TCA9548A_exe = executable('TCA9548A', 'test_TCA9548A.cpp',
                                  include_directories : inc,
                                  link_with : [oxlib,ox_device_lib],
                                  dependencies :  [
                                      thread_dep,rt_dep,
                                      bs_dep,bt_dep
                                  ])

test('TCA9548A', test_TCA9548A_exe)
