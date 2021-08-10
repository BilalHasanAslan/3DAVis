
#include "HDF5Reader.h"
#include <string>
#include <iostream>
#include <H5Cpp.h>
#include "LogKeeper.h"
#include "boost/multi_array.hpp"
#include <cassert>

namespace NDAVis
{
    std::string fileName;
    hid_t file;
    hid_t dataset;
    hid_t dspace;

    //Opening File
    HDF5Reader::HDF5Reader(std::string fileName)
    {
        this->fileName = fileName;
        file = H5Fopen(fileName.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT);
    }

    bool HDF5Reader::openDataset(std::string datasetName)
    {
        dataset = H5Dopen2(file, datasetName.c_str(), H5P_DEFAULT);
        dspace = H5Dget_space(dataset);
        return true;
    }

    void HDF5Reader::setDimensions()
    {
        std::cout << "Number of Dimensions" << std::endl;
        const int ndims = H5Sget_simple_extent_ndims(dspace);
        std::cout << std::to_string(ndims) << std::endl;
        std::cout << "Size of Dimensions" << std::endl;
        hsize_t dims[ndims];
        H5Sget_simple_extent_dims(dspace, dims, NULL);
        for (int j = 0; j < ndims; j++)
        {
            std::cout << std::to_string(dims[j]) << std::endl;
        }
        NX = dims[0];
        NY = dims[1];
        NZ = dims[2];
    }

    int HDF5Reader::getXdimension()
    {
        return NX;
    }
    int HDF5Reader::getYdimension()
    {
        return NY;
    }
    int HDF5Reader::getZdimension()
    {
        return NZ;
    }

    double *HDF5Reader::readDataset(int X, int Y, int Z, int Xoffset, int Yoffset, int Zoffset)
    {
        double dataRead[100][100][100];

        for (int j = 0; j < 100; j++)
        {
            for (int i = 0; i < 100; i++)
            {
                for (int k = 0; k < 100; k++)
                {
                    dataRead[j][i][k] = 0;
                }
            }
        }
        hsize_t offset[3];
        hsize_t count[3];
        offset[0] = Xoffset;
        offset[1] = Yoffset;
        offset[2] = Zoffset;
        count[0] = X;
        count[1] = Y;
        count[2] = Z;
        herr_t status = H5Sselect_hyperslab(dspace, H5S_SELECT_SET, offset, NULL, count, NULL);

        hsize_t dimsm[3];
        dimsm[0] = X;
        dimsm[1] = Y;
        dimsm[2] = Z;
        hsize_t offset_out[3];
        offset_out[0] = 0;
        offset_out[1] = 0;
        offset_out[2] = 0;
        hsize_t count_out[3];
        count_out[0] = X;
        count_out[1] = Y;
        count_out[2] = Z;
        hid_t memspace = H5Screate_simple(3, dimsm, NULL);
        status = H5Sselect_hyperslab(memspace, H5S_SELECT_SET, offset_out, NULL, count_out, NULL);
        status = H5Dread(dataset, H5T_NATIVE_INT, memspace, dspace, H5P_DEFAULT, dataRead);
        for (int j = 0; j < X; j++)
        {
            for (int i = 0; i < Y; i++)
                printf("%f ", dataRead[j][i][0]);
            printf("\n");
        }
        std::cout << "Test" << std::endl;
        data = &dataRead[0][0][0];
        return data;
    }

    void HDF5Reader::Closefile()
    {
        H5Dclose(dataset);
        H5Sclose(dspace);
        H5Sclose(memspace);
        H5Fclose(file);
    }

}