#include "HDF53DConstructor.h"
#include "HDF5Reader.h"
#include "VtkVisul.h"
#include <string>
#include <iostream>
#include <thread>
#include <cmath>

namespace NDAVis
{
    //HDF5Reader readerClient, readerServer;
    HDF53DConstructor::HDF53DConstructor()
    {
        readyImage = false;
        readyClientCube = false;
    }

    void HDF53DConstructor::setFile(std::string fileName)
    {
        this->fileName = fileName;
        readyImage = false;
        readyClientCube = false;
        readerClient = HDF5Reader(fileName);
        readerServer = HDF5Reader(fileName);

        readerClient.setStarterClientCube();
        int totalDim = readerClient.getXdimension() * readerClient.getYdimension() * readerClient.getZdimension();
        clientArr = new float[totalDim];
        readerClient.readDataset(clientArr, readerClient.getXdimension(), readerClient.getYdimension(), readerClient.getZdimension(), 0, 0, 0);
        readyClientCube = true;
        clientNX = readerClient.getXdimension();
        clientNY = readerClient.getYdimension();
        clientNZ = readerClient.getZdimension();

        clientOffsetNX = 0;
        clientOffsetNY = 0;
        clientOffsetNZ = 0;
    }

    void HDF53DConstructor::renderServer(int cameraView1, int cameraView2, int cameraView3, int cameraPos1, int cameraPos2, int cameraPos3, int color)
    {
        int clientDims = readerClient.getXdimension() * readerClient.getYdimension() * readerClient.getZdimension();
        long factor = serverMemory / clientDims;
        int dimFactor = std::pow(factor, 1.0 / 3);

        auto tempReader = HDF5Reader(fileName);
        std::ostringstream tempname;
        tempname << "0/MipMaps/DATA/DATA_XY_" << 1 << "_Z_" << 1;
        tempReader.openDataset(tempname.str());
        tempReader.setDimensions();
        if (tempReader.getXdimension() / readerClient.getXdimension() < dimFactor)
        {
            dimFactor = tempReader.getXdimension() / readerClient.getXdimension();
        }
        if (tempReader.getYdimension() / readerClient.getYdimension() < dimFactor)
        {
            dimFactor = tempReader.getYdimension() / readerClient.getYdimension();
        }
        if (tempReader.getZdimension() / readerClient.getZdimension() < dimFactor)
        {
            dimFactor = tempReader.getZdimension() / readerClient.getZdimension();
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

        readerServer.openDataset(name.str());
        readerServer.setDimensions();

        int totalDim = readerClient.getXdimension() * readerClient.getYdimension() * readerClient.getZdimension() * dimFactor * dimFactor * dimFactor;

        serverArr = new float[totalDim];

        int xOffset = (readerServer.getXdimension() - readerClient.getXdimension() * dimFactor) / 2;
        int yOffset = (readerServer.getYdimension() - readerClient.getYdimension() * dimFactor) / 2;
        int zOffset = (readerServer.getZdimension() - readerClient.getZdimension() * dimFactor) / 2;

        /*         for(int i=0;i<totalDim;i++){
            if(serverArr[i]>0){
                std::cout << serverArr[i] << std::endl;
            }
        } */
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



        readerServer.readDataset(serverArr, renderDimX ,renderDimY , renderDimZ, xOffset, yOffset, zOffset);

        /* 
        float *serverArrr = new float[totalDim];
        float *ptr = serverArrr;
        for (int i = 0; i < totalDim; i++)
        {
            *ptr = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            ptr++;
        }   */

        //visul.VtkVisul();
        visul.setColor(color);
        visul.InsertArray(serverArr, totalDim);

        visul.setCamera(cameraView1, cameraView2, cameraView3, cameraPos1, cameraPos2, cameraPos3);
        visul.render(renderDimX, renderDimY, renderDimZ , 2, 2, 2, 0, 0, 0);
    }

    void HDF53DConstructor::setColor(int color)
    {
        readyImage = false;
        visul.setColor(color);

        readyImage = true;
    }

    void HDF53DConstructor::setCameraView(int cameraView1, int cameraView2, int cameraView3, int cameraPos1, int cameraPos2, int cameraPos3)
    {
        readyImage = false;
        visul.setCamera(cameraView1, cameraView2, cameraView3, cameraPos1, cameraPos2, cameraPos3);

        readyImage = true;
    }

    bool HDF53DConstructor::isClientCubeReady()
    {
        return readyClientCube;
    }

    bool HDF53DConstructor::isImageReady()
    {
        return readyImage;
    }

    int HDF53DConstructor::getClientCubedimX()
    {
        return readerClient.NX;
    }

    int HDF53DConstructor::getClientCubedimY()
    {
        return readerClient.NY;
    }

    int HDF53DConstructor::getClientCubedimZ()
    {
        return readerClient.NZ;
    }

    void HDF53DConstructor::setNewCordinates(int x1y1z1, int x2y1z1, int x1y2z1, int x2y2z1, int x1y1z2, int x2y1z2, int x1y2z2, int x2y2z2)
    {
        readyClientCube = false;
        readyImage = false;
        /*int idx = x1y1z1;
        int tempZ = idx / (readerClient.getXdimension() * readerClient.getYdimension());
        idx -= (tempZ * readerClient.getXdimension() * readerClient.getYdimension());
        int tempY = idx / readerClient.getXdimension();
        int tempX = idx % readerClient.getXdimension();

        int idxX2 = x2y1z1;
        int tempZX2 = idxX2 / (readerClient.getXdimension() * readerClient.getYdimension());
        idxX2 -= (tempZX2 * readerClient.getXdimension() * readerClient.getYdimension());
        int tempYX2 = idxX2 / readerClient.getXdimension();
        int tempXX2 = idxX2 % readerClient.getXdimension();

        int idxY2 = x1y2z1;
        int tempZY2 = idxY2 / (readerClient.getXdimension() * readerClient.getYdimension());
        idxY2 -= (tempZY2 * readerClient.getXdimension() * readerClient.getYdimension());
        int tempYY2 = idxY2 / readerClient.getXdimension();
        int tempXY2 = idxY2 % readerClient.getXdimension();

        int idxZ2 = x1y1z2;
        int tempZZ2 = idxZ2 / (readerClient.getXdimension() * readerClient.getYdimension());
        idxZ2 -= (tempZZ2 * readerClient.getXdimension() * readerClient.getYdimension());
        int tempYZ2 = idxZ2 / readerClient.getXdimension();
        int tempXZ2 = idxZ2 % readerClient.getXdimension();

        int idxCorner = x2y2z2;
        int tempZCorner = idxCorner / (readerClient.getXdimension() * readerClient.getYdimension());
        idxCorner -= (tempZCorner * readerClient.getXdimension() * readerClient.getYdimension());
        int tempYCorner = idxCorner / readerClient.getXdimension();
        int tempXCorner = idxCorner % readerClient.getXdimension();

        int tempDiffX = tempX - tempXX2;
        int tempDiffY = tempY - tempYY2;
        int tempDiffZ = tempZ - tempZZ2;

        int factorX = tempDiffX;
        int factorY = tempDiffY;
        int factorZ = tempDiffZ;
        factorX = std::pow(clientMemory, 1.0 / 3) / factorX;
        factorY = std::pow(clientMemory, 1.0 / 3) / factorY;
        factorZ = std::pow(clientMemory, 1.0 / 3) / factorZ;

        clientOffsetNX = (tempX  + clientOffsetNX)* factorX;
        clientOffsetNY = (tempY  + clientOffsetNY)* factorY;
        clientOffsetNZ = (tempZ  + clientOffsetNZ)* factorZ;

        clientNX = tempXCorner* factorX;
        clientNY = tempYCorner* factorY;
        clientNZ = tempZCorner* factorZ;*/
    }

    float *HDF53DConstructor::getClientCube()
    {
        return clientArr;
    }

}
