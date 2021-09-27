#ifndef TILE_H_
#define TILE_H_

#include <vector>
#include "HDF5Reader.h"

namespace NDAVis
{
    // A single mipmap
    struct Tile
    {
        Tile(){};
        Tile(int ID)
        {
            this->ID = ID;
        };

        float *cubeArr;
        int NX, NY, NZ;
        int ID;

        void setDimensions(int NX, int NY, int NZ)
        {
            this->NX = NX;
            this->NY = NY;
            this->NZ = NZ;
            cubeArr = new float[NX * NY * NZ];
        }
    };

    struct Tiles
    {
        Tiles() {}

        int XYChunk = 64;
        int ZChunk = 64;

        std::vector<Tile> allTiles;
        int xChunksDim, yChunksDim, zChunksDim;
        
        void readTiles(int *tileNum, int size, HDF5Reader &reader, int xChunksDim, int yChunksDim, int zChunksDim);        
        void combineArray(float *arr, int xDim, int yDim, int zDim, int xOffset, int yOffset, int zOffset);

    };
}

#endif //TILE_H_