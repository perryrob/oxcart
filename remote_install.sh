#!/bin/bash

if [ "$(uname -n)" = "wildcat" ]; then
    echo "Coping files to remote host" 

    DST_DIR=/home/perryr/oxcart

    SRC_DIR=/home/perryr/proj/oxcart

    REMOTE=bone

    scp -q ${SRC_DIR}/build/src/*.so ${REMOTE}:${DST_DIR}/lib/.
    echo "cp -> ${SRC_DIR}/build/src/*.so ${REMOTE}:${DST_DIR}/lib/."
    scp -q ${SRC_DIR}/build/src/algo/*.so ${REMOTE}:${DST_DIR}/lib/.
    echo "cp -> ${SRC_DIR}/build/src/algo/*.so ${REMOTE}:${DST_DIR}/lib/."
    scp -q ${SRC_DIR}/build/src/devices/*.so ${REMOTE}:${DST_DIR}/lib/.
    echo "cp -> ${SRC_DIR}/build/src/devices*.so ${REMOTE}:${DST_DIR}/lib/."

    
    scp -q ${SRC_DIR}/build/apps/oxalgos ${REMOTE}:${DST_DIR}/bin/.
    echo "cp -> ${SRC_DIR}/build/apps/oxalgos ${REMOTE}:${DST_DIR}/bin/."
    scp -q ${SRC_DIR}/build/apps/oxcart_d ${REMOTE}:${DST_DIR}/bin/.
    echo "cp -> ${SRC_DIR}/build/apps/oxcart_d ${REMOTE}:${DST_DIR}/bin/."
    scp -q ${SRC_DIR}/build/apps/oxclient ${REMOTE}:${DST_DIR}/bin/.
    echo "cp -> ${SRC_DIR}/build/apps/oxclient ${REMOTE}:${DST_DIR}/bin/."
    
    scp -rq ${SRC_DIR}/build/test ${REMOTE}:${DST_DIR}/.
    echo "cp -> ${SRC_DIR}/build/test ${REMOTE}:${DST_DIR}/."
    
    scp -rq ${SRC_DIR}/include/* ${REMOTE}:${DST_DIR}/include/.
    echo "cp -> ${SRC_DIR}/include/* ${REMOTE}:${DST_DIR}/include/."
    
    echo " done."
else
    echo "Nothing to do on $(uname -n)"
fi
