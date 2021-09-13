#include <emscripten/emscripten.h>
#include "built/include/zfp.h"

int EMSCRIPTEN_KEEPALIVE zfpDecompress (int precision, float* array, int width, int height, int depth, unsigned char* buffer, int compressedSize) {
    int status = 0;    //success
    zfp_type type;
    zfp_field* field; 
    zfp_stream* zfp;   
    bitstream* stream; 
    type = zfp_type_float;

    field = zfp_field_3d(array, type, width, height, depth);
    zfp = zfp_stream_open(NULL);

    zfp_stream_set_precision(zfp, precision);
    stream = stream_open(buffer, compressedSize);
    zfp_stream_set_bit_stream(zfp, stream);
    zfp_stream_rewind(zfp);

    if (!zfp_decompress(zfp, field)) {
        status = 1;
    }

    zfp_field_free(field);
    zfp_stream_close(zfp);
    stream_close(stream);

    return status;
}