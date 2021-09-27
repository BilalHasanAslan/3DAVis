#ifndef MIPMAPUTIL_H_
#define MIPMAPUTIL_H_

#include <H5Cpp.h>
#include <fitsio.h>
#include <vector>
namespace NDAVis
{

    struct MipMapUtil
    {
        std::vector<hsize_t> mipDims(const std::vector<hsize_t> &dims, int mip, int zmip);
        bool useChunks(const std::vector<hsize_t> &dims);
        void createHdf5Dataset(H5::DataSet& dataset, H5::Group group, std::string path, H5::DataType dataType, std::vector<hsize_t> dims, const std::vector<hsize_t>& chunkDims = std::vector<hsize_t>());
        void readFitsData(fitsfile *filePtr, hsize_t channel, unsigned int stokes, hsize_t size, float *destination);
        int tileSizeXY = 64;
        int tileSizeZ = 64;
    };
}

#endif //MIPMAPUTIL_H_