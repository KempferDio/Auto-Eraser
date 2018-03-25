CC = g++

INCLUDE = include
LIB = lib
OBJ = obj
SRC = src

TARGET = bin/AutoEraser

SRCS = $(wildcard $(SRC)/*.cpp)
OBJS = $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))

CFLAGS = -c -Wall -std=gnu++17
LFLAGS = -lstdc++fs 
DELETE = find . -name "*.o" -type f -delete



ifeq ($(OC), Windows_NT)
	DELETE = del /S *.o
endif

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $^ $(LFLAGS)  -o $@

$(OBJ)/%.o : $(SRC)/%.cpp
	$(CC) $< -I$(INCLUDE) $(CFLAGS)  -o $@

clear :
	$(DELETE)

.PHONY: all clear