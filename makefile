.PHONY: build clean

CC = g++
CFLAGS = -std=c++17

SOURCE_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
OBJ_DIR = obj

SOURCES = main.cpp database.cpp
OBJECTS = $(SOURCES:.cpp=.o)

build: simple_db

simple_db: main.o database.o
	[ -d $(BUILD_DIR) ] || mkdir -p $(BUILD_DIR)
	$(CC) -I$(INCLUDE_DIR) $(OBJ_DIR)/main.o $(OBJ_DIR)/database.o -o $(BUILD_DIR)/$@ $(CFLAGS)

main.o: $(SOURCE_DIR)/main.cpp
	[ -d $(OBJ_DIR) ] || mkdir -p $(OBJ_DIR)
	$(CC) -I$(INCLUDE_DIR) -c $< -o $(OBJ_DIR)/$@ $(CFLAGS)

database.o: $(SOURCE_DIR)/database.cpp
	[ -d $(OBJ_DIR) ] || mkdir -p $(OBJ_DIR)
	$(CC) -I$(INCLUDE_DIR) -c $< -o $(OBJ_DIR)/$@ $(CFLAGS)

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(OBJ_DIR)
