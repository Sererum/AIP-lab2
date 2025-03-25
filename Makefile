COMPILER = g++
COMPILER_FLAGS = -Isrc -Wall -Wextra -std=c++17 #-Werror
OBJECTS = build/release/lab2.o build/release/my_string.o build/release/base_file.o build/release/file32.o build/release/file32_2.o build/release/rle_file.o build/release/rle_file_2.o

build/release/output.out: $(OBJECTS)
	$(COMPILER) $(COMPILER_FLAGS) -o build/release/output.out $(OBJECTS)

build/release/lab2.o: src/lab2.cpp
	$(COMPILER) $(COMPILER_FLAGS) -o build/release/lab2.o -c src/lab2.cpp

build/release/my_string.o: src/my_string/my_string.cpp
	$(COMPILER) $(COMPILER_FLAGS) -o build/release/my_string.o -c src/my_string/my_string.cpp

build/release/base_file.o: src/base_file/base_file.cpp 
	$(COMPILER) $(COMPILER_FLAGS) -o build/release/base_file.o -c src/base_file/base_file.cpp
	
build/release/file32.o: src/file32/file32.cpp 
	$(COMPILER) $(COMPILER_FLAGS) -o build/release/file32.o -c src/file32/file32.cpp

build/release/file32_2.o: src/file32/file32_2.cpp 
	$(COMPILER) $(COMPILER_FLAGS) -o build/release/file32_2.o -c src/file32/file32_2.cpp

build/release/rle_file.o: src/rle_file/rle_file.cpp 
	$(COMPILER) $(COMPILER_FLAGS) -o build/release/rle_file.o -c src/rle_file/rle_file.cpp

build/release/rle_file_2.o: src/rle_file/rle_file_2.cpp 
	$(COMPILER) $(COMPILER_FLAGS) -o build/release/rle_file_2.o -c src/rle_file/rle_file_2.cpp

.PHONY: run
run: build/release/output.out
	build/release/output.out

.PHONY: clean
clean:
	rm -rf build/release/*
	rm -rf build/debug/*
	# rm build/leaks

DEBUG_FLAGS = $(COMPILER_FLAGS) -g -O0
DEBUG_OBJECTS = build/debug/debug_lab2.o build/debug/debug_my_string.o build/debug/debug_base_file.o build/debug/debug_file32.o build/debug/debug_file32_2.o  build/debug/debug_rle_file.o build/debug/debug_rle_file_2.o

build/debug/debug.out: $(DEBUG_OBJECTS)
	$(COMPILER) $(DEBUG_FLAGS) -o build/debug/debug.out $(DEBUG_OBJECTS)

build/debug/debug_lab2.o: src/lab2.cpp
	$(COMPILER) $(DEBUG_FLAGS) -o build/debug/debug_lab2.o -c src/lab2.cpp

build/debug/debug_my_string.o: src/my_string/my_string.cpp
	$(COMPILER) $(DEBUG_FLAGS) -o build/debug/debug_my_string.o -c src/my_string/my_string.cpp

build/debug/debug_base_file.o: src/base_file/base_file.cpp 
	$(COMPILER) $(DEBUG_FLAGS) -o build/debug/debug_base_file.o -c src/base_file/base_file.cpp
	
build/debug/debug_file32.o: src/file32/file32.cpp 
	$(COMPILER) $(DEBUG_FLAGS) -o build/debug/debug_file32.o -c src/file32/file32.cpp

build/debug/debug_file32_2.o: src/file32/file32_2.cpp 
	$(COMPILER) $(DEBUG_FLAGS) -o build/debug/debug_file32_2.o -c src/file32/file32_2.cpp

build/debug/debug_rle_file.o: src/rle_file/rle_file.cpp 
	$(COMPILER) $(DEBUG_FLAGS) -o build/debug/debug_rle_file.o -c src/rle_file/rle_file.cpp

build/debug/debug_rle_file_2.o: src/rle_file/rle_file_2.cpp 
	$(COMPILER) $(DEBUG_FLAGS) -o build/debug/debug_rle_file_2.o -c src/rle_file/rle_file_2.cpp

.PHONY: debug
debug: build/debug/debug.out
	gdb build/debug/debug.out

build/leaks.out: $(DEBUG_OBJECTS)
	$(COMPILER) $(DEBUG_FLAGS) -fsanitize=address -o build/leaks.out $(DEBUG_OBJECTS) 

.PHONY: leaks
leaks: build/leaks.out
	build/leaks.out
