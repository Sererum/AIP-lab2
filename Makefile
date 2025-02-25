# Флаги компиляции
COMPILER = g++ 
COMPILE_FLAGS = -Isrc -Wall -Wextra -Werror -std=c++17

OBJECTS = build/lab2.o build/my_string.o #build/rect.o build/barrel.o build/matrix.o  build/text_wrapper.o  

# Целевой исполняемый файл
build/output: $(OBJECTS)
	$(COMPILER) $(COMPILE_FLAGS) -o build/output $(OBJECTS)
	
# Компиляция исходников в объектные файлы
build/lab2.o: src/lab2.cpp
	$(COMPILER) $(COMPILE_FLAGS) -c src/lab2.cpp -o build/lab2.o

build/my_string.o: src/my_string/my_string.cpp src/my_string/my_string.h
	$(COMPILER) $(COMPILE_FLAGS) -c src/my_string/my_string.cpp -o build/my_string.o

# build/rect.o: src/rect/rect.cpp src/rect/rect.h
# 	$(COMPILER) $(COMPILE_FLAGS) -c src/rect/rect.cpp -o build/rect.o 
# 
# build/barrel.o: src/barrel/barrel.cpp src/barrel/barrel.h
# 	$(COMPILER) $(COMPILE_FLAGS) -c src/barrel/barrel.cpp -o build/barrel.o
# 
# build/matrix.o: src/matrix/matrix.cpp src/matrix/matrix.h
# 	$(COMPILER) $(COMPILE_FLAGS) -c src/matrix/matrix.cpp -o build/matrix.o
# 
# build/text_wrapper.o: src/text_wrapper/text_wrapper.cpp src/text_wrapper/text_wrapper.h build/my_string.o
# 	$(COMPILER) $(COMPILE_FLAGS) -c src/text_wrapper/text_wrapper.cpp -o build/text_wrapper.o

# Дебаг-сборка
build/debug: $(OBJECTS)
	$(COMPILER) -g $(COMPILE_FLAGS) -o build/debug $(OBJECTS) 

# Сборка для проверки утечек
build/leaks: $(OBJECTS)
	$(COMPILER) -g -fsanitize=address $(COMPILE_FLAGS) -o build/leaks $(OBJECTS) 

# Запуск скомпилированной программы 
.PHONY: run 
run: build/output
	./build/output

# Запуск отладчика после дебаг-сборки
.PHONY: debug
debug: build/debug
	gdb build/debug

# Запуск сборки для проверки утечек
.PHONY: leaks
leaks: build/leaks
	./build/leaks

# Очистка
.PHONY: clean
clean:
	rm -rf build/*

# Компиляция тестов
# build/test_rect_basic_methods.out: tests/test_rect_basic_methods.cpp build/rect.o
# 	$(COMPILER) $(COMPILE_FLAGS) -o build/test_rect_basic_methods.out tests/test_rect_basic_methods.cpp build/rect.o
# 
# build/test_rect_properties.out: tests/test_rect_properties.cpp build/rect.o
# 	$(COMPILER) $(COMPILE_FLAGS) -o build/test_rect_properties.out tests/test_rect_properties.cpp build/rect.o
# 
# build/test_rect_operations.out: tests/test_rect_operations.cpp build/rect.o
# 	$(COMPILER) $(COMPILE_FLAGS) -o build/test_rect_operations.out tests/test_rect_operations.cpp build/rect.o
# 
# build/test_bounding_rect.out: tests/test_bounding_rect.cpp build/rect.o 
# 	$(COMPILER) $(COMPILE_FLAGS) -o build/test_bounding_rect.out tests/test_bounding_rect.cpp build/rect.o 
# 
# # Запуск всех тестов
# .PHONY: all_tests
# all_tests: build/test_rect_basic_methods.out build/test_rect_properties.out build/test_rect_operations.out build/test_bounding_rect.out
# 	@./build/test_rect_basic_methods.out
# 	@./build/test_rect_properties.out
# 	@./build/test_rect_operations.out
# 	@./build/test_bounding_rect.out

