#include "MipMap.h"
#include <H5Cpp.h>
#include <fitsio.h>
#include <string>
#include <sstream>
#include <vector>
#include "MipMapUtil.h"
#include <functional>
#include <algorithm>
#include <numeric>
#include <memory>
#include <cstring>
#include <iostream>

namespace NDAVis
{

    // MipMap------------------------------------------------------------------------------------------------------------------------

    MipMap::MipMap(const std::vector<hsize_t> &datasetDims, int mip, int zmip) : datasetDims(datasetDims), mip(mip), zmip(zmip) {}

    MipMap::~MipMap()
    {
        if (!bufferDims.empty())
        {
            delete[] vals;
            delete[] count;
        }
    }

    void MipMap::createDataset(H5::Group group, const std::vector<hsize_t> &chunkDims)
    {
        H5::FloatType floatType(H5::PredType::NATIVE_FLOAT);
        floatType.setOrder(H5T_ORDER_LE);

        std::ostringstream mipMapName;
        mipMapName << "MipMaps/DATA/DATA_XY_" << mip << "_Z_" << zmip;

        MipMapUtil tempObj;
        if (tempObj.useChunks(datasetDims))
        {
            tempObj.createHdf5Dataset(dataset, group, mipMapName.str(), floatType, datasetDims, chunkDims);
        }
        else
        {
            tempObj.createHdf5Dataset(dataset, group, mipMapName.str(), floatType, datasetDims);
        }
    }

    void MipMap::write(hsize_t channelOffset)
    {

        int N = datasetDims.size();
        std::vector<hsize_t> count = {depth, height, width};
        std::vector<hsize_t> start = {0, 0, 0};
        H5::DataSpace memSpace(bufferDims.size(), bufferDims.data());
        auto fileSpace = dataset.getSpace();
        if (!count.empty() && !start.empty())
        {
            fileSpace.selectHyperslab(H5S_SELECT_SET, count.data(), start.data());
        }
        dataset.write(vals, H5::PredType::NATIVE_FLOAT, memSpace, fileSpace);
    }

    void MipMap::createBuffers(std::vector<hsize_t> &bufferDims)
    {
        bufferSize = std::accumulate(begin(bufferDims), end(bufferDims), (hsize_t)1, std::multiplies<hsize_t>());

        vals = new double[bufferSize];
        count = new int[bufferSize];

        resetBuffers();

        this->bufferDims = bufferDims;

        auto N = bufferDims.size();

        width = bufferDims[2];
        height = bufferDims[1];
        depth = bufferDims[0];
    }

    void MipMap::resetBuffers()
    {
        memset(vals, 0, sizeof(double) * bufferSize);
        memset(count, 0, sizeof(int) * bufferSize);
    }

    // MipMaps------------------------------------------------------------------------------------------------------------------------
    MipMaps::MipMaps(std::vector<hsize_t> standardDims, const std::vector<hsize_t> &chunkDims) : standardDims(standardDims), chunkDims(chunkDims)
    {
        auto dims = standardDims;
        int N = dims.size();
        int mip = 1;
        MipMapUtil tempObj;
        // We keep going until we have a mipmap which fits entirely within the minimum size
        while (dims[2] > 64 || dims[1] > 64)
        {
            int zmip = 1;

            std::vector<hsize_t> tempDims = {dims[0], dims[1], dims[2]};
            tempDims = tempObj.mipDims(tempDims, 1, 1);
            mipMaps.push_back(MipMap(tempDims, mip, zmip));
            while (tempDims[0] > 64)
            {
                tempDims = tempObj.mipDims(tempDims, 1, 2);
                zmip *= 2;
                mipMaps.push_back(MipMap(tempDims, mip, zmip));
            }
            dims = tempObj.mipDims(dims, 2, 1);
            mip *= 2;
        }
    }

    void MipMaps::createDatasets(H5::Group group)
    {
        for (auto &mipMap : mipMaps)
        {
            mipMap.createDataset(group, chunkDims);
        }
    }

    void MipMaps::write(hsize_t channelOffset)
    {
        for (auto &mipMap : mipMaps)
        {
            mipMap.write(channelOffset);
        }
    }

    void MipMaps::createBuffers(const std::vector<hsize_t> &standardBufferDims)
    {
        for (auto &mipMap : mipMaps)
        {
            MipMapUtil tempObj;
            auto dims = tempObj.mipDims(standardBufferDims, mipMap.mip, mipMap.zmip);
            mipMap.createBuffers(dims);
        }
    }

    void MipMaps::resetBuffers()
    {
        for (auto &mipMap : mipMaps)
        {
            mipMap.resetBuffers();
        }
    }

}
