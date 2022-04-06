# CXX = g++
CXX = $(CROSS_COMPILE)g++
AR = $(CROSS_COMPILE)ar
CXXFLAGS   = -std=c++14 -fpermissive --coverage -g
INCLUDE    = -I/home/tangpei/sysmgr/new_repo/hbre/sys-mgr/master_control/src/system_statemachine/sysmgr_lib/ -I ../utils
LDFLAGS    = -L/home/tangpei/sysmgr/new_repo/hbre/sys-mgr/master_control/build/lib
LIBS 	   = -Bstatic -lrt -ldl -lpthread -Bdynamic

SRCS      := main.cpp
TARGET    := main

all:
	$(foreach file, $(SRCS),\
		$(CXX) -o $(patsubst  %.cpp, %, $(file)) $(CXXFLAGS) $(file) $(INCLUDE) $(LDFLAGS) $(LIBS);)

clean:
	$(foreach file, $(SRCS),\
		rm -rf $(patsubst  %.cpp, %, $(file));)


ubuntu:
	$(foreach file, $(SRCS),\
		g++ -o $(patsubst  %.cpp, %, $(file)) $(CXXFLAGS) $(file) $(INCLUDE) $(LDFLAGS) $(LIBS) -DUBUNTU;)
