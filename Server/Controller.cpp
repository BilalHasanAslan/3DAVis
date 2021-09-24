#include "Controller.h"
#include "HDF5Reader.h"
#include "VtkVisul.h"
#include "Tile.h"
#include <string>
#include <iostream>
#include <thread>
#include <cmath>
#include <vector>
#include "LogKeeper.h"

namespace NDAVis
{
    //HDF5Reader readerClient, readerServer;
    Controller::Controller()
    {
        readyImage = false;
        readyClientTiles = false;
    }

    void Controller::setFile(std::string fileName)
    {
        NDAVis::LogKeeper log = NDAVis::LogKeeper("Time Taken To Starting Client", true);
        this->fileName = fileName;
        readyImage = false;
        readyClientTiles = false;
        readerClient = HDF5Reader(fileName);
        readerServer = HDF5Reader(fileName);

        readerClient.setStarterClientCube();
        int totalDim = readerClient.getXdimension() * readerClient.getYdimension() * readerClient.getZdimension();

        smallXYFile = readerClient.XY;
        smallZFile = readerClient.Z;

        clientNX = readerClient.getXdimension();
        clientNY = readerClient.getYdimension();
        clientNZ = readerClient.getZdimension();

        int xChunks = 1 + ((clientNX - 1) / XYChunk);
        int yChunks = 1 + ((clientNY - 1) / XYChunk);
        int zChunks = 1 + ((clientNZ - 1) / ZChunk);
        int tileNumDim = xChunks * yChunks * zChunks;
        int *tileNum = new int[tileNumDim];
        for (int i = 0; i < tileNumDim; i++)
        {
            tileNum[i] = i + 1;
        }
        clientTiles = Tiles();
        clientTiles.readTiles(tileNum, tileNumDim, readerClient, xChunks, yChunks, zChunks);
        readyClientTiles = true;
        auto tempReader = HDF5Reader(fileName);
        std::ostringstream tempname;
        tempname << "0/MipMaps/DATA/DATA_XY_" << 1 << "_Z_" << 1;
        tempReader.openDataset(tempname.str());
        tempReader.setDimensions();
        bigNX = tempReader.getXdimension();
        bigNY = tempReader.getYdimension();
        bigNZ = tempReader.getZdimension();
        log.endLog(false);
    }

    void Controller::startServerRender(int cameraView1, int cameraView2, int cameraView3, int cameraPos1, int cameraPos2, int cameraPos3, float *color, int colorSize, float *opacity, int opacitySize)
    {
        NDAVis::LogKeeper log = NDAVis::LogKeeper("Time Taken To Render Server", true);
        int clientDims = readerClient.getXdimension() * readerClient.getYdimension() * readerClient.getZdimension();
        long factor = serverMemory / clientDims;
        int dimFactor = std::pow(factor, 1.0 / 3);

        if (bigNX / readerClient.getXdimension() < dimFactor)
        {
            dimFactor = bigNX / readerClient.getXdimension();
        }
        if (bigNY / readerClient.getYdimension() < dimFactor)
        {
            dimFactor = bigNY / readerClient.getYdimension();
        }
        if (bigNZ / readerClient.getZdimension() < dimFactor)
        {
            dimFactor = bigNZ / readerClient.getZdimension();
        }

        int temp = 1;
        while (temp < dimFactor)
        {
            temp *= 2;
        }
        int tempZ = temp;
        if (temp > readerClient.XY)
        {
            temp = readerClient.XY;
        }
        readerServer.XY = readerClient.XY / temp;

        if (tempZ > readerClient.Z)
        {
            tempZ = readerClient.Z;
        }
        readerServer.Z = readerClient.Z / tempZ;



        std::ostringstream name;
        name << "0/MipMaps/DATA/DATA_XY_" << readerServer.XY << "_Z_" << readerServer.Z;
        //name << "0/MipMaps/DATA/DATA_XY_" << 1 << "_Z_" << 1;
        readerServer.openDataset(name.str());
        readerServer.setDimensions();

        int xOffset = (readerServer.getXdimension() - readerClient.getXdimension() * dimFactor) / 2;
        int yOffset = (readerServer.getYdimension() - readerClient.getYdimension() * dimFactor) / 2;
        int zOffset = (readerServer.getZdimension() - readerClient.getZdimension() * dimFactor) / 2;

        int renderDimX = readerClient.getXdimension() * dimFactor;
        int renderDimY = readerClient.getYdimension() * dimFactor;
        int renderDimZ = readerClient.getZdimension() * dimFactor;

        if (xOffset + renderDimX > readerServer.NX)
        {
            xOffset = 0;
            renderDimX = readerServer.NX;
        }
        if (yOffset + renderDimY > readerServer.NY)
        {
            yOffset = 0;
            renderDimY = readerServer.NY;
        }
        if (zOffset + renderDimZ > readerServer.NZ)
        {
            zOffset = 0;
            renderDimZ = readerServer.NZ;
        }

        int totalDim = renderDimZ * renderDimY * renderDimX;
        serverArr = new float[totalDim];

        int xChunks = 1 + ((readerServer.NX - 1) / XYChunk);
        int yChunks = 1 + ((readerServer.NY - 1) / XYChunk);
        int zChunks = 1 + ((readerServer.NZ - 1) / ZChunk);

        int tileNumDim = xChunks * yChunks * zChunks;
        int *tileNum = new int[tileNumDim];

        int xtileStart = xOffset / XYChunk;
        int ytileStart = yOffset / XYChunk;
        int ztileStart = zOffset / ZChunk;

        int xtileEnd = (xOffset + renderDimX - 1) / XYChunk + 2;
        int ytileEnd = (yOffset + renderDimY - 1) / XYChunk + 2;
        int ztileEnd = (zOffset + renderDimZ - 1) / ZChunk + 2;

        if (xtileEnd > xChunks)
        {
            xtileEnd = xChunks;
        }

        if (ytileEnd > yChunks)
        {
            ytileEnd = yChunks;
        }

        if (ztileEnd > zChunks)
        {
            ztileEnd = zChunks;
        }

        int c = 0;
        for (int i = ztileStart; i < ztileEnd; i++)
        {
            for (int j = ytileStart; j < ytileEnd; j++)
            {
                for (int k = xtileStart; k < xtileEnd; k++)
                {
                    tileNum[c] = k + xChunks * j + xChunks * yChunks * i + 1;
                    c++;
                }
            }
        }

        serverTiles = Tiles();
        serverTiles.readTiles(tileNum, c, readerServer, xChunks, yChunks, zChunks);
        serverTiles.combineArray(serverArr, renderDimX, renderDimY, renderDimZ, xOffset, yOffset, zOffset);
        visul.setColor(color, colorSize, opacity, opacitySize);
        visul.InsertArray(serverArr, totalDim);
        visul.setCamera(cameraView1, cameraView2, cameraView3, cameraPos1, cameraPos2, cameraPos3);
        visul.render(renderDimX, renderDimY, renderDimZ, 2, 2, 2, 0, 0, 0);
        //visul.getImage();
        
        log.endLog(false);
    }

