#include <string>
#include <iostream>
#include "Compression.h"
#include <zfp.h>

namespace NDAVis{
    static const std::string base64_chars =
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";

    std::string Compression::to_base64 (char const* buf, unsigned int bufLen) {
        std::string ret;
        int i = 0;
        int j = 0;
        char char_array_3[3];
        char char_array_4[4];

        while (bufLen--) {
            char_array_3[i++] = *(buf++);
            if (i == 3) {
                char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
                char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0)) >> 4;
                char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0)) >> 6;
                char_array_4[3] = char_array_3[2] & 0x3f;

                for(i = 0; (i <4) ; i++)
                     ret += base64_chars[char_array_4[i]];
                i = 0;
            }
        }
        if (i) {
            for(j = i; j < 3; j++)
            char_array_3[j] = '\0';

            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (j = 0; (j < i + 1); j++)
                ret += base64_chars[char_array_4[j]];

            while((i++ < 3))
                ret += '=';
        }

        return ret;
    }

    int Compression::compress(const float* srcArray, std::vector<char>& compression_buffer, size_t& compressed_size, int width, int height, int depth, int precision) {
        int status = 0; //success
        zfp_type type = zfp_type_float;
        zfp_field* field;
        zfp_stream* zfp;
        size_t buffer_size;
        bitstream* stream;

        field = zfp_field_3d((void*)srcArray, type, width, height, depth);
        zfp = zfp_stream_open(nullptr);
        zfp_stream_set_precision(zfp, precision);

        buffer_size = zfp_stream_maximum_size(zfp, field);
        if (compression_buffer.size() < buffer_size) {
            compression_buffer.resize(buffer_size);
        }
        stream = stream_open(compression_buffer.data(), buffer_size);
        zfp_stream_set_bit_stream(zfp, stream);
        zfp_stream_rewind(zfp);

        compressed_size = zfp_compress(zfp, field);
        if (!compressed_size) {
            status = 1;
        }

        zfp_field_free(field);
        zfp_stream_close(zfp);
        stream_close(stream);

        return status;
    }
}

