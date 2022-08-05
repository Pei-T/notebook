# Copyright (C) Horizon Robotics, Inc. - All Rights Reserved
# Unauthorized copying of this file, via any medium is strictly prohibited
# Proprietary and confidential

ROOTDIR    = ./
CXX        = $(CROSS_COMPILE)g++
CXXFLAGS   = -std=c++14 -g -Wall
INCLUDE    = -I$(ROOTDIR)
LDFLAGS    = -L$(ROOTDIR)
LIBS       = -lpthread

TARGET = test

all:
	$(CXX) *.cpp -o $(TARGET) $(CXXFLAGS) $(file) $(INCLUDE) $(LDFLAGS) $(LIBS);

clean:
	rm $(TARGET)