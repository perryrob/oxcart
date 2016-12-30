
test_named_store_exe = executable('test_named_store', 'test_named_store.cpp',
                                  include_directories : inc,
                                  link_with : [oxlib],
                                  dependencies :  [
                                      thread_dep,rt_dep,
                                      bs_dep,bt_dep
                                  ])

test_oxmem_exe = executable('test_oxmem', 'test_oxmem.cpp',
                                  include_directories : inc,
                                  link_with : [oxlib],
                                  dependencies :  [
                                      thread_dep,rt_dep,
                                      bs_dep,bt_dep
                                  ])

test_oxdev_exe = executable('test_oxdev', 'test_oxdev.cpp',
                                  include_directories : inc,
                                  link_with : [oxlib],
                                  dependencies :  [
                                      thread_dep,rt_dep,
                                      bs_dep,bt_dep
                                  ])

test('test_named_store test', test_named_store_exe)
test('test_oxmem test', test_oxmem_exe)
test('test_odev test', test_oxdev_exe)
