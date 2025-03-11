#include "base_32_file.h"

// из lab4
const char default_alphabet[32] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z', '1', '2', '3', '4', '5', '6'
};

//вызывает конструктор BaseFile и сохраняет таблицу кодировки
Base32File::Base32File(const char* path, const char* mode, const char* alphabet)
    : BaseFile(path, mode), alphabet(alphabet) {}

//кодирует данные перед записью
size_t Base32File::write(const void* raw_buf, size_t n_bytes) {
    if (!can_write()) return 0;

    int encoded_size = encoded32_size(n_bytes);
    char* encoded_buf = new char[encoded_size + 1]; // +1 для завершающего '\0'
    encode32(static_cast<const char*>(raw_buf), n_bytes, encoded_buf);

    size_t written = write_raw(encoded_buf, encoded_size);

    delete[] encoded_buf;
    return written;
}

size_t Base32File::read(void* dst_buf, size_t max_bytes) {
    if (!can_read()) return 0;

    int encoded_max = encoded32_size(max_bytes);
    char* encoded_buf = new char[encoded_max + 1]; 

    size_t read_encoded = read_raw(encoded_buf, encoded_max);
    encoded_buf[read_encoded] = '\0'; // добавляем завершающий '\0'

    int decoded_size = decoded32_size(read_encoded);
    char* decoded_buf = new char[decoded_size + 1];
    decode32(encoded_buf, read_encoded, decoded_buf);

    size_t copied = std::min(decoded_size, max_bytes);
    std::memcpy(dst_buf, decoded_buf, copied);
    static_cast<char*>(dst_buf)[copied] = '\0'; 

    delete[] encoded_buf;
    delete[] decoded_buf;
    return copied;
}
