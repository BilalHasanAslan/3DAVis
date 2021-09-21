
#include "HDF5Reader.h"
#include <string>
#include <iostream>
#include <H5Cpp.h>
#include "LogKeeper.h"
#include <cassert>
#include <sstream>
#include <iterator>

namespace NDAVis
{
    HDF5Reader::HDF5Reader()
    {
    }
    //Opening File
    HDF5Reader::HDF5Reader(std::string fileName)
    {
        this->fileName = fileName;
        file = H5Fopen(fileName.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT);
    }

    bool HDF5Reader::openDataset(std::string datasetName)
    {   
        dataset = file.openDataSet(datasetName.c_str());
        dspace = dataset.getSpace();
        filespace = H5Dget_space(dataset.getId());
        return true;
    }

    void HDF5Reader::setStarterClientCube()
    {   
        bool tempFound = false;
        std::string groupName = "0/MipMaps/DATA";
        H5::Group group = file.openGroup(groupName);
        XY = 1;
        Z = 1;
        //To find smallest XY dimension
        while (!tempFound)
        {
            std::ostringstream name;
            name << "DATA_XY_" << XY << "_Z_" << Z;
            if (H5Lexists(group.getId(), name.str().c_str(), H5P_DEFAULT) > 0)
            {
                XY *= 2;
            }
            else
            {
                XY /= 2;
                tempFound = true;
            }
        }

        //To find smallest Z dimension
        tempFound = false;
        while (!tempFound)
        {
            std::ostringstream name;
            name << "DATA_XY_" << XY << "_Z_" << Z;
            if (H5Lexists(group.getId(), name.str().c_str(), H5P_DEFAULT) > 0)
            {
                Z *= 2;
            }
            else
            {
                Z /= 2;
                tempFound = true;
            }
        }
        std::ostringstream name;
        name << "0/MipMaps/DATA/DATA_XY_" << XY << "_Z_" << Z;
        openDataset(name.str());
        setDimensions();
    }

    void HDF5Reader::setDimensions()
    {

        hsize_t dims[3];
        dspace.getSimpleExtentDims(dims, NULL);
        NZ = dims[0];
        NY = dims[1];
        NX = dims[2];
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

    void HDF5Reader::readDataset(float *arr, int X, int Y, int Z, int Xoffset, int Yoffset, int Zoffset)
    {
        hsize_t offset[3];
        hsize_t count[3];
        offset[0] = Zoffset;
        offset[1] = Yoffset;
        offset[2] = Xoffset;
        count[0] = Z;
        count[1] = Y;
        count[2] = X;
        memspace = H5Screate_simple(3, count, NULL);
        H5Sselect_hyperslab(memspace, H5S_SELECT_SET, offset, NULL, count, NULL);
        dataset.read(arr, H5::PredType::NATIVE_FLOAT, memspace, dspace);
    }

    void HDF5Reader::Closefile()
    {
        dataset.close();
        dspace.close();
        H5Sclose(memspace);
        H5Fclose(file.getId());
    }

    void HDF5Reader::readTileDataset(float *arr, int tileNum, int TileNX, int TileNY, int TileNZ, int Xoffset, int Yoffset, int Zoffset)
    {
        hsize_t offset[3];
        hsize_t count[3];
        offset[0] = Zoffset;
        offset[1] = Yoffset;
        offset[2] = Xoffset;
        count[0] = TileNZ;
        count[1] = TileNY;
        count[2] = TileNX;

        memspace = H5Screate_simple(3, count, NULL);
        H5Sselect_hyperslab(filespace, H5S_SELECT_SET, offset, NULL, count, NULL);
        dataset.read(arr, H5::PredType::NATIVE_FLOAT, memspace, filespace);
    }

}