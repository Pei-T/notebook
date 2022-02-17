CXX        = /usr/bin/g++
CXXFLAGS   = -std=c++14 -fpermissive --coverage
INCLUDE    = -I/usr/include
LDFLAGS    = -L/usr/lib
LIBS 	   = -Bstatic -lrt -ldl -lpthread -Bdynamic 

SRCS      := main.cpp
TARGET    := main

all:
	$(foreach file, $(SRCS),\
		$(CXX) -o $(patsubst  %.cpp, %, $(file)) $(CXXFLAGS) $(file) $(INCLUDE) $(LDFLAGS) $(LIBS);)

clean:
	$(foreach file, $(SRCS),\
		rm -rf $(patsubst  %.cpp, %, $(file));)

install:
	$(foreach file, $(SRCS),\
		install $(patsubst  %.cpp, %, $(file)) ../output/;)