    void Controller::setColor(float *color, int colorSize, float *opacity, int opacitySize)
    {
        visul.setColor(color, colorSize, opacity, opacitySize);
    }

    void Controller::setCameraView(int cameraView1, int cameraView2, int cameraView3, int cameraPos1, int cameraPos2, int cameraPos3)
    {
        readyImage = false;
        visul.setCamera(cameraView1, cameraView2, cameraView3, cameraPos1, cameraPos2, cameraPos3);

        readyImage = true;
    }

    bool Controller::isClientCubeReady()
    {
        return readyClientTiles;
    }

    bool Controller::isImageReady()
    {
        return readyImage;
    }

    int Controller::getClientCubedimX()
    {
        return readerClient.NX;
    }

    int Controller::getClientCubedimY()
    {
        return readerClient.NY;
    }

    int Controller::getClientCubedimZ()
    {
        return readerClient.NZ;
    }

    void Controller::setNewCordinates(int x1y1z1, int x2y1z1, int x1y2z1, int x2y2z1, int x1y1z2, int x2y1z2, int x1y2z2, int x2y2z2)
    {
        NDAVis::LogKeeper log = NDAVis::LogKeeper("Time Taken To Render Server", true);
        readyImage = false;

        int idx = x1y1z1-1;
        int tempZ = idx / (bigNX * bigNY);
        idx -= (tempZ * bigNX * bigNY);
        int tempY = idx / bigNX;
        int tempX = idx % bigNX;

        int idxX2 = x2y1z1-1;
        int tempZX2 = idxX2 / (bigNX * bigNY);
        idxX2 -= (tempZX2 * bigNX * bigNY);
        int tempYX2 = idxX2 / bigNX;
        int tempXX2 = idxX2 % bigNX;

        int idxY2 = x1y2z1-1;
        int tempZY2 = idxY2 / (bigNX * bigNY);
        idxY2 -= (tempZY2 * bigNX * bigNY);
        int tempYY2 = idxY2 / bigNX;
        int tempXY2 = idxY2 % bigNX;

        int idxZ2 = x1y1z2-1;
        int tempZZ2 = idxZ2 / (bigNX * bigNY);
        idxZ2 -= (tempZZ2 * bigNX * bigNY);
        int tempYZ2 = idxZ2 / bigNX;
        int tempXZ2 = idxZ2 % bigNX;

        int idxCorner = x2y2z2-1;
        int tempZCorner = idxCorner / (bigNX * bigNY);
        idxCorner -= (tempZCorner * bigNX * bigNY);
        int tempYCorner = idxCorner / bigNX;
        int tempXCorner = idxCorner % bigNX;

        int tempDiffX = tempXX2 - tempX;
        int tempDiffY = tempYY2 - tempY;
        int tempDiffZ = tempZZ2 - tempZ;

        int factorX = (tempDiffX - 1) / std::pow(serverMemory, 1.0 / 3) + 1;
        int factorY = (tempDiffY - 1) / std::pow(serverMemory, 1.0 / 3) + 1;
        int factorZ = (tempDiffZ - 1) / std::pow(serverMemory, 1.0 / 3) + 1;

        bool change = false;
        if (std::max(factorX, factorY) != readerServer.XY)
        {
            int count = 2;
            while (count < std::max(factorX, factorY))
            {
                count *= 2;
            }
            readerServer.XY = count / 2;
            change = true;
        }
        if (factorZ != readerServer.Z)
        {
            int count = 2;
            while (count < std::max(factorX, factorY))
            {
                count *= 2;
            }
            readerServer.XY = count / 2;
            change = true;
        }

        tempDiffX = tempDiffX / readerServer.XY;
        tempDiffY = tempDiffY / readerServer.XY;
        tempDiffZ = tempDiffZ / readerServer.Z;
        serverOffsetNX = tempX / readerServer.XY;
        serverOffsetNY = tempY / readerServer.XY;
        serverOffsetNZ = tempZ / readerServer.Z;

        if (change)
        {
            std::ostringstream name;
            name << "0/MipMaps/DATA/DATA_XY_" << readerServer.XY << "_Z_" << readerServer.Z;
            readerServer.openDataset(name.str());
            readerServer.setDimensions();
            serverTiles.allTiles.clear();

        }

        int xChunks = 1 + ((readerServer.NX - 1) / XYChunk);
        int yChunks = 1 + ((readerServer.NY - 1) / XYChunk);
        int zChunks = 1 + ((readerServer.NZ - 1) / ZChunk);

        int xtileStart = serverOffsetNX / XYChunk;
        int ytileStart = serverOffsetNY / XYChunk;
        int ztileStart = serverOffsetNZ / ZChunk;

        int xtileEnd = (serverOffsetNX + tempDiffX - 1) / XYChunk + 2;
        int ytileEnd = (serverOffsetNY + tempDiffY - 1) / XYChunk + 2;
        int ztileEnd = (serverOffsetNZ + tempDiffZ - 1) / ZChunk + 2;

        if (xtileEnd > xChunks)
        {
            xtileEnd = xChunks;
        }

        if (ytileEnd > yChunks)
        {
            ytileEnd = yChunks;
        }

        if (ztileEnd > zChunks)
        {
            ztileEnd = zChunks;
        }
        int tileNumDim = xChunks * yChunks * zChunks;
        int *tileNum = new int[tileNumDim];
        int c = 0;
        for (int i = ztileStart; i < ztileEnd; i++)
        {
            for (int j = ytileStart; j < ytileEnd; j++)
            {
                for (int k = xtileStart; k < xtileEnd; k++)
                {
                    bool found = false;

                    for (auto &tile : serverTiles.allTiles)
                    {
                        if (tile.ID = c)
                        {
                            found = true;
                        }
                    }

                    if (found != false)
                    {
                        tileNum[c] = k + xChunks * j + xChunks * yChunks * i + 1;
                        c++;
                    }
                }
            }
        }

        int totalDim = tempDiffZ * tempDiffY * tempDiffX;
        serverArr = new float[totalDim];

        serverTiles.readTiles(tileNum, c, readerServer, xChunks, yChunks, zChunks);
        serverTiles.combineArray(serverArr, tempDiffX, tempDiffY, tempDiffZ, serverOffsetNX, serverOffsetNY, serverOffsetNZ);
        visul.InsertArray(serverArr, totalDim);
        visul.render(tempDiffX, tempDiffY, tempDiffZ, 2, 2, 2, 0, 0, 0);
        log.endLog(false);
    }

