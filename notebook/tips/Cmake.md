# Cmake tips

## 1 常用命令
```cmake
cmake_minimum_required(VERSION 2.6) #cmake版本
set(CXX_FLAGS -g) #设置编译选项
add_definitions(-DSUBSYS_NAME=LOCAL_SYSMGR) #添加宏
include_directories(./include) #添加头文件目录
file(GLOB_RECURSE local_sys_statemachine_SRCS 
    ../centre_sysmgr/src/*.cpp 
    ./*.cpp) #添加源文件
add_executable(local_sysmgr ${local_sys_statemachine_SRCS}) #编译可执行
add_library(sysmgr SHARED ${SOURCES}) #编译.so 
target_link_libraries(sysmgr
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../third_party/zmq/libzmq.a
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../third_party/android/libalog.so
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../third_party/json/libjsoncpp.a
        libpthread.so
) #添加三方库
```