#include "file32_2.h"

Base32File2::Base32File2(IFile* ifile, const char* alphabet)
    : file(ifile), alphabet(alphabet) {
    std::cout << "Base32File2 Constructor" << std::endl;
}

Base32File2::~Base32File2() {
    delete file; // Освобождение памяти
    std::cout << "Base32File2 Destructor" << std::endl;
}

bool Base32File2::is_open() const {
    return file->is_open();
}

bool Base32File2::can_read() const {
    return file->can_read();
}

bool Base32File2::can_write() const {
    return file->can_write();
}

size_t Base32File2::write(const void* raw_buf, size_t n_bytes) {
    if (!can_write()) return 0;

    int encoded_size = encoded32_size(n_bytes);
    char* encoded_buf = new char[encoded_size + 1];
    encode32(static_cast<const char*>(raw_buf), n_bytes, encoded_buf);

    size_t written = file->write(encoded_buf, encoded_size);

    delete[] encoded_buf;
    return written;
}

size_t Base32File2::read(void* dst_buf, size_t max_bytes) {
    if (!can_read()) return 0;

    int encoded_max = encoded32_size(max_bytes);
    char* encoded_buf = new char[encoded_max + 1];

    size_t read_encoded = file->read(encoded_buf, encoded_max);

    int decoded_size = decoded32_size(read_encoded);
    char* decoded_buf = new char[decoded_size + 1];
    decode32(encoded_buf, read_encoded, decoded_buf);

    size_t copied = std::min(decoded_size, (int)max_bytes);
    std::memcpy(dst_buf, decoded_buf, copied);

    delete[] encoded_buf;
    delete[] decoded_buf;
    return copied;
}

long Base32File2::tell() const {
    return file->tell();
}

bool Base32File2::seek(long offset) {
    return file->seek(offset);
}

bool Base32File2::close() {
    return file->close();
}

int Base32File2::encoded32_size(int raw_size) const {
    return (raw_size * 8 + 4) / 5;
}

int Base32File2::decoded32_size(int encode_size) const {
    return (encode_size * 5) / 8;
}

int Base32File2::encode32(const char* raw_data, int raw_size, char* dst) const {
    int bitcnt = 0, buffer = 0, dstind = 0;
    for (int i = 0; i < raw_size; ++i) {
        buffer = (buffer << 8) | raw_data[i];
        bitcnt += 8;
        while (bitcnt >= 5) {
            dst[dstind++] = alphabet[(buffer >> (bitcnt - 5)) & 0x1F];
            bitcnt -= 5;
        }
    }
    if (bitcnt > 0) {
        dst[dstind++] = alphabet[(buffer << (5 - bitcnt)) & 0x1F];
    }
    dst[dstind] = '\0';
    return 0;
}

int Base32File2::decode32(const char* encoded_data, int encoded_size, char* dst) const {
    int bit_buffer = 0, bits_in_buffer = 0, dst_index = 0;
    for (int i = 0; i < encoded_size; ++i) {
        int index;
        if (encoded_data[i] >= 'A' && encoded_data[i] <= 'Z') {
            index = encoded_data[i] - 'A';
        } else if (encoded_data[i] >= '1' && encoded_data[i] <= '6') {
            index = encoded_data[i] - '1' + 26;
        } else {
            return 2;
        }
        bit_buffer = (bit_buffer << 5) | index;
        bits_in_buffer += 5;
        if (bits_in_buffer >= 8) {
            dst[dst_index++] = (bit_buffer >> (bits_in_buffer - 8)) & 0xFF;
            bits_in_buffer -= 8;
        }
    }
    dst[dst_index] = '\0';
    return 0;
}
