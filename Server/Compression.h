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
        std::string to_base64 (char const* buf, unsigned int bufLen); 
        int compress(const float* srcArray, std::vector<char>& compression_buffer, size_t& compressed_size, int width, int height, int depth, int precision);
    };
}

#endif //COMPRESSION_H_