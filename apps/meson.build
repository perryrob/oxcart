

executable('oxcart_d',
           'oxcart_d.cpp',
           include_directories : inc,
           dependencies : [
               thread_dep,rt_dep,
               bs_dep,bt_dep,bt_log,bt_logs,gpsd_dep,bluetooth_dep
           ],
           link_with : [oxlib,ox_device_lib]
)

executable('oxclient',
           'oxclient.cpp',
           include_directories : inc,
           dependencies : [
               thread_dep,rt_dep,
               bs_dep,bt_dep,bt_log,bt_logs,gpsd_dep,bluetooth_dep
           ],
           link_with : [oxlib,ox_device_lib]
)
