#pragma once

#include "libs.h"

class MyString {
private:
    char* data;   // Указатель на динамически выделенную память
    int length; // Длина строки без завершающего нуля

public:
    // Конструкторы
    MyString(); // Пустая строка
    MyString(const char* str); // Строка из C-строки
	MyString(int length, char fill_char);
	MyString(const MyString &str);

	MyString& operator=(const MyString &str);

    // Деструктор
    ~MyString();

    // Методы
    char get(int i) const;
    void set(int i, char c);
    void set_new_string(const char* str);
    void print(const char *end="\n") const;
    void read_line();
	void read_line2();

    // Геттер длины строки
    int get_length() const { return length; }
};
