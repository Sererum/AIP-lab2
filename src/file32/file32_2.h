#pragma once

#include "libs.h"
#include "base_file/ifile.h"
#include "file32.h"

class Base32File2 : public IFile {
private:
    IFile* file;
    const char* alphabet;

public:
    Base32File2(IFile* ifile, const char* alphabet = default_alphabet);
    ~Base32File2();

    bool is_open() const override;

    bool can_read() const override;
    bool can_write() const override;
    size_t write(const void* buf, size_t n_bytes) override;
    size_t read(void* buf, size_t max_bytes) override;

    long tell() const override;
    bool seek(long offset) override;
    bool close() override;

private:
    int encoded32_size(int raw_size) const;
    int decoded32_size(int encode_size) const;
    int encode32(const char* raw_data, int raw_size, char* dst) const;
    int decode32(const char* encoded_data, int encoded_size, char* dst) const;
};
