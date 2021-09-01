#include <string>
#include <iostream>
#include <zfp>
#include "Compression.h"

using namespace NDAVis{
    int Compression::compress(const float* srcArray, std::vector<char>& compression_buffer, size_t& compressed_size, int nx, int ny, int nz, int precision) {
        int status = 0;
        zfp_type type = zfp_type_float;
        return status;
    }
}