    void Controller::clientRequestCube(int *cubes, int cubesSize, int XY, int Z)
    {   
        NDAVis::LogKeeper log = NDAVis::LogKeeper("Time Taken To Read Client Tiles", true);
        if (XY != readerClient.XY || Z != readerClient.Z)
        {
            clientTiles.allTiles.clear();

            readerClient.XY = XY;
            readerClient.Z = Z;

            std::ostringstream name;
            name << "0/MipMaps/DATA/DATA_XY_" << readerClient.XY << "_Z_" << readerClient.Z;
            std::cout<<name.str()<<std::endl;
            readerClient.openDataset(name.str());
            readerClient.setDimensions();
        }
        int xChunks = 1 + ((readerServer.NX - 1) / XYChunk);
        int yChunks = 1 + ((readerServer.NY - 1) / XYChunk);
        int zChunks = 1 + ((readerServer.NZ - 1) / ZChunk);
        int *tileNum = new int[cubesSize];
        int c = 0;
        for (int i = 0; i < cubesSize; i++)
        {
            bool found = false;
            for (auto &tile : clientTiles.allTiles)
            {
                if (tile.ID != cubes[i])
                {
                    found = true;
                }
            }
            if (!found)
            {
                tileNum[c] = cubes[i];
                c++;
            }
        }

        clientTiles.readTiles(tileNum, c, readerClient, xChunks, yChunks, zChunks);
        log.endLog(false);
    }

    void Controller::getImage(){
        visul.getImage();
    }

}
