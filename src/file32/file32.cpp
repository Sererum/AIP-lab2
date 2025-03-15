#include "file32.h"

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

/*
class INT {
	INT(const char*);
}

class IR : INT {
	IR(const char* int, const char *ir) : INT(int) {
		...
	}
}
*/

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

int Base32File::encoded32_size(int raw_size) const {
    return (raw_size*8+4) / 5;
}

int Base32File::decoded32_size(int encode_size) const {
    return (encode_size * 5) / 8; 
}

size_t Base32File::read(void* dst_buf, size_t max_bytes) {
    if (!can_read()) return 0;

    int encoded_max = encoded32_size(max_bytes);
    char* encoded_buf = new char[encoded_max + 1]; 

    size_t read_encoded = read_raw(encoded_buf, encoded_max);

    int decoded_size = decoded32_size(read_encoded);
    char* decoded_buf = new char[decoded_size + 1];
    decode32(encoded_buf, read_encoded, decoded_buf);

    size_t copied = std::min(decoded_size, (int) max_bytes);
    std::memcpy(dst_buf, decoded_buf, copied);
    static_cast<char*>(dst_buf)[copied] = '\0'; 

    delete[] encoded_buf;
    delete[] decoded_buf;
    return copied;
}

int Base32File::encode32(const char* raw_data, int raw_size, char* dst) const {
    if (!raw_data || raw_size <= 0 || !dst){
        return 1;//условие для выхода
        } 
    int bitcnt = 0; 
    int buffer = 0; 
    int dstind = 0; 
    for (int i = 0; i < raw_size; ++i){
        buffer = (buffer << 8) | raw_data[i]; //каждую операцию + 1 байт в буфере
        bitcnt += 8;
        while (bitcnt >= 5) // делим на пятерки
        {
            dst[dstind++] = alphabet[(buffer >> (bitcnt - 5)) & 0x1F]; // сдвигаем влево и сравниваем
            bitcnt -= 5;
        }
    }

    if (bitcnt > 0) {
        dst[dstind++] = alphabet[(buffer << (5 - bitcnt)) & 0x1F]; 
    }
    dst[dstind] = '\0';
    return 0;
}

int Base32File::decode32(const char *encoded_data, int encoded_size, char *dst) const {
    if (!encoded_data || encoded_size <= 0 || !dst) return 1;

    int bit_buffer = 0;
    int bits_in_buffer = 0;
    int dst_index = 0;

    for (int i = 0; i < encoded_size; ++i) {
        int index;

        //определяем индекс символа из таблицы
        if (encoded_data[i] >= 'A' && encoded_data[i] <= 'Z') {
            index = encoded_data[i] - 'A';
        } 
        else if (encoded_data[i] >= '1' && encoded_data[i] <= '6') {
            index = encoded_data[i] - '1' + 26;
        } 
        else {
            return 2; //недопустимый символ
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

