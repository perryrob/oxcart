

executable('oxcart_d',
           'oxcart_d.cpp',
           include_directories : inc,
           dependencies : [
               thread_dep,rt_dep,
               bs_dep,bt_dep,bt_log,bt_logs,gpsd_dep,bluetooth_dep
           ],
           link_with : [oxlib,ox_device_lib],
           install : INSTALL,
           install_dir : BIN_INSTALL_DIR
)

executable('mag_cal',
           'mag_cal.cpp',
           include_directories : inc,
           dependencies : [
               thread_dep,rt_dep,
               bs_dep,bt_dep,bt_log,bt_logs,gpsd_dep,bluetooth_dep
           ],
           link_with : [oxlib,ox_device_lib],
           install : INSTALL,
           install_dir : BIN_INSTALL_DIR
)

executable('oxclient',
           'oxclient.cpp',
           include_directories : inc,
           dependencies : [
               thread_dep,rt_dep,
               bs_dep,bt_dep,bt_log,bt_logs,gpsd_dep,bluetooth_dep,bt_po
           ],
           link_with : [oxlib,ox_device_lib,ox_algo_lib],
           install : INSTALL,
           install_dir : BIN_INSTALL_DIR
)

executable('oxalgos',
           'oxalgos.cpp',
           include_directories : inc,
           dependencies : [
               thread_dep,rt_dep,
               bs_dep,bt_dep,bt_log,bt_logs,gpsd_dep,bluetooth_dep
           ],
           link_with : [oxlib,ox_device_lib,ox_algo_lib],
           install : INSTALL,
           install_dir : BIN_INSTALL_DIR
)
executable('gpspipe',
           'gpspipe.cpp',
           include_directories : inc,
           dependencies : [
               thread_dep,rt_dep,
               bs_dep,bt_dep,bt_log,bt_logs,gpsd_dep,bluetooth_dep
           ],
           link_with : [oxlib,ox_device_lib],
           install : INSTALL,
           install_dir : BIN_INSTALL_DIR
)
