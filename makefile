CC = g++

INCLUDE = include
LIB = lib
OBJ = obj
SRC = src

TARGET = bin/AutoEraser

SRCS = $(wildcard $(SRC)/*.cpp)
OBJS = $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))

CFLAGS = -c -Wall -std=gnu++17 -DDEBUG
LFLAGS = -lstdc++fs 


UNAME = $(shell uname)

ifeq ($(UNAME), Windows_NT)
	CFLAGS += -DWINDOWS
	DELETE = del /S *.o
endif

ifeq ($(UNAME), Linux)
	CFLAGS += -DLINUX
	DELETE = find . -name "*.o" -type f -delete
endif


all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $^ $(LFLAGS) -o $@

$(OBJ)/%.o : $(SRC)/%.cpp
	$(CC) $< -I$(INCLUDE) $(CFLAGS) -o $@

clear :
	$(DELETE)

.PHONY: all clear os