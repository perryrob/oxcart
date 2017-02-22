#!/bin/bash

if [ "$(uname -n)" = "wildcat" ]; then

    DST_DIR=/home/perryr/oxcart

    SRC_DIR=/home/perryr/proj/oxcart

    REMOTE=bone
    
    case "$1" in
    
    lib)
        echo "Stopping remote apps..."
        ssh $REMOTE '/home/perryr/oxcart/bin/ox.sh stop' > /dev/null 2>&1
        scp -q ${SRC_DIR}/build/src/*.so ${REMOTE}:${DST_DIR}/lib/.
        echo "cp -> ${SRC_DIR}/build/src/*.so ${REMOTE}:${DST_DIR}/lib/."
        scp -q ${SRC_DIR}/build/src/algo/*.so ${REMOTE}:${DST_DIR}/lib/.
        echo "cp -> ${SRC_DIR}/build/src/algo/*.so ${REMOTE}:${DST_DIR}/lib/."
        scp -q ${SRC_DIR}/build/src/devices/*.so ${REMOTE}:${DST_DIR}/lib/.
        echo "cp -> ${SRC_DIR}/build/src/devices*.so ${REMOTE}:${DST_DIR}/lib/."
        ssh $REMOTE '/home/perryr/oxcart/bin/ox.sh start' > /dev/null 2>&1
        echo "Start remote apps..."
        ;;
    bin)
        echo "Stopping remote apps..."
        ssh $REMOTE '/home/perryr/oxcart/bin/ox.sh stop' > /dev/null 2>&1
        scp -q ${SRC_DIR}/build/apps/oxalgos ${REMOTE}:${DST_DIR}/bin/.
        echo "cp -> ${SRC_DIR}/build/apps/oxalgos ${REMOTE}:${DST_DIR}/bin/."
        scp -q ${SRC_DIR}/build/apps/oxcart_d ${REMOTE}:${DST_DIR}/bin/.
        echo "cp -> ${SRC_DIR}/build/apps/oxcart_d ${REMOTE}:${DST_DIR}/bin/."
        scp -q ${SRC_DIR}/build/apps/oxclient ${REMOTE}:${DST_DIR}/bin/.
        echo "cp -> ${SRC_DIR}/build/apps/oxclient ${REMOTE}:${DST_DIR}/bin/."
        scp -q ${SRC_DIR}/apps/ox.sh ${REMOTE}:${DST_DIR}/bin/.
        echo "cp -> ${SRC_DIR}/apps/ox.sh ${REMOTE}:${DST_DIR}/bin/."
        ssh $REMOTE '/home/perryr/oxcart/bin/ox.sh start' > /dev/null 2>&1
        echo "Start remote apps..."
        ;;
    test)
         scp -rq ${SRC_DIR}/build/test ${REMOTE}:${DST_DIR}/.
         echo "cp -> ${SRC_DIR}/build/test ${REMOTE}:${DST_DIR}/."
         ;;
    arduino)
        pushd ${SRC_DIR}/arduino
        . ./env/bin/activate
        pushd oxcart
        platformio run -t upload &&  sleep 1 && platformio device monitor
        deactivate
        popd
        popd
        ;;
    include)
        scp -rq ${SRC_DIR}/include/* ${REMOTE}:${DST_DIR}/include/.
        echo "cp -> ${SRC_DIR}/include/* ${REMOTE}:${DST_DIR}/include/."
        ;;
    *)
        echo "Coping files to remote host" 
        $0 lib
        $0 bin
        $0 test
        $0 include
        echo " done."
        ;;
    esac

    
else
    echo "Nothing to do on $(uname -n)"
fi
