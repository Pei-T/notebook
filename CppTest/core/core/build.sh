#!/bin/bash

function all() {
	# install path
	install_prefix=$TARGET_TMPROOTFS_DIR/usr

	echo "core build script...."
    echo "CROSS_COMPILE: $CROSS_COMPILE"
    echo "TOOLCHAIN_DIR: ${SRC_HOST_DIR}/${TOOLCHAIN_NAME}"
    echo "TARGET_MODE: $TARGET_MODE"
    echo "ARCH: $ARCH" 
    echo "Install_prefix: $install_prefix"
    echo "out path: $TARGET_OUT_DIR"

    xmake f -p cross -a $ARCH -m $TARGET_MODE --sdk=${SRC_HOST_DIR}/${TOOLCHAIN_NAME} -o $TARGET_OUT_DIR/build/core
    xmake
    xmake install
}

function all_32() {
    all
}

function clean() {
    # make clean here
    echo "clean core done"
    xmake clean
    xmake f --clean
    rm -rf $TARGET_OUT_DIR/build/core/
}

# include utils func
. $INCLUDE_FUNCS
# include end

## you can add dependon module name
dependon third_party

cd $(dirname $0)
buildopt $1
