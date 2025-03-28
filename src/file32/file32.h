#pragma once

#include "base_file/base_file.h" // Включаем базовый класс
#include "libs.h"

// Таблица кодировки по умолчанию (из lab4)
extern const char default_alphabet[32];

class Base32File : public BaseFile {
public:
    // принимает путь, режим и таблицу кодировки (по умолчанию default_alphabet)
    Base32File(const char* path, const char* mode, const char* alphabet = default_alphabet); 

    size_t write(const void* buf, size_t n_bytes) override;
    size_t read(void* buf, size_t max_bytes) override;

private:
	int encoded32_size(int raw_size) const;
	int decoded32_size(int raw_size) const;

	int encode32(const char* raw_data, int raw_size, char* dst) const;
 	int decode32(const char *encoded_data, int encoded_size, char *dst) const; 
	
    const char* alphabet; // Таблица кодировки
};

