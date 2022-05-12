CC = $(CROSS_COMPILE)g++
AR = $(CROSS_COMPILE)ar

OUT_DIR = obj
BIN_DIR = .
SRC_DIR = .
INC_DIR = ../utils
# LIB_DIR = ../LibTest
LIB_DIR = .
LIBS = -Bstatic  -lpthread -Bdynamic
CFLAGS =  -g -Wall -I${INC_DIR}
LDFLAGS = -L${LIB_DIR}

TARGET = main

.PHONY: directories default all clean

MKDIR_P = mkdir -p
default: directories ${BIN_DIR}/$(TARGET) Makefile
directories: ${OUT_DIR} ${BIN_DIR}
all: directories default

${OUT_DIR}:
	${MKDIR_P} ${OUT_DIR}

${BIN_DIR}:
	${MKDIR_P} ${BIN_DIR}

SOURCES = $(wildcard ${SRC_DIR}/*.cpp)
SOURCE_FILES = $(notdir ${SOURCES})
OBJECTS = $(patsubst ${SRC_DIR}/%.cpp,${OUT_DIR}/%.o, ${SOURCES})
HEADERS = $(wildcard ${INC_DIR}/*.h)

${OUT_DIR}/%.o: ${SRC_DIR}/%.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

${BIN_DIR}/$(TARGET): $(OBJECTS)
	@echo "Start to build..."
	$(CC) $(OBJECTS) ${LDFLAGS} -Wall $(LIBS) -o $@

clean:
	-rm -f ${OUT_DIR}/*.o
	-rm -f ${BIN_DIR}/$(TARGET)
