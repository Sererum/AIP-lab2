#pragma once

#include "libs.h"
#include "base_file/ifile.h"

class RleFile2 : public IFile {
private:
    IFile* file; // Указатель на объект IFile

public:
    RleFile2(IFile* ifile);
    ~RleFile2();

    bool is_open() const override;

    bool can_read() const override;
    bool can_write() const override;
    size_t write(const void* buf, size_t n_bytes) override;
    size_t read(void* buf, size_t max_bytes) override;

    long tell() const override;
    bool seek(long offset) override;

    bool close() override;
};
