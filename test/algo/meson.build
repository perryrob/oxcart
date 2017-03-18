
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

test_linregres_exe = executable('linregres', 'test_linregres.cpp',
                                  include_directories : inc,
                                  link_with : [oxlib,ox_algo_lib],
                                  dependencies :  [
                                      thread_dep,rt_dep,
                                      bs_dep,bt_dep,bt_log,bt_logs,bt_chrono
                                  ])

test_cksum_exe = executable('cksum', 'test_cksum.cpp',
                                  include_directories : inc,
                                  link_with : [oxlib,ox_algo_lib],
                                  dependencies :  [
                                      thread_dep,rt_dep,
                                      bs_dep,bt_dep,bt_log,bt_logs,bt_chrono
                                  ])

test_polar_exe = executable('polar', 'test_polar.cpp',
                                  include_directories : inc,
                                  link_with : [oxlib,ox_algo_lib],
                                  dependencies :  [
                                      thread_dep,rt_dep,
                                      bs_dep,bt_dep,bt_log,bt_logs,bt_chrono
                                  ])

test_wind_exe = executable('wind', 'test_wind.cpp',
                                  include_directories : inc,
                                  link_with : [oxlib,ox_algo_lib],
                                  dependencies :  [
                                      thread_dep,rt_dep,
                                      bs_dep,bt_dep,bt_log,bt_logs,bt_chrono
                                  ])

test_turbulence_exe = executable('turbulence', 'test_turbulence.cpp',
                                  include_directories : inc,
                                  link_with : [oxlib,ox_algo_lib],
                                  dependencies :  [
                                      thread_dep,rt_dep,
                                      bs_dep,bt_dep,bt_log,bt_logs,bt_chrono
                                  ])

test('madg', test_Madg_exe)
test('airdata', test_airdata_exe)
test('linregres', test_linregres_exe)
test('nmea_cksum', test_cksum_exe)
test('polar', test_polar_exe)
test('wind', test_wind_exe)
test('turbulence', test_turbulence_exe)
