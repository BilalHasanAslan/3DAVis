#include "Tile.h"
#include "LogKeeper.h"
#include <chrono>
#include <iostream>

namespace NDAVis
{

    void Tiles::readTiles(int *tileNum, int size, HDF5Reader &reader, int xChunksDim, int yChunksDim, int zChunksDim)
    {
        std::chrono::high_resolution_clock::time_point t_end, t_start;
        double elapsed_time_ms;
        t_start = std::chrono::high_resolution_clock::now();
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
        t_end = std::chrono::high_resolution_clock::now();
        elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
        std::cout << "Time Taken To Read all Tiles : " + std::to_string(elapsed_time_ms) + " ms" + " & " + std::to_string(elapsed_time_ms / 1000) + " s" << std::endl;
    }

    void Tiles::combineArray(float *arr, int xDim, int yDim, int zDim, int xOffset, int yOffset, int zOffset)
    {
        std::chrono::high_resolution_clock::time_point t_end, t_start;
        double elapsed_time_ms;
        t_start = std::chrono::high_resolution_clock::now();
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
        t_end = std::chrono::high_resolution_clock::now();
        elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
        std::cout << "Time Taken To Reconstruct all Tiles : " + std::to_string(elapsed_time_ms) + " ms" + " & " + std::to_string(elapsed_time_ms / 1000) + " s" << std::endl;
    }

}