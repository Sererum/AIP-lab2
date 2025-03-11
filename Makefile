COMPILER = g++
COMPILER_FLAGS = -Isrc -Werror -Wall -Wextra -std=c++17
OBJECTS = build/lab2.o build/my_string.o build/base.o build/base32.o

build/output: $(OBJECTS)
	$(COMPILER) $(COMPILER_FLAGS) -o build/output $(OBJECTS)

build/lab2.o: src/lab2.cpp
	$(COMPILER) $(COMPILER_FLAGS) -o build/lab2.o -c src/lab2.cpp

build/my_string.o: src/my_string/my_string.cpp
	$(COMPILER) $(COMPILER_FLAGS) -o build/my_string.o -c src/my_string/my_string.cpp

build/base.o: src/base/base_file.cpp 
	$(COMPILER) $(COMPILER_FLAGS) -o build/base.o -c src/base/base_file.cpp
	
build/base32.o: src/base32/base_32_file.cpp 
	$(COMPILER) $(COMPILER_FLAGS) -o build/base32.o -c src/base32/base_32_file.cpp

.PHONY: run
run: build/output
	build/output

.PHONY: clean
clean:
	rm -rf build/*
