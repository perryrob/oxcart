#!/bin/bash

function copy_bin {
    scp -q ${SRC_DIR}/build/apps/oxalgos ${REMOTE}:${DST_DIR}/bin/.
    echo "cp -> ${SRC_DIR}/build/apps/oxalgos ${REMOTE}:${DST_DIR}/bin/."
    scp -q ${SRC_DIR}/build/apps/oxcart_d ${REMOTE}:${DST_DIR}/bin/.
    echo "cp -> ${SRC_DIR}/build/apps/oxcart_d ${REMOTE}:${DST_DIR}/bin/."
    scp -q ${SRC_DIR}/build/apps/oxclient ${REMOTE}:${DST_DIR}/bin/.
    echo "cp -> ${SRC_DIR}/build/apps/oxclient ${REMOTE}:${DST_DIR}/bin/."
    scp -q ${SRC_DIR}/apps/ox.sh ${REMOTE}:${DST_DIR}/bin/.
    echo "cp -> ${SRC_DIR}/apps/ox.sh ${REMOTE}:${DST_DIR}/bin/."
}

function copy_lib {
    scp -q ${SRC_DIR}/build/src/*.so ${REMOTE}:${DST_DIR}/lib/.
    echo "cp -> ${SRC_DIR}/build/src/*.so ${REMOTE}:${DST_DIR}/lib/."
    scp -q ${SRC_DIR}/build/src/algo/*.so ${REMOTE}:${DST_DIR}/lib/.
    echo "cp -> ${SRC_DIR}/build/src/algo/*.so ${REMOTE}:${DST_DIR}/lib/."
    scp -q ${SRC_DIR}/build/src/devices/*.so ${REMOTE}:${DST_DIR}/lib/.
    echo "cp -> ${SRC_DIR}/build/src/devices*.so ${REMOTE}:${DST_DIR}/lib/."
}

function copy_test {
    scp -rq ${SRC_DIR}/build/test ${REMOTE}:${DST_DIR}/.
    echo "cp -> ${SRC_DIR}/build/test ${REMOTE}:${DST_DIR}/."
}
function copy_include {
    scp -rq ${SRC_DIR}/include/* ${REMOTE}:${DST_DIR}/include/.
    echo "cp -> ${SRC_DIR}/include/* ${REMOTE}:${DST_DIR}/include/."
}

function copy_data {
    scp -rq ${SRC_DIR}/include/* ${REMOTE}:${DST_DIR}/data/.
    echo "cp -> ${SRC_DIR}/include/* ${REMOTE}:${DST_DIR}/data/."
}


if [ "$(uname -n)" = "wildcat" ]; then

    DST_DIR=/home/perryr/oxcart

    SRC_DIR=/home/perryr/proj/oxcart

    REMOTE=bone
    
    case "$1" in
    ninja)
        . ./env.sh
        pushd ${SRC_DIR}/build
        ninja -j 8
        popd
        ;;
    clean)
        pushd ${SRC_DIR}
        pushd build
        rm -rf *
        popd
        . ./env.sh
        meson build --cross-file cross_file.txt
        popd
        ;;
    lib)
        if ! [ -z ${AUTO_RESTART+x} ]; then 
            echo "Stopping remote apps..."
            ssh $REMOTE '/home/perryr/oxcart/bin/ox.sh stop' > /dev/null 2>&1
        fi
    
        copy_lib
   
        if ! [ -z ${AUTO_RESTART+x} ]; then 
            ssh $REMOTE '/home/perryr/oxcart/bin/ox.sh start' > /dev/null 2>&1
            echo "Start remote apps..."
        fi
        ;;
    bin)
        if ! [ -z ${AUTO_RESTART+x} ]; then 
            echo "Stopping remote apps..."
            ssh $REMOTE '/home/perryr/oxcart/bin/ox.sh stop' > /dev/null 2>&1
        fi
        
        copy_bin

        if ! [ -z ${AUTO_RESTART+x} ]; then 
            ssh $REMOTE '/home/perryr/oxcart/bin/ox.sh start' > /dev/null 2>&1
            echo "Start remote apps..."
        fi
        ;;
     test)
        copy_test
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
    arduino_monitor)
        pushd ${SRC_DIR}/arduino
        . ./env/bin/activate
        pushd oxcart
        platformio device monitor
        deactivate
        popd
        popd
        ;;
    upgrade)
        UPGRADE_DIR=/tmp/oxcart
        UPGRADE_FILE=OXCART.tar.gz
        mkdir -p ${UPGRADE_DIR}/bin
        mkdir -p ${UPGRADE_DIR}/lib
        mkdir -p ${UPGRADE_DIR}/include
        mkdir -p ${UPGRADE_DIR}/data
        mkdir -p ${UPGRADE_DIR}/test
        DST_DIR=${UPGRADE_DIR}
        REMOTE=localhost
        copy_lib
        copy_bin
        copy_include
        copy_test
        pushd /tmp
        /bin/tar cfz ${UPGRADE_FILE} oxcart
        rm -rf ${UPGRADE_DIR}
        popd
        cp /tmp/${UPGRADE_FILE} ${SRC_DIR}/.
        echo "Upgrade file ${SRC_DIR}/${UPGRADE_FILE}... ready"
        ;;
    include)
        copy_include
        ;;
    *)
        $0 clean
        $0 ninja
        echo "Coping files to remote host" 
        $0 lib
        $0 bin
        $0 test
        $0 include
        $0 upgrade
        echo " done."
        ;;
    esac

    
else
    echo "Nothing to do on $(uname -n)"
fi
