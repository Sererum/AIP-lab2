#include "my_string.h"

MyString::MyString() : data(new char[1]), length(0) {
    data[0] = '\0'; // Инициализируем пустой символ
}

// Конструктор с параметром (копирование C-строки)
MyString::MyString(const char* str) {
    if (!str) {
        data = new char[1];
        data[0] = '\0';
        length = 0;
    } else {
        length = std::strlen(str);
        data = new char[length + 1]; // +1 для завершающего нуля
        std::strcpy(data, str); // Копируем строку и встравляем '\0'
    }
}

MyString::MyString(int length, char fill_char) : length(length) {
	if (length < 0) 
        throw std::out_of_range("Index out of range.");

	data = new char[length + 1]; 
	for (int i = 0; i < length; ++i)
		data[i] = fill_char;
    data[length] = '\0'; 
}

MyString::MyString(const MyString &str) : data(nullptr), length(str.length) {
	*this = str;
}

MyString& MyString::operator=(const MyString &str) {
	if (this == &str)
		return *this;

	delete[] data;
	
	length = str.length;
	data = new char[length + 1];
	std::strcpy(data, str.data);

	return *this;
}

// Деструктор
MyString::~MyString() {
    delete[] data; // Освобождаем память
}

// Получение символа по индексу
char MyString::get(int i) const {
    if (i < 0 || i >= length) {
        throw std::out_of_range("Index out of range.");
    }
    return data[i];
}

// Установка символа по индексу
void MyString::set(int i, char c) {
    if (i < 0 || i >= length) {
        throw std::out_of_range("Index out of range.");
    }
    data[i] = c;
}

// Замена текущего содержимого на новое
void MyString::set_new_string(const char* str) {
    if (!str) {
        delete[] data;
        data = new char[1];
        data[0] = '\0';
        length = 0;
        return;
    }

    int new_length = std::strlen(str);
    if (new_length != length) {
        delete[] data; // Освобождаем старую память
        data = new char[new_length + 1]; // Выделяем новую память
    }
    std::strcpy(data, str); // Копируем новую строку
    length = new_length;
}

// Вывод строки на консоль
void MyString::print(const char *end) const {
    std::cout << data << end;
}

// Считывание строки с консоли
void MyString::read_line() {
    // Очищаем старые данные
    delete[] data;

    // Буфер для чтения строки
    const int buffer_size = 1024;
    char buffer[buffer_size];

    // Считываем строку
    std::cin.getline(buffer, buffer_size);

    // Создаем новую строку
    length = std::strlen(buffer);
    data = new char[length + 1];
    std::strcpy(data, buffer);
}

void MyString::read_line2() {
	delete[] data;

	int i = 0, capacity = 4;
	char next_char;
	char *str = new char[capacity + 1];

	std::cout << "Введите новую строчку: "; 

	while ((next_char = getchar()) != '\n') {
		str[i++] = next_char;

		if (i >= capacity) {
			str[capacity] = '\0';
			capacity *= 2;
			char *temp = new char[capacity + 1];

			std::strcpy(temp, str);

			delete[] str;
			str = temp;
		}
	}
	str[i] = '\0';
	std::cout << str << std::endl;

	data = new char[i + 1];
	length = i;
	std::strcpy(data, str);
	delete[] str;
}

