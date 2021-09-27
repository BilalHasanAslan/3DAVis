#ifndef CONVERTER_H_
#define CONVERTER_H_

#include <H5Cpp.h>
#include <fitsio.h>
#include <string>
#include <vector>
#include "MipMap.h"

namespace NDAVis
{
    class Converter
    {
    public:
        Converter(std::string inputFileName, std::string outputFileName);

        fitsfile *inputFilePtr;
        long dims[4];
        int N;
        hsize_t depth, height, width;
        std::vector<hsize_t> standardDims;
        std::vector<hsize_t> tileDims;
        MipMaps mipMaps;
        float *standardCube;
        std::string tempOutputFileName;
        std::string outputFileName;
        H5::DataSet standardDataSet;
        H5::H5File outputFile;
        H5::Group outputGroup;
        unsigned long tileSize = 64;
        unsigned long tileSizeZ = 64;
        
        void convert();
        void copyAndCalculate();
        void getFitsDims(fitsfile *filePtr, int &N, long *dims);
        void openFitsFile(fitsfile **filePtrPtr, std::string inputFileName);
    };

}

#endif //CONVERTER_H_