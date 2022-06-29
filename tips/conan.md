# conan安装库
## conan install
新建conanfile.txt
```
[requires]
libssh2/1.10.0
[imports]
include, * -> ./include
lib, * -> ./lib
```
conan install .
## connect search
```sh
conan search jsoncpp -r=conancenter
```
## conan cross compile
设置交叉编译器
export CROSS_COMPILER_PREFIX=/home/tangpei/CrossCompile/prebuilts/host/gcc-linaro-6.5.0-2018.12-x86_64_aarch64-linux-gnu

设置下面Cmake的环境
export CONAN_CMAKE_TOOLCHAIN_FILE=...

运行命令
conan install . --build jsoncpp
```cmake
# This one is important
SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_PROCESSOR arm)

set(_compiler_prefix "${_compiler_prefix}")
if(NOT EXISTS ${_compiler_prefix})
        if(NOT $ENV{CROSS_COMPILER_PREFIX} STREQUAL "")
            set(_compiler_prefix $ENV{CROSS_COMPILER_PREFIX})
        elseif(CROSS_COMPILER_PREFIX)
            set(_compiler_prefix ${CROSS_COMPILER_PREFIX})
        else()
                find_program(_armcc_path armcc)
                if(NOT _armcc_path)
                        message(FATAL_ERROR "NOT FOUND compiler armcc in system path")
                endif()
                get_filename_component(_bin ${_armcc_path} DIRECTORY )
                get_filename_component(_compiler_prefix ${_bin} DIRECTORY )
        endif()
endif()
set(_suffix)
if(WIN32)
        set(_suffix .exe)
endif()

#INCLUDE(CMakeForceCompiler)

# Specify the cross compiler
#SET(CMAKE_C_COMPILER "${_compiler_prefix}/bin/armcc${_suffix}")
#SET(CMAKE_CXX_COMPILER "${_compiler_prefix}/bin/armcc${_suffix}")
#SET(CMAKE_AR "${_compiler_prefix}/bin/armar${_suffix}" CACHE FILEPATH "Archiver")

SET(CMAKE_C_COMPILER "${_compiler_prefix}/bin/aarch64-linux-gnu-gcc${_suffix}")
SET(CMAKE_CXX_COMPILER "${_compiler_prefix}/bin/aarch64-linux-gnu-g++${_suffix}")
#CMAKE_C_COMPILER("${_compiler_prefix}/sw/gcc/bin/arm-linux-gnueabihf-gcc${_suffix}" GNU)
#CMAKE_CXX_COMPILER ("${_compiler_prefix}/sw/gcc/bin/arm-linux-gnueabihf-g++${_suffix}" GNU)

UNSET(CMAKE_C_FLAGS CACHE)
#SET(CMAKE_C_FLAGS "--cpu=Cortex-A9 --thumb -Ospace" CACHE STRING "" FORCE)
UNSET(CMAKE_CXX_FLAGS CACHE)
#SET(CMAKE_CXX_FLAGS ${CMAKE_C_FLAGS} CACHE STRING "" FORCE)
UNSET(CMAKE_EXE_LINKER_FLAGS CACHE)
#SET(CMAKE_EXE_LINKER_FLAGS "" CACHE STRING "" FORCE)
UNSET(CMAKE_AR_FLAGS CACHE)
#SET(CMAKE_AR_FLAGS "-p -armcc,-Ospace" CACHE STRING "" FORCE)

# set(CMAKE_C_ARCHIVE_CREATE "<CMAKE_AR> cr <TARGET> <LINK_FLAGS> <OBJECTS>")
#SET(CMAKE_C_ARCHIVE_CREATE "<CMAKE_AR> ${CMAKE_AR_FLAGS} -o <TARGET> <OBJECTS>" CACHE STRING "C Archive Create")
# set(CMAKE_CXX_ARCHIVE_CREATE "<CMAKE_AR> cr <TARGET> <LINK_FLAGS> <OBJECTS>")
#SET(CMAKE_CXX_ARCHIVE_CREATE "<CMAKE_AR> ${CMAKE_AR_FLAGS} -o <TARGET> <OBJECTS>" CACHE STRING "CXX Archive Create")

#include_directories("${_compiler_prefix}/include")
include_directories("${_compiler_prefix}/aarch64-linux-gnu/include")

# Where is the target environment
SET(CMAKE_FIND_ROOT_PATH "${_compiler_prefix}/aarch64-linux-gnu/libc")

# Search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# For libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

unset(_compiler_prefix)
```
