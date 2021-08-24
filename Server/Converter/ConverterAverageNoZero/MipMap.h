#ifndef MIPMAP_H_
#define MIPMAP_H_

#include <H5Cpp.h>
#include <fitsio.h>
#include <vector>
#include <cmath>
#include "MipMapUtil.h"
namespace NDAVis
{
    // A single mipmap
    struct MipMap
    {
        MipMap(){};
        MipMap(const std::vector<hsize_t> &datasetDims, int mip, int zmip);
        ~MipMap();

        std::vector<hsize_t> datasetDims;
        int mip;
        int zmip;

        void createDataset(H5::Group group, const std::vector<hsize_t> &chunkDims);

        H5::DataSet dataset;

        std::vector<hsize_t> bufferDims;
        hsize_t bufferSize;

        hsize_t width;
        hsize_t height;
        hsize_t depth;
        hsize_t stokes;

        double *vals;
        int *count;

        void accumulate(float val, hsize_t x, hsize_t y, hsize_t z)
        {
            hsize_t mipIndex = (z / zmip) * width * height + (y / mip) * width + (x / mip);
            if (count[mipIndex] == 0)
            {
                vals[mipIndex] += val;
                count[mipIndex]++;
            }
            else
            {
                if (val != 0)
                {
                    vals[mipIndex] += val;
                    count[mipIndex]++;
                }
            }
        }

        void calculate()
        {
            for (hsize_t mipIndex = 0; mipIndex < bufferSize; mipIndex++)
            {
                if (count[mipIndex])
                {
                    vals[mipIndex] /= count[mipIndex];
                }
                else
                {
                    vals[mipIndex] = NAN;
                }
            }
        }
        void write(hsize_t channelOffset);
        void createBuffers(std::vector<hsize_t> &bufferDims);
        void resetBuffers();
    };

    struct MipMaps
    {
        MipMaps(){};
        MipMaps(std::vector<hsize_t> standardDims, const std::vector<hsize_t> &chunkDims);
        std::vector<hsize_t> standardDims;
        std::vector<hsize_t> chunkDims;
        std::vector<MipMap> mipMaps;
        void createDatasets(H5::Group group);
        void write(hsize_t channelOffset);
        void accumulate(double val, hsize_t x, hsize_t y, hsize_t z)
        {
            for (auto &mipMap : mipMaps)
            {
                mipMap.accumulate(val, x, y, z);
            }
        }

        void calculate()
        {
            for (auto &mipMap : mipMaps)
            {
                mipMap.calculate();
            }
        }

        void createBuffers(const std::vector<hsize_t> &standardBufferDims);
        void resetBuffers();
    };
}

#endif //MIPMAP_H_