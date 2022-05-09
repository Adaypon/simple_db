.PHONY: build clean

CC = g++
CFLAGS = -std=c++17

SOURCE_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
OBJ_DIR = obj

build: simple_db

simple_db: main.o
	[ -d $(BUILD_DIR) ] || mkdir -p $(BUILD_DIR)
	$(CC) -I$(INCLUDE_DIR) $(OBJ_DIR)/$< -o $(BUILD_DIR)/$@ $(CFLAGS)

main.o: $(SOURCE_DIR)/main.cpp
	[ -d $(OBJ_DIR) ] || mkdir -p $(OBJ_DIR)
	$(CC) -I$(INCLUDE_DIR) -c $< -o $(OBJ_DIR)/$@ $(CFLAGS)

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(OBJ_DIR)
