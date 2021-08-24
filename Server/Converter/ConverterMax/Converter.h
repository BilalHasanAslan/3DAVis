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
        unsigned long tileSize = 64;
        unsigned long tileSizeZ = 64;
        Converter(std::string inputFileName, std::string outputFileName);
        void openFitsFile(fitsfile **filePtrPtr, std::string inputFileName);
        fitsfile *inputFilePtr;
        long dims[4];
        int N;
        void getFitsDims(fitsfile *filePtr, int &N, long *dims);
        hsize_t depth, height, width;
        std::vector<hsize_t> standardDims;
        std::vector<hsize_t> tileDims;
        MipMaps mipMaps;
        void convert();
        void copyAndCalculate();
        float *standardCube;
        std::string tempOutputFileName;
        std::string outputFileName;
            H5::DataSet standardDataSet;

        // Main HDF5 objects
        H5::H5File outputFile;
        H5::Group outputGroup;
    };

}

#endif //CONVERTER_H_