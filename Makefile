COMPILER = g++
COMPILER_FLAGS = -Isrc -Werror -Wall -Wextra -std=c++17
OBJECTS = build/lab2.o build/base.o # build/base32.o

build/output: $(OBJECTS)
	$(COMPILER) $(COMPILER_FLAGS) -Ibase -o build/output $(OBJECTS)

build/lab2.o: src/lab2.cpp
	$(COMPILER) $(COMPILER_FLAGS) -Isrc/base -o build/lab2.o -c src/lab2.cpp

build/base.o: src/base/BaseFile.cpp 
	$(COMPILER) $(COMPILER_FLAGS) -o build/base.o -c src/base/BaseFile.cpp
	
build/base32.o: src/base32/Base32File.cpp build/base.o
	$(COMPILER) $(COMPILER_FLAGS) -Isrc/base -o build/base32.o -c src/base32/Base32File.cpp build/base.o

.PHONY: run
run: build/output
	build/output

.PHONY: clean
clean:
	rm -rf build/*
