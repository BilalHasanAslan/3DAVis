
#include "HDF5Reader.h"
#include <string>
#include <iostream>
#include <H5Cpp.h>
#include "LogKeeper.h"
#include <boost/multi_array.hpp>
#include <cassert>
#include <iterator>

//25000000

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
        std::cout << XY << std::endl;
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
        std::cout << Z << std::endl;
        std::ostringstream name;
        name << "0/MipMaps/DATA/DATA_XY_" << XY << "_Z_" << Z;
        std::cout << name.str() << std::endl;
        openDataset(name.str());
        setDimensions();
    }

    void HDF5Reader::setDimensions()
    {
        std::cout << "Size of Dimensions" << std::endl;
        hsize_t dims[3];
        dspace.getSimpleExtentDims(dims, NULL);
        for (int j = 0; j < 3; j++)
        {
            std::cout << std::to_string(dims[j]) << std::endl;
        }

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
        offset[0] = Xoffset;
        offset[1] = Yoffset;
        offset[2] = Zoffset;
        count[0] = Z;
        count[1] = Y;
        count[2] = X;
        std::cout << "2" << std::endl;

/*      typedef boost::multi_array<float, 3> array_type;
        typedef array_type::index index;
        array_type arr1(boost::extents[Z][Y][X]); */

        //float arr1[Z][Y][X];
        //float arr1[10][10][10];
        std::cout << "2" << std::endl;
        //memspace = H5Screate_simple(3, count, NULL);
        //auto status = H5Sselect_hyperslab(dspace, H5S_SELECT_SET, offset, NULL, count, NULL);
        //auto status = H5Dread(dataset, H5T_NATIVE_INT, memspace, dspace, H5P_DEFAULT, arr);
        dataset.read(arr, H5::PredType::NATIVE_FLOAT, dspace, dspace);
        std::cout << "2" << std::endl;


/*         for (int j = 0; j < Z; j++)
        {
            for (int i = 0; i < Y; i++)
            {
                for (int f = 0; f < X; f++)
                {
                    arr[j + Z * (i + Y * f)] = arr1[j][i][f];  
                        if (arr1[j][i][f] != 0)
                    {
                        std::cout << arr1[j][i][f] << std::endl;
                    } 
                }
            }
        } */

        //H5Sclose(memspace);
    }

    void HDF5Reader::Closefile()
    {
        dataset.close();
        dspace.close();
        H5Sclose(memspace);
        H5Fclose(file.getId());
    }

}