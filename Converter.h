#ifndef CONVERTER_H_
#define CONVERTER_H_

#include <H5Cpp.h>
#include <fitsio.h>
#include <string>

namespace NDAVis
{
    class Converter
    {
    public:
        Converter(std::string inputFileName, std::string outputFileName);
        void openFitsFile(fitsfile **filePtrPtr, std::string inputFileName);
        fitsfile *inputFilePtr;
        long dims[4];
        int N;
        void getFitsDims(fitsfile* filePtr, int& N, long* dims);
        hsize_t depth, height, width;
    };
}

#endif //CONVERTER_H_