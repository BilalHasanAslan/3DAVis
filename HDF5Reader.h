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
        bool openDataset(std::string datasetName);
        void setDimensions();
        double* readDataset(int X,int Y,int Z,int Xoffset,int Yoffset,int Zoffset);
        int getXdimension();
        int getYdimension();
        int getZdimension();
        std::string fileName;
        double *data;
        hid_t file;
        hid_t dataset;
        hid_t dspace;
        int NX,NZ,NY;
    };

}
#endif //HDF5_Reader_H_