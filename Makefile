COMPILER = g++
COMPILER_FLAGS = -Isrc -Werror -Wall -Wextra -std=c++17
OBJECTS = build/lab2.o build/my_string.o build/base_file.o build/file32.o

build/output: $(OBJECTS)
	$(COMPILER) $(COMPILER_FLAGS) -o build/output $(OBJECTS)

build/lab2.o: src/lab2.cpp
	$(COMPILER) $(COMPILER_FLAGS) -o build/lab2.o -c src/lab2.cpp

build/my_string.o: src/my_string/my_string.cpp
	$(COMPILER) $(COMPILER_FLAGS) -o build/my_string.o -c src/my_string/my_string.cpp

build/base_file.o: src/base_file/base_file.cpp 
	$(COMPILER) $(COMPILER_FLAGS) -o build/base_file.o -c src/base_file/base_file.cpp
	
build/file32.o: src/file32/file32.cpp 
	$(COMPILER) $(COMPILER_FLAGS) -o build/file32.o -c src/file32/file32.cpp

.PHONY: run
run: build/output
	build/output

.PHONY: clean
clean:
	rm -rf build/*
