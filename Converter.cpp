#include <H5Cpp.h>
#include <fitsio.h>
#include <string>
#include "Converter.h"

namespace NDAVis
{
    Converter::Converter(std::string inputFileName, std::string outputFileName)
    {
        openFitsFile(&inputFilePtr, inputFileName);

        getFitsDims(inputFilePtr, N, dims);
        depth = N >= 3 ? dims[2] : 1;
        height = dims[1];
        width = dims[0];
    }

    void Converter::openFitsFile(fitsfile **filePtrPtr, std::string inputFileName)
    {
        int status(0);

        fits_open_file(filePtrPtr, inputFileName.c_str(), READONLY, &status);

        if (status != 0)
        {
            throw "Could not open FITS file";
        }

        int bitpix;
        fits_get_img_type(*filePtrPtr, &bitpix, &status);

        if (status != 0)
        {
            throw "Could not read image type";
        }

        if (bitpix != -32)
        {
            throw "Currently only supports FP32 files";
        }
    }

    void getFitsDims(fitsfile *filePtr, int &N, long *dims)
    {
        int status(0);

        fits_get_img_dim(filePtr, &N, &status);

        if (status != 0)
        {
            throw "Could not read image dimensions";
        }

        if (N < 2 || N > 4)
        {
            throw "Currently only supports 2D, 3D and 4D cubes";
        }

        fits_get_img_size(filePtr, 4, dims, &status);

        if (status != 0)
        {
            throw "Could not read image size";
        }
    }

}