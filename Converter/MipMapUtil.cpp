#include <H5Cpp.h>
#include <fitsio.h>
#include <string>
#include <sstream>
#include <vector>
#include "MipMapUtil.h"
#include <cmath>
#include <iostream>
namespace NDAVis
{

    //MipMapUtil------------------------------------------------------------------------------------------------------------------------
    std::vector<hsize_t> MipMapUtil::mipDims(const std::vector<hsize_t> &dims, int mip, int zmip)
    {
        int N = dims.size();
        auto mipDims = dims;

        for (auto i = 1; i < 3; i++)
        {
            mipDims[i] = std::ceil((float)mipDims[i] / mip);
        }

        mipDims[0] = std::ceil((float)mipDims[0] / zmip);

        return mipDims;
    }

    bool MipMapUtil::useChunks(const std::vector<hsize_t> &dims)
    {

        for (auto i = 1; i < 3; i++)
        {
            if (dims[i] < tileSizeXY)
            {
                return false;
            }
        }

        if (dims[0] < tileSizeZ)
        {
            return false;
        }

        return true;
    }

    void MipMapUtil::createHdf5Dataset(H5::DataSet &dataset, H5::Group group, std::string path, H5::DataType dataType, std::vector<hsize_t> dims, const std::vector<hsize_t> &chunkDims)
    {
        std::vector<std::string> result;
        std::istringstream stream(path);
        std::string substr;
        while (std::getline(stream, substr, '/'))
        {
            result.push_back(substr);
        }

        auto splitPath = result;

        auto name = splitPath.back();
        splitPath.pop_back();
        for (auto &groupname : splitPath)
        {
            if (!(H5Lexists(group.getId(), groupname.c_str(), H5P_DEFAULT) > 0))
            {
                group = group.createGroup(groupname);
            }
            else
            {
                group = group.openGroup(groupname);
            }
        }
        H5::DSetCreatPropList propList;
        if (!chunkDims.empty())
        {
            propList.setChunk(chunkDims.size(), chunkDims.data());
        }
        auto dataSpace = H5::DataSpace(dims.size(), dims.data());
        dataset = group.createDataSet(name, dataType, dataSpace, propList);
    }

    void MipMapUtil::readFitsData(fitsfile *filePtr, hsize_t channel, unsigned int stokes, hsize_t size, float *destination)
    {
        long fpixel[] = {1, 1, (long)channel + 1, stokes + 1};
        int status(0);

        fits_read_pix(filePtr, TFLOAT, fpixel, size, NULL, destination, NULL, &status);

        if (status != 0)
        {
            throw "Could not read image data";
        }
    }



}