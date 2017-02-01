
test_Madg_exe = executable('Madg', 'test_Madg.cpp',
                                  include_directories : inc,
                                  link_with : [oxlib,ox_algo_lib],
                                  dependencies :  [
                                      thread_dep,rt_dep,
                                      bs_dep,bt_dep,bt_log,bt_logs,bt_chrono
                                  ])

test_airdata_exe = executable('airdata', 'test_airdata.cpp',
                                  include_directories : inc,
                                  link_with : [oxlib,ox_algo_lib],
                                  dependencies :  [
                                      thread_dep,rt_dep,
                                      bs_dep,bt_dep,bt_log,bt_logs,bt_chrono
                                  ])

test('madg', test_Madg_exe)
test('airdata', test_airdata_exe)
