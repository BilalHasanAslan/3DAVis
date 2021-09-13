#ifndef Controller_H_
#define Controller_H_

#include <string>
#include "HDF5Reader.h"
#include "VtkVisul.h"
#include "Tile.h"
namespace NDAVis
{
    struct Controller
    {
        Controller();
        bool readyImage = false;
        bool readyClientTiles = false;
        //Memory in mb = clientMemory*4/1000000 Same for Server Memory
        //262144 for one mb, 262144000 for one gb
        long clientMemory = 262144;
        long serverMemory = 262144000;
        int XYChunk = 64;
        int ZChunk = 64;
        Tiles clientTiles, serverTiles;
        void setFile(std::string fileName);
        void startServerRender(int cameraView1, int cameraView2, int cameraView3, int cameraPos1, int cameraPos2, int cameraPos3,float *color, int colorSize,float* opacity,int opacitySize);
        void renderServer();
        void setNewCordinates(int x1y1z1, int x2y1z1, int x1y2z1, int x2y2z1, int x1y1z2, int x2y1z2, int x1y2z2, int x2y2z2);
        void setColor(float *color, int colorSize,float* opacity,int opacitySize);
        void setCameraView(int view1, int view2, int view3, int position1, int position2, int position3);
        bool isClientCubeReady();
        bool isImageReady();
        void getImage();
        HDF5Reader readerClient, readerServer;
        std::string fileName;
        VtkVisul visul;
        int getClientCubedimX();
        int getClientCubedimY();
        int getClientCubedimZ();
        float *serverArr;
        int clientNX, clientNY, clientNZ, serverOffsetNX, serverOffsetNY, serverOffsetNZ, bigNX, bigNY, bigNZ;
        void clientRequestCube(int *cubes, int cubesSize, int XY,int Z);
    };

}

#endif //Controller_H_