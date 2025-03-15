#pragma once

#include "libs.h"

class BaseFile {
public:
    BaseFile(); 
    BaseFile(const char* path, const char* mode); 
    explicit BaseFile(FILE* f);  
    virtual ~BaseFile();

    bool is_open() const;
    bool can_read() const;
    bool can_write() const;
    size_t write_raw(const void* buf, size_t n_bytes);
    size_t read_raw(void* buf, size_t max_bytes);
    long tell() const;
    bool seek(long offset);
	bool close();

    virtual size_t write(const void* buf, size_t n_bytes) { return write_raw(buf, n_bytes); }
    virtual size_t read(void* buf, size_t max_bytes) { return read_raw(buf, max_bytes); }

private:
    FILE* file;       
    bool owns_file;   
    const char* mode; 
};

// класс для работы с текстовыми файлами
class TextFile : public BaseFile {
public:
    TextFile(const char* path, const char* mode) : BaseFile(path, mode) {}
    ~TextFile() = default;

    void write_line(const char* line);
    size_t read_line(char* buffer, size_t buffer_size); 
};

// класс для только-чтения файлов
class ReadOnlyFile : public BaseFile {
public:
    ReadOnlyFile(const char* path) : BaseFile(path, "r") {}
    ~ReadOnlyFile() = default;

    size_t write_raw(const void*, size_t) {
        std::cerr << "Write operation not allowed in ReadOnlyFile\n";
        return 0;
    }

    size_t write(const void*, size_t) { return 0; }
};
