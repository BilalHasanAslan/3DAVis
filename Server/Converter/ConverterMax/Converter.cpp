#include <H5Cpp.h>
#include <fitsio.h>
#include <string>
#include "Converter.h"
#include "MipMap.h"
#include <cmath>
#include <stdio.h>
#include <iostream>

namespace NDAVis
{
    Converter::Converter(std::string inputFileName, std::string outputFileName)
    {   
        openFitsFile(&inputFilePtr, inputFileName);

        getFitsDims(inputFilePtr, N, dims);
        depth = N >= 3 ? dims[2] : 1;
        height = dims[1];
        width = dims[0];
        standardDims = {depth,height,width};
        tileDims = {1, 64, 64};
        //mipmaps
        mipMaps = MipMaps(standardDims, tileDims);
        // Prepare output file
        this->outputFileName = outputFileName;
        tempOutputFileName = outputFileName + ".tmp";
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

    void Converter::getFitsDims(fitsfile *filePtr, int &N, long *dims)
    {
        int status(0);

        fits_get_img_dim(filePtr, &N, &status);

        if (status != 0)
        {
            throw "Could not read image dimensions";
        }

        if (N < 2 || N > 3)
        {
            throw "Currently only supports 2D, 3D cubes";
        }

        fits_get_img_size(filePtr, 4, dims, &status);

        if (status != 0)
        {
            throw "Could not read image size";
        }
    }

    void Converter::convert()
    {
        outputFile = H5::H5File(tempOutputFileName, H5F_ACC_TRUNC);
        outputGroup = outputFile.createGroup("0");

        std::vector<hsize_t> chunkDims;
        chunkDims = tileDims;       
        H5::FloatType floatType(H5::PredType::NATIVE_FLOAT);
        floatType.setOrder(H5T_ORDER_LE);
        MipMapUtil tempObj;
        //tempObj.createHdf5Dataset(standardDataSet, outputGroup, "DATA", floatType, standardDims, chunkDims);
        mipMaps.createDatasets(outputGroup);


        copyAndCalculate();
        rename(tempOutputFileName.c_str(), outputFileName.c_str());
    }

    void Converter::copyAndCalculate()
    {
        hsize_t cubeSize = depth * height * width;
        standardCube = new float[cubeSize];
        mipMaps.createBuffers({depth, height, width});

        MipMapUtil tempObj;
        tempObj.readFitsData(inputFilePtr, 0, 1, cubeSize, standardCube);
        for (hsize_t z = 0; z < depth; z++)
        {
            for (hsize_t y = 0; y < height; y++)
            {
                for (hsize_t x = 0; x < width; x++)
                {
                    auto sourceIndex = x + width * y + (height * width) * z;
                    auto &val = standardCube[sourceIndex];
                    if (std::isfinite(val))
                    {
                        mipMaps.accumulate(val, x, y, z);
                    }
                }
            }

        } // end of mipmap loop
        // Final mipmap calculation
        mipMaps.calculate();
        // Write the mipmaps
        mipMaps.write(0);
        // Clear the mipmaps before the next Stokes
        mipMaps.resetBuffers();
        delete[] standardCube;
    }

}
