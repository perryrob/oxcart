
test_named_store_exe = executable('test_named_store', 'test_named_store.cpp',
                                  include_directories : inc,
                                  link_with : [oxlib],
                                  dependencies :  [
                                      thread_dep,rt_dep,
                                      bs_dep,bt_dep,bt_log,bt_logs,bt_chrono
                                  ])

test_oxmem_exe = executable('test_oxmem', 'test_oxmem.cpp',
                                  include_directories : inc,
                                  link_with : [oxlib],
                                  dependencies :  [
                                      thread_dep,rt_dep,
                                      bs_dep,bt_dep,bt_log,bt_logs,bt_chrono
                                  ])

test_oxbus_exe = executable('test_oxbus', 'test_oxbus.cpp',
                                  include_directories : inc,
                                  link_with : [oxlib],
                                  dependencies :  [
                                      thread_dep,rt_dep,
                                      bs_dep,bt_dep,bt_log,bt_logs,bt_chrono
                                  ])

test_awire_exe = executable('test_awire', 'test_arduino_wire.cpp',
                            include_directories : inc,
                            link_with : [oxlib],
                            dependencies :  [
                                thread_dep,rt_dep,
                                bs_dep,bt_dep,bt_log,bt_logs,bt_chrono
                            ])

test_oxapp_exe = executable('test_oxapp', 'test_oxapp.cpp',
                            include_directories : inc,
                            link_with : [oxlib],
                            dependencies :  [
                                thread_dep,rt_dep,
                                bs_dep,bt_dep,bt_log,bt_logs,bt_chrono
                            ])

test_oxblue_exe = executable('test_oxblue', 'test_oxblue.cpp',
                            include_directories : inc,
                            link_with : [oxlib],
                            dependencies :  [
                                thread_dep,rt_dep,
                                bs_dep,bt_dep,bt_log,bt_logs,bluetooth_dep,
                                bt_chrono
                            ])

test_oxalgo_exe = executable('test_algo', 'test_oxalgo.cpp',
                            include_directories : inc,
                            link_with : [oxlib],
                            dependencies :  [
                                thread_dep,rt_dep,
                                bs_dep,bt_dep,bt_log,bt_logs,bluetooth_dep,
                                bt_chrono
                            ])

test_oxalgothread_exe = executable('test_algothread', 'test_oxalgothread.cpp',
                            include_directories : inc,
                            link_with : [oxlib],
                            dependencies :  [
                                thread_dep,rt_dep,
                                bs_dep,bt_dep,bt_log,bt_logs,bluetooth_dep,
                                bt_chrono
                            ])


test('test_named_store test', test_named_store_exe)
test('test_oxmem test', test_oxmem_exe)
test('test_oxbus test', test_oxbus_exe)
test('test_awire test', test_awire_exe)
test('test_oxapp test', test_oxapp_exe)
test('test_oxblue test', test_oxblue_exe)
test('test_algo test', test_oxalgo_exe)
test('test_algothread test', test_oxalgo_exe)

subdir( 'devices' )
subdir( 'algo' )