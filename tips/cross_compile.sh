COMPILER_ROOT="/data/tangpei/new_repo/prebuilts/host/gcc-linaro-6.5.0-2018.12-x86_64_aarch64-linux-gnu/bin/"
PREPATH=${PWD}
export PATH=$PATH:${COMPILER_ROOT}
export CC=${COMPILER_ROOT}aarch64-linux-gnu-gcc
export CXX=${COMPILER_ROOT}aarch64-linux-gnu-g++
export CPP=${COMPILER_ROOT}'aarch64-linux-gnu-g++ -E'
export AR=${COMPILER_ROOT}aarch64-linux-gnu-ar

chmod +x configure
rm ${PREPATH}/Output -rf
mkdir ${PREPATH}/Output

./configure \
    CC=$CC \
    --host=aarch64-linux-gnu \
    --prefix=${PREPATH}/Output

make;
make install;