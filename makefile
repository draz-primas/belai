flagslink   := 
flagsbuild  := -Wall -Wextra -Wpedantic -Iinclude
source_dirs := src
objects := $(patsubst %.c, build/%.o, \
$(foreach dir, $(source_dirs), $(wildcard $(dir)/*.c)))
CC := cc
TARGET := belai

.PHONY: all release debug clean export-compile-flags init

grafika:
	make clean release flagsbuild="-Iinclude -DRENDER" flagslink="-lSDL2 -lSDL2_image"

all: $(objects)
	$(CC) $(objects) -o $(TARGET) $(flagslink) && ./$(TARGET)

release: $(patsubst %.o, %-O3.o, $(objects))
	$(CC) $(patsubst %.o, %-O3.o, $(objects)) -o $(TARGET) -O3 $(flagslink)

debug: $(patsubst %.o, %-g.o, $(objects))
	$(CC) $(patsubst %.o, %-g.o, $(objects)) -o $(TARGET) -g -fsanitize=address $(flagslink)

build/%.o:: %.c
	$(CC) -c $< -o $@ $(flagsbuild)

build/%-O3.o:: %.c
	$(CC) -c $< -o $@ $(flagsbuild) -O3

build/%-g.o:: %.c
	$(CC) -c $< -o $@ $(flagsbuild) -g -fsanitize=address

clean:
	rm -rf build
	mkdir -p build
	mkdir -p $(foreach dir, $(source_dirs), build/$(dir))

export-compile-flags:
	echo "$(flagsbuild) $(flagslink)" | tr -s '[:space:]' '\n' > compile_flags.txt

init:
	mkdir -p build
	mkdir -p $(foreach dir, $(source_dirs), build/$(dir))
	mkdir -p $(foreach dir, $(source_dirs), $(dir))
