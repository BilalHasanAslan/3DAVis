#ifndef HDF53DConstructor_H_
#define HDF53DConstructor_H_

#include <string>
#include "HDF5Reader.h"
#include "VtkVisul.h"
namespace NDAVis
{
    struct HDF53DConstructor
    {
        HDF53DConstructor();
        bool readyImage = false;
        bool readyClientCube = false;
        //Memory in mb = clientMemory*4/1000000 Same for Server Memory
        //262144 for one mb, 262144000 for one gb
        long clientMemory = 262144;
        long serverMemory = 262144000;
        void setFile(std::string fileName);
        void renderServer(int cameraView1, int cameraView2, int cameraView3, int cameraPos1, int cameraPos2, int cameraPos3, int color);
        void setNewCordinates(int x1y1z1, int x2y1z1, int x1y2z1, int x2y2z1, int x1y1z2, int x2y1z2, int x1y2z2, int x2y2z2);
        void setColor(int color);
        void setCameraView(int view1, int view2, int view3, int position1, int position2, int position3);
        bool isClientCubeReady();
        bool isImageReady();
        float* getClientCube();
        void getImage();
        HDF5Reader readerClient, readerServer;
        std::string fileName;
        VtkVisul visul;
        int getClientCubedimX();
        int getClientCubedimY();
        int getClientCubedimZ();
        float *clientArr;
        float *serverArr;
        int clientNX, clientNY, clientNZ,clientOffsetNX, clientOffsetNY, clientOffsetNZ;
    };

}

#endif //HDF53DConstructor_H_