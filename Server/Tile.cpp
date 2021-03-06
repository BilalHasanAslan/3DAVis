#include "Tile.h"
#include "LogKeeper.h"

namespace NDAVis
{

    /*
    The above code is a function that reads the tiles from the HDF5 file.
    
    Args:
      tileNum: The number of the tile that is being read.
      size: The number of tiles to read.
      reader: the HDF5Reader object that is used to read the data from the HDF5 file
      xChunksDim: The number of tiles in the x direction.
      yChunksDim: The number of tiles in the y direction.
      zChunksDim: The number of tiles in the z direction.
    Returns:
      A vector of tiles.
    */
    void Tiles::readTiles(int *tileNum, int size, HDF5Reader &reader, int xChunksDim, int yChunksDim, int zChunksDim)
    {
        NDAVis::LogKeeper log = NDAVis::LogKeeper("Time Taken To Read Tiles", true);
        this->xChunksDim = xChunksDim;
        this->yChunksDim = yChunksDim;
        this->zChunksDim = zChunksDim;
        int temp = *tileNum;
        for (int i = 0; i < size; i++)
        {
            Tile tempTile = Tile(temp);
            int tempTileNX, tempTileNY, tempTileNZ, Xoffset, Yoffset, Zoffset;
            if (temp <= xChunksDim)
            {
                if (temp == xChunksDim)
                {
                    tempTileNX = (reader.getXdimension()) - XYChunk * (xChunksDim - 1);
                    Xoffset = XYChunk * (xChunksDim - 1);
                }
                else
                {
                    tempTileNX = XYChunk;
                    Xoffset = XYChunk * (temp - 1);
                }
                if (reader.getYdimension() >= XYChunk)
                {
                    tempTileNY = XYChunk;
                    Yoffset = 0;
                }
                else
                {
                    tempTileNY = reader.getYdimension();
                    Yoffset = 0;
                }
                if (reader.getZdimension() >= ZChunk)
                {
                    tempTileNZ = ZChunk;
                    Zoffset = 0;
                }
                else
                {
                    tempTileNZ = reader.getZdimension();
                    Zoffset = 0;
                }
            }
            else if (temp <= xChunksDim * yChunksDim)
            {
                if (yChunksDim == 1 + ((temp - 1) / xChunksDim))
                {
                    tempTileNY = (reader.getYdimension()) - XYChunk * (yChunksDim - 1);
                    Yoffset = ((temp - 1) / xChunksDim) * XYChunk;
                }
                else
                {
                    tempTileNY = XYChunk;
                    Yoffset = ((temp - 1) / xChunksDim) * XYChunk;
                }

                if (temp % xChunksDim == 0)
                {
                    tempTileNX = (reader.getXdimension()) - XYChunk * (xChunksDim - 1);
                    Xoffset = (xChunksDim - 1) * XYChunk;
                }
                else
                {
                    tempTileNX = XYChunk;
                    Xoffset = ((temp % xChunksDim) - 1) * XYChunk;
                }

                if (reader.getZdimension() >= ZChunk)
                {
                    tempTileNZ = ZChunk;
                    Zoffset = 0;
                }
                else
                {
                    tempTileNZ = reader.getZdimension();
                    Zoffset = 0;
                }
            }
            else
            {
                if (temp % xChunksDim == 0)
                {
                    tempTileNX = (reader.getXdimension()) - XYChunk * (xChunksDim - 1);
                    Xoffset = (xChunksDim - 1) * XYChunk;
                }
                else
                {
                    tempTileNX = XYChunk;
                    Xoffset = ((temp % xChunksDim) - 1) * XYChunk;
                }

                if (zChunksDim == 1 + ((temp - 1) / (xChunksDim * yChunksDim)))
                {
                    tempTileNZ = (reader.getZdimension()) - ZChunk * (zChunksDim - 1);
                    Zoffset = ((temp - 1) / (xChunksDim * yChunksDim)) * ZChunk;
                }
                else
                {
                    tempTileNZ = ZChunk;
                    Zoffset = ((temp - 1) / (xChunksDim * yChunksDim)) * ZChunk;
                }

                if (temp % (xChunksDim * yChunksDim) != 0 && 1 + ((temp % (xChunksDim * yChunksDim) - 1) / xChunksDim) == yChunksDim)
                {
                    tempTileNY = (reader.getYdimension()) - XYChunk * (yChunksDim - 1);
                    Yoffset = ((temp % (xChunksDim * yChunksDim) - 1) / xChunksDim) * XYChunk;
                }
                else if (temp % (xChunksDim * yChunksDim) == 0)
                {
                    tempTileNY = (reader.getYdimension()) - XYChunk * (yChunksDim - 1);
                    Yoffset = ((xChunksDim * yChunksDim - 1) / xChunksDim) * XYChunk;
                }
                else
                {
                    tempTileNY = XYChunk;
                    Yoffset = ((temp % (xChunksDim * yChunksDim) - 1) / xChunksDim) * XYChunk;
                }
            }
            tempTile.setDimensions(tempTileNX, tempTileNY, tempTileNZ);
            reader.readTileDataset(tempTile.cubeArr, temp, tempTileNX, tempTileNY, tempTileNZ, Xoffset, Yoffset, Zoffset);
            allTiles.push_back(tempTile);
            temp++;
        }
        log.endLog(false);
    }


    /*
    Reconstructing one big cube from small tiles
    Args:
      arr: the array that you want to fill with the data from the tiles
      xDim: The number of elements in the x dimension of the array
      yDim: The number of rows in the original array
      zDim: The number of chunks in the z direction
      xOffset: The offset in the x dimension
      yOffset: The offset in the y dimension.
      zOffset: The offset in the z direction.
    Returns:
      The array of values that are being returned is the array of values that are being passed in.
    */
    void Tiles::combineArray(float *arr, int xDim, int yDim, int zDim, int xOffset, int yOffset, int zOffset)
    {
        NDAVis::LogKeeper log = NDAVis::LogKeeper("Time Taken To Reconstruct Tiles", true);
        #pragma omp parallel for
        for (int i = 0; i < zDim; i++)
        {
            for (int j = 0; j < yDim; j++)
            {
                for (int k = 0; k < xDim; k++)
                {
                    int tileNum = 1 + yChunksDim * xChunksDim * ((i + zOffset) / ZChunk) + ((j + yOffset) / XYChunk) * xChunksDim + (k + xOffset) / XYChunk;
                    int tileOffsetX, tileOffsetY, tileOffsetZ;
                    if (k == 0)
                    {
                        tileOffsetX = (xOffset % XYChunk);
                    }
                    else
                    {
                        tileOffsetX = 0;
                    }

                    if (j == 0)
                    {
                        tileOffsetY = yOffset % XYChunk;
                    }
                    else
                    {
                        tileOffsetY = 0;
                    }

                    if (i == 0)
                    {
                        tileOffsetZ = zOffset % ZChunk;
                    }
                    else
                    {
                        tileOffsetZ = 0;
                    }

                    int count = 0;
                    for (auto &tile : allTiles)
                    {

                        if (tile.ID == tileNum)
                        {
                            count = 0;
                            for (int f = (tileOffsetX % XYChunk); f < tile.NX && (k + f) < xDim; f++)
                            {

                                arr[(k + count) + j * xDim + i * yDim * xDim] = tile.cubeArr[(f % XYChunk) + ((tileOffsetY + j) % XYChunk) * tile.NX + ((tileOffsetZ + i) % ZChunk) * tile.NY * tile.NX];
                                count++;
                            }
                            k += count - 1;
                            break;
                        }
                    }
                }
            }
        }
        log.endLog(false);
    }
}