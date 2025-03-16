#include "libs.h"
#include "base_file/base_file.h"

#define MAX_COMPRESSION_VALUE 255

class RleFile : public BaseFile {
public:
    RleFile();
    RleFile(const char* path, const char* mode);
    explicit RleFile(FILE* f);

    size_t write(const void* buf, size_t n_bytes) override;
    size_t read(void* buf, size_t max_bytes) override;
};
