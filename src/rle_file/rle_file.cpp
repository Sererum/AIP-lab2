#include "rle_file.h"

RleFile::RleFile() : BaseFile() {}

RleFile::RleFile(const char* path, const char* mode) : BaseFile(path, mode) {}

RleFile::RleFile(FILE* f) : BaseFile(f) {}

size_t RleFile::write(const void* buf, size_t n_bytes) {
    const unsigned char* data = static_cast<const unsigned char*>(buf);

    size_t max_compressed_size = n_bytes * 2; 
    unsigned char* compressed_data = new unsigned char[max_compressed_size];
    size_t compressed_index = 0;

    size_t i = 0;
    while (i < n_bytes) {
        size_t run_length = 1;
        while (i + run_length < n_bytes 
			&& data[i] == data[i + run_length] 
			&& run_length < MAX_COMPRESSION_VALUE) 
		{
            ++run_length;
        }

        if (run_length > 1) {
            compressed_data[compressed_index++] = static_cast<unsigned char>(run_length);
            compressed_data[compressed_index++] = data[i];
            i += run_length;
        } else {
            compressed_data[compressed_index++] = 1;
            compressed_data[compressed_index++] = data[i];
            ++i;
        }
    }

    size_t bytes_written = write_raw(compressed_data, compressed_index);

    delete[] compressed_data;

    return bytes_written;
}

size_t RleFile::read(void* buf, size_t max_bytes) {
    unsigned char* compressed_data = new unsigned char[max_bytes];
    size_t bytes_read = read_raw(compressed_data, max_bytes);

    unsigned char* out_data = static_cast<unsigned char*>(buf);
    size_t out_index = 0;

    for (size_t i = 0; i < bytes_read; ) {
        unsigned char run_length = compressed_data[i++];
        unsigned char byte_value = compressed_data[i++];

        for (size_t j = 0; j < run_length && out_index < max_bytes; ++j) {
            out_data[out_index++] = byte_value;
        }
    }

    delete[] compressed_data;

    return out_index;
}
