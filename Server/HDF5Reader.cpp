
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
    /*
    The constructor for the HDF5Reader class does nothing.
    
    Args:
      self: The object that is being created.
      file_name: The name of the file to be read.
    Returns:
      Nothing
    */
    HDF5Reader::HDF5Reader()
    {
    }

    //Opening File
    /*
    The constructor opens the file with the given name.
    
    Args:
      fileName: The name of the file to open.
    Returns:
      Nothing.
    */
    HDF5Reader::HDF5Reader(std::string fileName)
    {
        this->fileName = fileName;
        file = H5Fopen(fileName.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT);
    }


    /*
    Open the HDF5 file and open the dataset.
    
    Args:
      datasetName: the name of the dataset to open
    Returns:
      
    */
    bool HDF5Reader::openDataset(std::string datasetName)
    {   
        dataset = file.openDataSet(datasetName.c_str());
        dspace = dataset.getSpace();
        filespace = H5Dget_space(dataset.getId());
        return true;
    }

    /*
    Find the smallest XY and Z dimensions of the file.
    
    Args:

    Returns:
      The starter client cube.
    */
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

    /*
    Read the HDF5 file and set the dimensions from the data.
    
    Args:
      None
    Returns:
      Nothing.
    */
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

    /*
    Read a 3D dataset into a 3D array.
    
    Args:
      arr: the array to be filled with data
      X: the number of columns in the dataset
      Y: The number of rows in the dataset.
      Z: The number of slices in the z-dimension.
      Xoffset: The offset in the X direction.
      Yoffset: The offset in the Y dimension.
      Zoffset: The offset in the Z direction.
    Returns:
      Nothing.
    */
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

    /*
    Closes the file that has been opened and clears memory
    
    Args:
    Returns:
      Nothing.
    */
    void HDF5Reader::Closefile()
    {
        dataset.close();
        dspace.close();
        H5Sclose(memspace);
        H5Fclose(file.getId());
    }

    /*
    Read a tile of data from the HDF5 file into a float array.
    
    Args:
      arr: the array to be filled with data
      tileNum: the tile number
      TileNX: the number of pixels in the X direction for the tile
      TileNY: The number of rows in the tile.
      TileNZ: The number of Z slices in the tile
      Xoffset: The starting x-coordinate of the tile.
      Yoffset: The offset in the Y direction.
      Zoffset: The starting Z index of the tile
    Returns:
      Nothing.
    */
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