#!/bin/bash

BASE_PATH=/home/perryr/oxcart/
export LD_LIBRARY_PATH=${BASE_PATH}/lib:$LD_LIBRARY_PATH
EXE_PATH=${BASE_PATH}/bin

START_APPS="oxcart_d
oxalgos
"

KILL_APPS="oxcart_d
oxalgos
oxclient
"


case "$1" in

    start)
        for app in ${START_APPS}; do
            ${EXE_PATH}/${app} &
        done
        ;;
    kobo)
        ${EXE_PATH}/oxclient -k &
        ;;
    start_all)
        $0 start
        sleep 1
        $0 kobo
        ;;
    restart)
        $0 stop
        $0 start
        ;;
    stop)
        for app in ${KILL_APPS}; do
            for pid in $( ps -ef |  grep "${app}" | grep -v grep | awk '{print $2;}'); do
                kill $pid
            done
        done
        ;;
    *)
        echo "$0 [start,stop,restart]"
esac