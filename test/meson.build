
test_named_store_exe = executable('test_named_store', 'test_named_store.cpp',
                                  include_directories : inc,
                                  link_with : [oxlib],
                                  dependencies :  [
                                      thread_dep,rt_dep,
                                      bs_dep,bt_dep
                                  ])

test('oxlib test', test_named_store_exe)
