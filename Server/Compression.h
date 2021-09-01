#ifndef COMPRESSION_H_
#define COMPRESSION_H_

#include <string>
#include <vector>
#include "App.h"

namespace NDAVis
{
    class Compression
    {
    public:
        int compress(const float* srcArray, std::vector<char>& compression_buffer, size_t& compressed_size, int nx, int ny, int nz, int precision);
    };
}

#endif //COMPRESSION_H_