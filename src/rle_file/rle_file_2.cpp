#include "rle_file_2.h"

RleFile2::RleFile2(IFile* ifile) : file(ifile) {
    std::cout << "RleFile2 Constructor" << std::endl;
}

RleFile2::~RleFile2() {
    delete file;
    std::cout << "RleFile2 Destructor" << std::endl;
}

bool RleFile2::is_open() const {
    return file->is_open();
}

bool RleFile2::can_read() const {
    return file->can_read();
}

bool RleFile2::can_write() const {
    return file->can_write();
}

size_t RleFile2::write(const void* buf, size_t n_bytes) {
    const unsigned char* data = static_cast<const unsigned char*>(buf);

    size_t max_compressed_size = n_bytes * 2;
    unsigned char* compressed_data = new unsigned char[max_compressed_size];
    size_t compressed_index = 0;

    size_t i = 0;
    while (i < n_bytes) {
        size_t run_length = 1;
        while (i + run_length < n_bytes && data[i] == data[i + run_length] && run_length < 255) {
            ++run_length;
        }

        compressed_data[compressed_index++] = static_cast<unsigned char>(run_length);
        compressed_data[compressed_index++] = data[i];
        i += run_length;
    }

    size_t bytes_written = file->write(compressed_data, compressed_index);

    delete[] compressed_data;
    return bytes_written;
}

size_t RleFile2::read(void* buf, size_t max_bytes) {
    unsigned char* compressed_data = new unsigned char[max_bytes];
    size_t bytes_read = file->read(compressed_data, max_bytes);

    unsigned char* out_data = static_cast<unsigned char*>(buf);
    size_t out_index = 0;

    for (size_t i = 0; i < bytes_read;) {
        unsigned char run_length = compressed_data[i++];
        unsigned char byte_value = compressed_data[i++];

        for (size_t j = 0; j < run_length && out_index < max_bytes; ++j) {
            out_data[out_index++] = byte_value;
        }
    }

    delete[] compressed_data;
    return out_index;
}

long RleFile2::tell() const {
    return file->tell();
}

bool RleFile2::seek(long offset) {
    return file->seek(offset);
}

bool RleFile2::close() {
    return file->close();
}
