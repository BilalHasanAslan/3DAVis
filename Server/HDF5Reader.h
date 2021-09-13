#ifndef HDF5_Reader_H_
#define HDF5_Reader_H_
#include <string>
#include <H5Cpp.h>
namespace NDAVis
{

    class HDF5Reader
    {
    public:
        HDF5Reader(std::string fileName);
        HDF5Reader();
        bool openDataset(std::string datasetName);
        void setDimensions();
        void readDataset(float* arr, int X, int Y, int Z, int Xoffset, int Yoffset, int Zoffset);
        int getXdimension();
        int getYdimension();
        int getZdimension();
        void setStarterClientCube();
        void Closefile();
        std::string fileName;
        double *data;
        H5::H5File file;
        H5::DataSet dataset;
        H5::DataSpace dspace;
        int NX, NZ, NY;
        hid_t memspace;
        int XY,Z;
        void readTileDataset(float* arr,int tileNum,int TileNX,int TileNY,int TileNZ,int Xoffset,int Yoffset,int Zoffset);
        hid_t filespace;
    };

}
#endif //HDF5_Reader_H_