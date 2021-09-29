#include "HDF5Reader.h"
#include <iostream>
#include <chrono>
#include <string>
#include "LogKeeper.h"
#include "VtkVisul.h"
#include "vtkAutoInit.h"
#include <iterator>
#include "Controller.h"
#include <H5Cpp.h>

using namespace NDAVis;
VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2);
int main()
{
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------

/*          int XYChunk = 64;
    int ZChunk = 64;
    HDF5Reader readerClient = HDF5Reader("250mb_1mb.hdf5");
    std::ostringstream tempname;
    tempname << "0/MipMaps/DATA/DATA_XY_" << 1 << "_Z_" << 1;
    readerClient.openDataset(tempname.str());
    readerClient.setDimensions();
    int xChunks = 1 + ((readerClient.NX - 1) / XYChunk);
    int yChunks = 1 + ((readerClient.NY - 1) / XYChunk);
    int zChunks = 1 + ((readerClient.NZ - 1) / ZChunk);
    Tiles ClientTiles = Tiles();
    int c = 1;
    int tileNum[] = {1};

    std::cout<<"1 Tile 1mb Read 250mb file"<<std::endl;
    ClientTiles.readTiles(tileNum, c, readerClient, xChunks, yChunks, zChunks);  */

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------

/*          int XYChunk = 64;
    int ZChunk = 64;
    HDF5Reader readerClient = HDF5Reader("250mb_1mb.hdf5");
    std::ostringstream tempname;
    tempname << "0/MipMaps/DATA/DATA_XY_" << 1 << "_Z_" << 1;
    readerClient.openDataset(tempname.str());
    readerClient.setDimensions();
    int xChunks = 1 + ((readerClient.NX - 1) / XYChunk);
    int yChunks = 1 + ((readerClient.NY - 1) / XYChunk);
    int zChunks = 1 + ((readerClient.NZ - 1) / ZChunk);
    Tiles ClientTiles = Tiles();
    int c = 2;
    int tileNum[] = {1,2};

    std::cout<<"2 Tile 1mb Read 250mb file"<<std::endl;
    ClientTiles.readTiles(tileNum, c, readerClient, xChunks, yChunks, zChunks);   */

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------

/*     int XYChunk = 64;
    int ZChunk = 64;
    HDF5Reader readerClient = HDF5Reader("250mb_1mb.hdf5");
    std::ostringstream tempname;
    tempname << "0/MipMaps/DATA/DATA_XY_" << 1 << "_Z_" << 1;
    readerClient.openDataset(tempname.str());
    readerClient.setDimensions();
    int xChunks = 1 + ((readerClient.NX - 1) / XYChunk);
    int yChunks = 1 + ((readerClient.NY - 1) / XYChunk);
    int zChunks = 1 + ((readerClient.NZ - 1) / ZChunk);
    Tiles ClientTiles = Tiles();
    int c = 3;
    int tileNum[] = {1,2,3};

    std::cout<<"3 Tile 1mb Read 250mb file"<<std::endl;
    ClientTiles.readTiles(tileNum, c, readerClient, xChunks, yChunks, zChunks);  */

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------

/*          int XYChunk = 64;
    int ZChunk = 64;
    HDF5Reader readerClient = HDF5Reader("250mb_1mb.hdf5");
    std::ostringstream tempname;
    tempname << "0/MipMaps/DATA/DATA_XY_" << 1 << "_Z_" << 1;
    readerClient.openDataset(tempname.str());
    readerClient.setDimensions();
    int xChunks = 1 + ((readerClient.NX - 1) / XYChunk);
    int yChunks = 1 + ((readerClient.NY - 1) / XYChunk);
    int zChunks = 1 + ((readerClient.NZ - 1) / ZChunk);
    Tiles ClientTiles = Tiles();
    int c = 4;
    int tileNum[] = {1,2,3,4};

    std::cout<<"4 Tile 1mb Read 250mb file"<<std::endl;
    ClientTiles.readTiles(tileNum, c, readerClient, xChunks, yChunks, zChunks);   */

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------
/* 
    int XYChunk = 64;
    int ZChunk = 64;
    HDF5Reader readerClient = HDF5Reader("250mb_1mb.hdf5");
    std::ostringstream tempname;
    tempname << "0/MipMaps/DATA/DATA_XY_" << 1 << "_Z_" << 1;
    readerClient.openDataset(tempname.str());
    readerClient.setDimensions();
    int xChunks = 1 + ((readerClient.NX - 1) / XYChunk);
    int yChunks = 1 + ((readerClient.NY - 1) / XYChunk);
    int zChunks = 1 + ((readerClient.NZ - 1) / ZChunk);
    Tiles ClientTiles = Tiles();
    int c = 8;
    int tileNum[] = {1,2,3,4,6,7,8};

    std::cout<<"8 Tile 1mb Read 250mb file"<<std::endl;
    ClientTiles.readTiles(tileNum, c, readerClient, xChunks, yChunks, zChunks);  */

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------

/*     int XYChunk = 64;
    int ZChunk = 64;
    HDF5Reader readerClient = HDF5Reader("500mb_1mb.hdf5");
    std::ostringstream tempname;
    tempname << "0/MipMaps/DATA/DATA_XY_" << 1 << "_Z_" << 1;
    readerClient.openDataset(tempname.str());
    readerClient.setDimensions();
    int xChunks = 1 + ((readerClient.NX - 1) / XYChunk);
    int yChunks = 1 + ((readerClient.NY - 1) / XYChunk);
    int zChunks = 1 + ((readerClient.NZ - 1) / ZChunk);
    Tiles ClientTiles = Tiles();
    int c = 1;
    int tileNum[] = {1};

    std::cout<<"1 Tile 1mb Read 500mb file"<<std::endl;
    ClientTiles.readTiles(tileNum, c, readerClient, xChunks, yChunks, zChunks); */

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------

/*     int XYChunk = 64;
    int ZChunk = 64;
    HDF5Reader readerClient = HDF5Reader("500mb_1mb.hdf5");
    std::ostringstream tempname;
    tempname << "0/MipMaps/DATA/DATA_XY_" << 1 << "_Z_" << 1;
    readerClient.openDataset(tempname.str());
    readerClient.setDimensions();
    int xChunks = 1 + ((readerClient.NX - 1) / XYChunk);
    int yChunks = 1 + ((readerClient.NY - 1) / XYChunk);
    int zChunks = 1 + ((readerClient.NZ - 1) / ZChunk);
    Tiles ClientTiles = Tiles();
    int c = 2;
    int tileNum[] = {1,2};

    std::cout<<"2 Tile 1mb Read 500mb file"<<std::endl;
    ClientTiles.readTiles(tileNum, c, readerClient, xChunks, yChunks, zChunks);    */

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------

/*     int XYChunk = 64;
    int ZChunk = 64;
    HDF5Reader readerClient = HDF5Reader("500mb_1mb.hdf5");
    std::ostringstream tempname;
    tempname << "0/MipMaps/DATA/DATA_XY_" << 1 << "_Z_" << 1;
    readerClient.openDataset(tempname.str());
    readerClient.setDimensions();
    int xChunks = 1 + ((readerClient.NX - 1) / XYChunk);
    int yChunks = 1 + ((readerClient.NY - 1) / XYChunk);
    int zChunks = 1 + ((readerClient.NZ - 1) / ZChunk);
    Tiles ClientTiles = Tiles();
    int c = 3;
    int tileNum[] = {1,2,3};

    std::cout<<"3 Tile 1mb Read 500mb file"<<std::endl;
    ClientTiles.readTiles(tileNum, c, readerClient, xChunks, yChunks, zChunks);    */

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------

/*     int XYChunk = 64;
    int ZChunk = 64;
    HDF5Reader readerClient = HDF5Reader("500mb_1mb.hdf5");
    std::ostringstream tempname;
    tempname << "0/MipMaps/DATA/DATA_XY_" << 1 << "_Z_" << 1;
    readerClient.openDataset(tempname.str());
    readerClient.setDimensions();
    int xChunks = 1 + ((readerClient.NX - 1) / XYChunk);
    int yChunks = 1 + ((readerClient.NY - 1) / XYChunk);
    int zChunks = 1 + ((readerClient.NZ - 1) / ZChunk);
    Tiles ClientTiles = Tiles();
    int c = 4;
    int tileNum[] = {1,2,3,4};

    std::cout<<"4 Tile 1mb Read 500mb file"<<std::endl;
    ClientTiles.readTiles(tileNum, c, readerClient, xChunks, yChunks, zChunks);  */

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------

/*     int XYChunk = 64;
    int ZChunk = 64;
    HDF5Reader readerClient = HDF5Reader("500mb_1mb.hdf5");
    std::ostringstream tempname;
    tempname << "0/MipMaps/DATA/DATA_XY_" << 1 << "_Z_" << 1;
    readerClient.openDataset(tempname.str());
    readerClient.setDimensions();
    int xChunks = 1 + ((readerClient.NX - 1) / XYChunk);
    int yChunks = 1 + ((readerClient.NY - 1) / XYChunk);
    int zChunks = 1 + ((readerClient.NZ - 1) / ZChunk);
    Tiles ClientTiles = Tiles();
    int c = 8;
    int tileNum[] = {1,2,3,4,5,6,7,8};

    std::cout<<"8 Tile 1mb Read 500mb file"<<std::endl;
    ClientTiles.readTiles(tileNum, c, readerClient, xChunks, yChunks, zChunks);  */

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------

/*     int XYChunk = 64;
    int ZChunk = 64;
    HDF5Reader readerClient = HDF5Reader("2000mb_1mb.hdf5");
    std::ostringstream tempname;
    tempname << "0/MipMaps/DATA/DATA_XY_" << 1 << "_Z_" << 1;
    readerClient.openDataset(tempname.str());
    readerClient.setDimensions();
    int xChunks = 1 + ((readerClient.NX - 1) / XYChunk);
    int yChunks = 1 + ((readerClient.NY - 1) / XYChunk);
    int zChunks = 1 + ((readerClient.NZ - 1) / ZChunk);
    Tiles ClientTiles = Tiles();
    int c = 1;
    int tileNum[] = {1};

    std::cout<<"1 Tile 1mb Read 2000mb file"<<std::endl;
    ClientTiles.readTiles(tileNum, c, readerClient, xChunks, yChunks, zChunks);   */

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------

/*     int XYChunk = 64;
    int ZChunk = 64;
    HDF5Reader readerClient = HDF5Reader("2000mb_1mb.hdf5");
    std::ostringstream tempname;
    tempname << "0/MipMaps/DATA/DATA_XY_" << 1 << "_Z_" << 1;
    readerClient.openDataset(tempname.str());
    readerClient.setDimensions();
    int xChunks = 1 + ((readerClient.NX - 1) / XYChunk);
    int yChunks = 1 + ((readerClient.NY - 1) / XYChunk);
    int zChunks = 1 + ((readerClient.NZ - 1) / ZChunk);
    Tiles ClientTiles = Tiles();
    int c = 2;
    int tileNum[] = {1,2};

    std::cout<<"2 Tile 1mb Read 2000mb file"<<std::endl;
    ClientTiles.readTiles(tileNum, c, readerClient, xChunks, yChunks, zChunks);  */ 

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------

/*     int XYChunk = 64;
    int ZChunk = 64;
    HDF5Reader readerClient = HDF5Reader("2000mb_1mb.hdf5");
    std::ostringstream tempname;
    tempname << "0/MipMaps/DATA/DATA_XY_" << 1 << "_Z_" << 1;
    readerClient.openDataset(tempname.str());
    readerClient.setDimensions();
    int xChunks = 1 + ((readerClient.NX - 1) / XYChunk);
    int yChunks = 1 + ((readerClient.NY - 1) / XYChunk);
    int zChunks = 1 + ((readerClient.NZ - 1) / ZChunk);
    Tiles ClientTiles = Tiles();
    int c = 3;
    int tileNum[] = {1,2,3};

    std::cout<<"3 Tile 1mb Read 2000mb file"<<std::endl;
    ClientTiles.readTiles(tileNum, c, readerClient, xChunks, yChunks, zChunks);   */

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------

/*     int XYChunk = 64;
    int ZChunk = 64;
    HDF5Reader readerClient = HDF5Reader("2000mb_1mb.hdf5");
    std::ostringstream tempname;
    tempname << "0/MipMaps/DATA/DATA_XY_" << 1 << "_Z_" << 1;
    readerClient.openDataset(tempname.str());
    readerClient.setDimensions();
    int xChunks = 1 + ((readerClient.NX - 1) / XYChunk);
    int yChunks = 1 + ((readerClient.NY - 1) / XYChunk);
    int zChunks = 1 + ((readerClient.NZ - 1) / ZChunk);
    Tiles ClientTiles = Tiles();
    int c = 4;
    int tileNum[] = {1,2,3,4};

    std::cout<<"4 Tile 1mb Read 2000mb file"<<std::endl;
    ClientTiles.readTiles(tileNum, c, readerClient, xChunks, yChunks, zChunks);   */

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------

/*     int XYChunk = 64;
    int ZChunk = 64;
    HDF5Reader readerClient = HDF5Reader("2000mb_1mb.hdf5");
    std::ostringstream tempname;
    tempname << "0/MipMaps/DATA/DATA_XY_" << 1 << "_Z_" << 1;
    readerClient.openDataset(tempname.str());
    readerClient.setDimensions();
    int xChunks = 1 + ((readerClient.NX - 1) / XYChunk);
    int yChunks = 1 + ((readerClient.NY - 1) / XYChunk);
    int zChunks = 1 + ((readerClient.NZ - 1) / ZChunk);
    Tiles ClientTiles = Tiles();
    int c = 8;
    int tileNum[] = {1,2,3,4,6,7,8};

    std::cout<<"8 Tile 1mb Read 2000mb file"<<std::endl;
    ClientTiles.readTiles(tileNum, c, readerClient, xChunks, yChunks, zChunks);  */

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------

/*     int XYChunk = 64;
    int ZChunk = 64;
    HDF5Reader readerClient = HDF5Reader("250mb_1mb.hdf5");

    std::ostringstream name;
    name << "0/MipMaps/DATA/DATA_XY_" << 1 << "_Z_" << 1;
    readerClient.openDataset(name.str());
    readerClient.setDimensions();

    int clientNX = readerClient.getXdimension();
    int clientNY = readerClient.getYdimension();
    int clientNZ = readerClient.getZdimension();

    int xChunks = 1 + ((clientNX - 1) / XYChunk);
    int yChunks = 1 + ((clientNY - 1) / XYChunk);
    int zChunks = 1 + ((clientNZ - 1) / ZChunk);
    int tileNumDim = xChunks * yChunks * zChunks;
    int *tileNum = new int[tileNumDim];
    int count = 0;
    for (int i = 0; i < tileNumDim; i++)
    {
        tileNum[i] = i + 1;
        count++;
    }
    std::cout << "Tile Num " << count << std::endl;
    Tiles clientTiles = Tiles();
    std::cout << "250 Tiles 1mb Read 250mb file" << std::endl;
    clientTiles.readTiles(tileNum, tileNumDim, readerClient, xChunks, yChunks, zChunks);

    std::cout << "250 Tiles 1mb Read Reconstruct" << std::endl;
    float *serverArr;
    int totalDim = clientNX * clientNY * clientNZ;
    serverArr = new float[totalDim];
    clientTiles.combineArray(serverArr, clientNX, clientNY, clientNZ, 0, 0, 0);

    std::chrono::high_resolution_clock::time_point t_end, t_start;
    double elapsed_time_ms;
    t_start = std::chrono::high_resolution_clock::now();

    std::cout << "250 Tiles 1mb Read Render" << std::endl;
    float color[] = {1, 2, 3};
    float opacity[] = {1, 2};
    VtkVisul visul;
    visul.setColor(color, 3, opacity, 2);
    visul.InsertArray(serverArr, totalDim);
    visul.setCamera(0, 1, 0, -0.5, -0.5, 210);
    visul.render(clientNX, clientNY, clientNZ, 2, 2, 2, 0, 0, 0);
    t_end = std::chrono::high_resolution_clock::now();
    elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time Taken To Render : " + std::to_string(elapsed_time_ms) + " ms" + " & " + std::to_string(elapsed_time_ms / 1000) + " s" << std::endl;
    t_start = std::chrono::high_resolution_clock::now();

    std::cout << "250 Tiles 1mb Get Image" << std::endl;
    visul.getImage(1);

    t_end = std::chrono::high_resolution_clock::now();
    elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time Taken To Get Image : " + std::to_string(elapsed_time_ms) + " ms" + " & " + std::to_string(elapsed_time_ms / 1000) + " s" << std::endl;
 */
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------

    /* int XYChunk = 64;
    int ZChunk = 64;
    HDF5Reader readerClient = HDF5Reader("500mb_1mb.hdf5");

    std::ostringstream name;
    name << "0/MipMaps/DATA/DATA_XY_" << 1 << "_Z_" << 1;
    readerClient.openDataset(name.str());
    readerClient.setDimensions();

    int clientNX = readerClient.getXdimension();
    int clientNY = readerClient.getYdimension();
    int clientNZ = readerClient.getZdimension();

    int xChunks = 1 + ((clientNX - 1) / XYChunk);
    int yChunks = 1 + ((clientNY - 1) / XYChunk);
    int zChunks = 1 + ((clientNZ - 1) / ZChunk);
    int tileNumDim = xChunks * yChunks * zChunks;
    int *tileNum = new int[tileNumDim];
    int count = 0;
    for (int i = 0; i < tileNumDim; i++)
    {
        tileNum[i] = i + 1;
        count++;
    }
    std::cout << "Tile Num " << count << std::endl;
    Tiles clientTiles = Tiles();
    std::cout << "500 Tiles 1mb Read 500mb file" << std::endl;
    clientTiles.readTiles(tileNum, tileNumDim, readerClient, xChunks, yChunks, zChunks);

    std::cout << "500 Tiles 1mb Read Reconstruct" << std::endl;
    float *serverArr;
    int totalDim = clientNX * clientNY * clientNZ;
    serverArr = new float[totalDim];
    clientTiles.combineArray(serverArr, clientNX, clientNY, clientNZ, 0, 0, 0);

    std::chrono::high_resolution_clock::time_point t_end, t_start;
    double elapsed_time_ms;
    t_start = std::chrono::high_resolution_clock::now();

    std::cout << "500 Tiles 1mb Read Render" << std::endl;
    float color[] = {1, 2, 3};
    float opacity[] = {1, 2};
    VtkVisul visul;
    visul.setColor(color, 3, opacity, 2);
    visul.InsertArray(serverArr, totalDim);
    visul.setCamera(0, 1, 0, -0.5, -0.5, 210);
    visul.render(clientNX, clientNY, clientNZ, 2, 2, 2, 0, 0, 0);
    t_end = std::chrono::high_resolution_clock::now();
    elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time Taken To Render : " + std::to_string(elapsed_time_ms) + " ms" + " & " + std::to_string(elapsed_time_ms / 1000) + " s" << std::endl;

    for(int i=0;i<totalDim;i++){
        serverArr[i] = ((float) rand() / (RAND_MAX)); 
    }


    t_start = std::chrono::high_resolution_clock::now();
    visul.setColor(color, 3, opacity, 2);
    visul.InsertArray(serverArr, totalDim);
    visul.setCamera(0, 1, 0, -0.5, -0.5, 210);
    visul.render(clientNX, clientNY, clientNZ, 2, 2, 2, 0, 0, 0);
    t_end = std::chrono::high_resolution_clock::now();
    elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time Taken To Render : " + std::to_string(elapsed_time_ms) + " ms" + " & " + std::to_string(elapsed_time_ms / 1000) + " s" << std::endl;

    
    t_start = std::chrono::high_resolution_clock::now();

    std::cout << "500 Tiles 1mb Get Image" << std::endl;
    visul.getImage(1);

    t_end = std::chrono::high_resolution_clock::now();
    elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time Taken To Get Image : " + std::to_string(elapsed_time_ms) + " ms" + " & " + std::to_string(elapsed_time_ms / 1000) + " s" << std::endl;  */ 

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------

/*     int XYChunk = 64;
    int ZChunk = 64;
    HDF5Reader readerClient = HDF5Reader("750mb_1mb.hdf5");

    std::ostringstream name;
    name << "0/MipMaps/DATA/DATA_XY_" << 1 << "_Z_" << 1;
    readerClient.openDataset(name.str());
    readerClient.setDimensions();

    int clientNX = readerClient.getXdimension();
    int clientNY = readerClient.getYdimension();
    int clientNZ = readerClient.getZdimension();

    int xChunks = 1 + ((clientNX - 1) / XYChunk);
    int yChunks = 1 + ((clientNY - 1) / XYChunk);
    int zChunks = 1 + ((clientNZ - 1) / ZChunk);
    int tileNumDim = xChunks * yChunks * zChunks;
    int *tileNum = new int[tileNumDim];
    int count = 0;
    for (int i = 0; i < tileNumDim; i++)
    {
        tileNum[i] = i + 1;
        count++;
    }
    std::cout << "Tile Num " << count << std::endl;
    Tiles clientTiles = Tiles();
    std::cout << "750 Tiles 1mb Read 750 file" << std::endl;
    clientTiles.readTiles(tileNum, tileNumDim, readerClient, xChunks, yChunks, zChunks);

    std::cout << "750 Tiles 1mb Read Reconstruct" << std::endl;
    float *serverArr;
    int totalDim = clientNX * clientNY * clientNZ;
    serverArr = new float[totalDim];
    clientTiles.combineArray(serverArr, clientNX, clientNY, clientNZ, 0, 0, 0);

    std::chrono::high_resolution_clock::time_point t_end, t_start;
    double elapsed_time_ms;
    t_start = std::chrono::high_resolution_clock::now();

    std::cout << "750 Tiles 1mb Read Render" << std::endl;
    float color[] = {1, 2, 3};
    float opacity[] = {1, 2};
    VtkVisul visul;
    visul.setColor(color, 3, opacity, 2);
    visul.InsertArray(serverArr, totalDim);
    visul.setCamera(0, 1, 0, -0.5, -0.5, 210);
    visul.render(clientNX, clientNY, clientNZ, 2, 2, 2, 0, 0, 0);
    t_end = std::chrono::high_resolution_clock::now();
    elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time Taken To Render : " + std::to_string(elapsed_time_ms) + " ms" + " & " + std::to_string(elapsed_time_ms / 1000) + " s" << std::endl;
    t_start = std::chrono::high_resolution_clock::now();

    std::cout << "750 Tiles 1mb Get Image" << std::endl;
    visul.getImage(1);

    t_end = std::chrono::high_resolution_clock::now();
    elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time Taken To Get Image : " + std::to_string(elapsed_time_ms) + " ms" + " & " + std::to_string(elapsed_time_ms / 1000) + " s" << std::endl; */

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------

/*     int XYChunk = 64;
    int ZChunk = 64;
    HDF5Reader readerClient = HDF5Reader("1000mb_1mb.hdf5");

    std::ostringstream name;
    name << "0/MipMaps/DATA/DATA_XY_" << 1 << "_Z_" << 1;
    readerClient.openDataset(name.str());
    readerClient.setDimensions();

    int clientNX = readerClient.getXdimension();
    int clientNY = readerClient.getYdimension();
    int clientNZ = readerClient.getZdimension();

    int xChunks = 1 + ((clientNX - 1) / XYChunk);
    int yChunks = 1 + ((clientNY - 1) / XYChunk);
    int zChunks = 1 + ((clientNZ - 1) / ZChunk);
    int tileNumDim = xChunks * yChunks * zChunks;
    int *tileNum = new int[tileNumDim];
    int count = 0;
    for (int i = 0; i < tileNumDim; i++)
    {
        tileNum[i] = i + 1;
        count++;
    }
    std::cout << "Tile Num " << count << std::endl;
    Tiles clientTiles = Tiles();
    std::cout << "1000 Tiles 1mb Read 1000 file" << std::endl;
    clientTiles.readTiles(tileNum, tileNumDim, readerClient, xChunks, yChunks, zChunks);

    std::cout << "1000 Tiles 1mb Read Reconstruct" << std::endl;
    float *serverArr;
    int totalDim = clientNX * clientNY * clientNZ;
    serverArr = new float[totalDim];
    clientTiles.combineArray(serverArr, clientNX, clientNY, clientNZ, 0, 0, 0);

    std::chrono::high_resolution_clock::time_point t_end, t_start;
    double elapsed_time_ms;
    t_start = std::chrono::high_resolution_clock::now();

    std::cout << "1000 Tiles 1mb Read Render" << std::endl;
    float color[] = {1, 2, 3};
    float opacity[] = {1, 2};
    VtkVisul visul;
    visul.setColor(color, 3, opacity, 2);
    visul.InsertArray(serverArr, totalDim);
    visul.setCamera(0, 1, 0, -0.5, -0.5, 210);
    visul.render(clientNX, clientNY, clientNZ, 2, 2, 2, 0, 0, 0);
    t_end = std::chrono::high_resolution_clock::now();
    elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time Taken To Render : " + std::to_string(elapsed_time_ms) + " ms" + " & " + std::to_string(elapsed_time_ms / 1000) + " s" << std::endl;
    t_start = std::chrono::high_resolution_clock::now();

    std::cout << "1000 Tiles 1mb Get Image" << std::endl;
    visul.getImage(1);

    t_end = std::chrono::high_resolution_clock::now();
    elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time Taken To Get Image : " + std::to_string(elapsed_time_ms) + " ms" + " & " + std::to_string(elapsed_time_ms / 1000) + " s" << std::endl; */

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------

/*     int XYChunk = 64;
    int ZChunk = 64;
    HDF5Reader readerClient = HDF5Reader("2000mb_1mb.hdf5");

    std::ostringstream name;
    name << "0/MipMaps/DATA/DATA_XY_" << 1 << "_Z_" << 1;
    readerClient.openDataset(name.str());
    readerClient.setDimensions();

    int clientNX = readerClient.getXdimension();
    int clientNY = readerClient.getYdimension();
    int clientNZ = readerClient.getZdimension();

    int xChunks = 1 + ((clientNX - 1) / XYChunk);
    int yChunks = 1 + ((clientNY - 1) / XYChunk);
    int zChunks = 1 + ((clientNZ - 1) / ZChunk);
    int tileNumDim = xChunks * yChunks * zChunks;
    int *tileNum = new int[tileNumDim];
    int count = 0;
    for (int i = 0; i < tileNumDim; i++)
    {
        tileNum[i] = i + 1;
        count++;
    }
    std::cout << "Tile Num " << count << std::endl;
    Tiles clientTiles = Tiles();
    std::cout << "2000 Tiles 1mb Read 2000 file" << std::endl;
    clientTiles.readTiles(tileNum, tileNumDim, readerClient, xChunks, yChunks, zChunks);

    std::cout << "2000 Tiles 1mb Read Reconstruct" << std::endl;
    float *serverArr;
    int totalDim = clientNX * clientNY * clientNZ;
    serverArr = new float[totalDim];
    clientTiles.combineArray(serverArr, clientNX, clientNY, clientNZ, 0, 0, 0);

    std::chrono::high_resolution_clock::time_point t_end, t_start;
    double elapsed_time_ms;
    t_start = std::chrono::high_resolution_clock::now();

    std::cout << "2000 Tiles 1mb Read Render" << std::endl;
    float color[] = {1, 2, 3};
    float opacity[] = {1, 2};
    VtkVisul visul;
    visul.setColor(color, 3, opacity, 2);
    visul.InsertArray(serverArr, totalDim);
    visul.setCamera(0, 1, 0, -0.5, -0.5, 210);
    visul.render(clientNX, clientNY, clientNZ, 2, 2, 2, 0, 0, 0);
    t_end = std::chrono::high_resolution_clock::now();
    elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time Taken To Render : " + std::to_string(elapsed_time_ms) + " ms" + " & " + std::to_string(elapsed_time_ms / 1000) + " s" << std::endl;
    t_start = std::chrono::high_resolution_clock::now();

    std::cout << "2000 Tiles 1mb Get Image" << std::endl;
    visul.getImage(1);

    t_end = std::chrono::high_resolution_clock::now();
    elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time Taken To Get Image : " + std::to_string(elapsed_time_ms) + " ms" + " & " + std::to_string(elapsed_time_ms / 1000) + " s" << std::endl; */

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------
        //-----------------------------------------------------------------------------------------------------------------------------------------------------------------
            //-----------------------------------------------------------------------------------------------------------------------------------------------------------------
                //-----------------------------------------------------------------------------------------------------------------------------------------------------------------

/*     int XYChunk = 64;
    int ZChunk = 32;
    HDF5Reader readerClient = HDF5Reader("250mb_0.5mb.hdf5");

    std::ostringstream name;
    name << "0/MipMaps/DATA/DATA_XY_" << 1 << "_Z_" << 1;
    readerClient.openDataset(name.str());
    readerClient.setDimensions();

    int clientNX = readerClient.getXdimension();
    int clientNY = readerClient.getYdimension();
    int clientNZ = readerClient.getZdimension();

    int xChunks = 1 + ((clientNX - 1) / XYChunk);
    int yChunks = 1 + ((clientNY - 1) / XYChunk);
    int zChunks = 1 + ((clientNZ - 1) / ZChunk);
    int tileNumDim = xChunks * yChunks * zChunks;
    int *tileNum = new int[tileNumDim];
    int count = 0;
    for (int i = 0; i < tileNumDim; i++)
    {
        tileNum[i] = i + 1;
        count++;
    }
    std::cout << "Tile Num " << count << std::endl;
    Tiles clientTiles = Tiles();
    std::cout << "250 Tiles 0.5mb Read 250mb file" << std::endl;
    clientTiles.readTiles(tileNum, tileNumDim, readerClient, xChunks, yChunks, zChunks);

    std::cout << "250 Tiles 0.5mb Read Reconstruct" << std::endl;
    float *serverArr;
    int totalDim = clientNX * clientNY * clientNZ;
    serverArr = new float[totalDim];
    clientTiles.combineArray(serverArr, clientNX, clientNY, clientNZ, 0, 0, 0);

    std::chrono::high_resolution_clock::time_point t_end, t_start;
    double elapsed_time_ms;
    t_start = std::chrono::high_resolution_clock::now();

    std::cout << "250 Tiles 0.5mb Read Render" << std::endl;
    float color[] = {1, 2, 3};
    float opacity[] = {1, 2};
    VtkVisul visul;
    visul.setColor(color, 3, opacity, 2);
    visul.InsertArray(serverArr, totalDim);
    visul.setCamera(0, 1, 0, -0.5, -0.5, 210);
    visul.render(clientNX, clientNY, clientNZ, 2, 2, 2, 0, 0, 0);
    t_end = std::chrono::high_resolution_clock::now();
    elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time Taken To Render : " + std::to_string(elapsed_time_ms) + " ms" + " & " + std::to_string(elapsed_time_ms / 1000) + " s" << std::endl;
    t_start = std::chrono::high_resolution_clock::now();

    std::cout << "250 Tiles 0.5mb Get Image" << std::endl;
    visul.getImage(1);

    t_end = std::chrono::high_resolution_clock::now();
    elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time Taken To Get Image : " + std::to_string(elapsed_time_ms) + " ms" + " & " + std::to_string(elapsed_time_ms / 1000) + " s" << std::endl; */
 
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------

/*     int XYChunk = 64;
    int ZChunk = 32;
    HDF5Reader readerClient = HDF5Reader("500mb_0.5mb.hdf5");

    std::ostringstream name;
    name << "0/MipMaps/DATA/DATA_XY_" << 1 << "_Z_" << 1;
    readerClient.openDataset(name.str());
    readerClient.setDimensions();

    int clientNX = readerClient.getXdimension();
    int clientNY = readerClient.getYdimension();
    int clientNZ = readerClient.getZdimension();

    int xChunks = 1 + ((clientNX - 1) / XYChunk);
    int yChunks = 1 + ((clientNY - 1) / XYChunk);
    int zChunks = 1 + ((clientNZ - 1) / ZChunk);
    int tileNumDim = xChunks * yChunks * zChunks;
    int *tileNum = new int[tileNumDim];
    int count = 0;
    for (int i = 0; i < tileNumDim; i++)
    {
        tileNum[i] = i + 1;
        count++;
    }
    std::cout << "Tile Num " << count << std::endl;
    Tiles clientTiles = Tiles();
    std::cout << "500 Tiles 0.5mb Read 500mb file" << std::endl;
    clientTiles.readTiles(tileNum, tileNumDim, readerClient, xChunks, yChunks, zChunks);

    std::cout << "500 Tiles 0.5mb Read Reconstruct" << std::endl;
    float *serverArr;
    int totalDim = clientNX * clientNY * clientNZ;
    serverArr = new float[totalDim];
    clientTiles.combineArray(serverArr, clientNX, clientNY, clientNZ, 0, 0, 0);

    std::chrono::high_resolution_clock::time_point t_end, t_start;
    double elapsed_time_ms;
    t_start = std::chrono::high_resolution_clock::now();

    std::cout << "500 Tiles 0.5mb Read Render" << std::endl;
    float color[] = {1, 2, 3};
    float opacity[] = {1, 2};
    VtkVisul visul;
    visul.setColor(color, 3, opacity, 2);
    visul.InsertArray(serverArr, totalDim);
    visul.setCamera(0, 1, 0, -0.5, -0.5, 210);
    visul.render(clientNX, clientNY, clientNZ, 2, 2, 2, 0, 0, 0);
    t_end = std::chrono::high_resolution_clock::now();
    elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time Taken To Render : " + std::to_string(elapsed_time_ms) + " ms" + " & " + std::to_string(elapsed_time_ms / 1000) + " s" << std::endl;
    t_start = std::chrono::high_resolution_clock::now();

    std::cout << "500 Tiles 0.5mb Get Image" << std::endl;
    visul.getImage(1);

    t_end = std::chrono::high_resolution_clock::now();
    elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time Taken To Get Image : " + std::to_string(elapsed_time_ms) + " ms" + " & " + std::to_string(elapsed_time_ms / 1000) + " s" << std::endl;  */

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------

/*     int XYChunk = 64;
    int ZChunk = 32;
    HDF5Reader readerClient = HDF5Reader("750mb_0.5mb.hdf5");

    std::ostringstream name;
    name << "0/MipMaps/DATA/DATA_XY_" << 1 << "_Z_" << 1;
    readerClient.openDataset(name.str());
    readerClient.setDimensions();

    int clientNX = readerClient.getXdimension();
    int clientNY = readerClient.getYdimension();
    int clientNZ = readerClient.getZdimension();

    int xChunks = 1 + ((clientNX - 1) / XYChunk);
    int yChunks = 1 + ((clientNY - 1) / XYChunk);
    int zChunks = 1 + ((clientNZ - 1) / ZChunk);
    int tileNumDim = xChunks * yChunks * zChunks;
    int *tileNum = new int[tileNumDim];
    int count = 0;
    for (int i = 0; i < tileNumDim; i++)
    {
        tileNum[i] = i + 1;
        count++;
    }
    std::cout << "Tile Num " << count << std::endl;
    Tiles clientTiles = Tiles();
    std::cout << "750 Tiles 0.5mb Read 750 file" << std::endl;
    clientTiles.readTiles(tileNum, tileNumDim, readerClient, xChunks, yChunks, zChunks);

    std::cout << "750 Tiles 0.5mb Read Reconstruct" << std::endl;
    float *serverArr;
    int totalDim = clientNX * clientNY * clientNZ;
    serverArr = new float[totalDim];
    clientTiles.combineArray(serverArr, clientNX, clientNY, clientNZ, 0, 0, 0);

    std::chrono::high_resolution_clock::time_point t_end, t_start;
    double elapsed_time_ms;
    t_start = std::chrono::high_resolution_clock::now();

    std::cout << "750 Tiles 0.5mb Read Render" << std::endl;
    float color[] = {1, 2, 3};
    float opacity[] = {1, 2};
    VtkVisul visul;
    visul.setColor(color, 3, opacity, 2);
    visul.InsertArray(serverArr, totalDim);
    visul.setCamera(0, 1, 0, -0.5, -0.5, 210);
    visul.render(clientNX, clientNY, clientNZ, 2, 2, 2, 0, 0, 0);
    t_end = std::chrono::high_resolution_clock::now();
    elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time Taken To Render : " + std::to_string(elapsed_time_ms) + " ms" + " & " + std::to_string(elapsed_time_ms / 1000) + " s" << std::endl;
    t_start = std::chrono::high_resolution_clock::now();

    std::cout << "750 Tiles 0.5mb Get Image" << std::endl;
    visul.getImage(1);

    t_end = std::chrono::high_resolution_clock::now();
    elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time Taken To Get Image : " + std::to_string(elapsed_time_ms) + " ms" + " & " + std::to_string(elapsed_time_ms / 1000) + " s" << std::endl;  */

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------

    /* int XYChunk = 64;
    int ZChunk = 32;
    HDF5Reader readerClient = HDF5Reader("1000mb_0.5mb.hdf5");

    std::ostringstream name;
    name << "0/MipMaps/DATA/DATA_XY_" << 1 << "_Z_" << 1;
    readerClient.openDataset(name.str());
    readerClient.setDimensions();

    int clientNX = readerClient.getXdimension();
    int clientNY = readerClient.getYdimension();
    int clientNZ = readerClient.getZdimension();

    int xChunks = 1 + ((clientNX - 1) / XYChunk);
    int yChunks = 1 + ((clientNY - 1) / XYChunk);
    int zChunks = 1 + ((clientNZ - 1) / ZChunk);
    int tileNumDim = xChunks * yChunks * zChunks;
    int *tileNum = new int[tileNumDim];
    int count = 0;
    for (int i = 0; i < tileNumDim; i++)
    {
        tileNum[i] = i + 1;
        count++;
    }
    std::cout << "Tile Num " << count << std::endl;
    Tiles clientTiles = Tiles();
    std::cout << "1000 Tiles 0.5mb Read 1000 file" << std::endl;
    clientTiles.readTiles(tileNum, tileNumDim, readerClient, xChunks, yChunks, zChunks);

    std::cout << "1000 Tiles 0.5mb Read Reconstruct" << std::endl;
    float *serverArr;
    int totalDim = clientNX * clientNY * clientNZ;
    serverArr = new float[totalDim];
    clientTiles.combineArray(serverArr, clientNX, clientNY, clientNZ, 0, 0, 0);

    std::chrono::high_resolution_clock::time_point t_end, t_start;
    double elapsed_time_ms;
    t_start = std::chrono::high_resolution_clock::now();

    std::cout << "1000 Tiles 0.5mb Read Render" << std::endl;
    float color[] = {1, 2, 3};
    float opacity[] = {1, 2};
    VtkVisul visul;
    visul.setColor(color, 3, opacity, 2);
    visul.InsertArray(serverArr, totalDim);
    visul.setCamera(0, 1, 0, -0.5, -0.5, 210);
    visul.render(clientNX, clientNY, clientNZ, 2, 2, 2, 0, 0, 0);
    t_end = std::chrono::high_resolution_clock::now();
    elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time Taken To Render : " + std::to_string(elapsed_time_ms) + " ms" + " & " + std::to_string(elapsed_time_ms / 1000) + " s" << std::endl;
    t_start = std::chrono::high_resolution_clock::now();

    std::cout << "1000 Tiles 0.5mb Get Image" << std::endl;
    visul.getImage(1);

    t_end = std::chrono::high_resolution_clock::now();
    elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time Taken To Get Image : " + std::to_string(elapsed_time_ms) + " ms" + " & " + std::to_string(elapsed_time_ms / 1000) + " s" << std::endl;  */

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------

    /* int XYChunk = 64;
    int ZChunk = 32;
    HDF5Reader readerClient = HDF5Reader("2000mb_0.5mb.hdf5");

    std::ostringstream name;
    name << "0/MipMaps/DATA/DATA_XY_" << 1 << "_Z_" << 1;
    readerClient.openDataset(name.str());
    readerClient.setDimensions();

    int clientNX = readerClient.getXdimension();
    int clientNY = readerClient.getYdimension();
    int clientNZ = readerClient.getZdimension();

    int xChunks = 1 + ((clientNX - 1) / XYChunk);
    int yChunks = 1 + ((clientNY - 1) / XYChunk);
    int zChunks = 1 + ((clientNZ - 1) / ZChunk);
    int tileNumDim = xChunks * yChunks * zChunks;
    int *tileNum = new int[tileNumDim];
    int count = 0;
    for (int i = 0; i < tileNumDim; i++)
    {
        tileNum[i] = i + 1;
        count++;
    }
    std::cout << "Tile Num " << count << std::endl;
    Tiles clientTiles = Tiles();
    std::cout << "2000 Tiles 0.5mb Read 2000 file" << std::endl;
    clientTiles.readTiles(tileNum, tileNumDim, readerClient, xChunks, yChunks, zChunks);

    std::cout << "2000 Tiles 0.5mb Read Reconstruct" << std::endl;
    float *serverArr;
    int totalDim = clientNX * clientNY * clientNZ;
    serverArr = new float[totalDim];
    clientTiles.combineArray(serverArr, clientNX, clientNY, clientNZ, 0, 0, 0);

    std::chrono::high_resolution_clock::time_point t_end, t_start;
    double elapsed_time_ms;
    t_start = std::chrono::high_resolution_clock::now();

    std::cout << "2000 Tiles 0.5mb Read Render" << std::endl;
    float color[] = {1, 2, 3};
    float opacity[] = {1, 2};
    VtkVisul visul;
    visul.setColor(color, 3, opacity, 2);
    visul.InsertArray(serverArr, totalDim);
    visul.setCamera(0, 1, 0, -0.5, -0.5, 210);
    visul.render(clientNX, clientNY, clientNZ, 2, 2, 2, 0, 0, 0);
    t_end = std::chrono::high_resolution_clock::now();
    elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time Taken To Render : " + std::to_string(elapsed_time_ms) + " ms" + " & " + std::to_string(elapsed_time_ms / 1000) + " s" << std::endl;
    t_start = std::chrono::high_resolution_clock::now();

    std::cout << "2000 Tiles 0.5mb Get Image" << std::endl;
    visul.getImage(1);

    t_end = std::chrono::high_resolution_clock::now();
    elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time Taken To Get Image : " + std::to_string(elapsed_time_ms) + " ms" + " & " + std::to_string(elapsed_time_ms / 1000) + " s" << std::endl;  */

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------
        //-----------------------------------------------------------------------------------------------------------------------------------------------------------------
            //-----------------------------------------------------------------------------------------------------------------------------------------------------------------
                //-----------------------------------------------------------------------------------------------------------------------------------------------------------------

/*     int XYChunk = 64;
    int ZChunk = 128;
    HDF5Reader readerClient = HDF5Reader("250mb_2mb.hdf5");

    std::ostringstream name;
    name << "0/MipMaps/DATA/DATA_XY_" << 1 << "_Z_" << 1;
    readerClient.openDataset(name.str());
    readerClient.setDimensions();

    int clientNX = readerClient.getXdimension();
    int clientNY = readerClient.getYdimension();
    int clientNZ = readerClient.getZdimension();

    int xChunks = 1 + ((clientNX - 1) / XYChunk);
    int yChunks = 1 + ((clientNY - 1) / XYChunk);
    int zChunks = 1 + ((clientNZ - 1) / ZChunk);
    int tileNumDim = xChunks * yChunks * zChunks;
    int *tileNum = new int[tileNumDim];
    int count = 0;
    for (int i = 0; i < tileNumDim; i++)
    {
        tileNum[i] = i + 1;
        count++;
    }
    std::cout << "Tile Num " << count << std::endl;
    Tiles clientTiles = Tiles();
    std::cout << "250 Tiles 2mb Read 250mb file" << std::endl;
    clientTiles.readTiles(tileNum, tileNumDim, readerClient, xChunks, yChunks, zChunks);

    std::cout << "250 Tiles 2mb Read Reconstruct" << std::endl;
    float *serverArr;
    int totalDim = clientNX * clientNY * clientNZ;
    serverArr = new float[totalDim];
    clientTiles.combineArray(serverArr, clientNX, clientNY, clientNZ, 0, 0, 0);

    std::chrono::high_resolution_clock::time_point t_end, t_start;
    double elapsed_time_ms;
    t_start = std::chrono::high_resolution_clock::now();

    std::cout << "250 Tiles 2mb Read Render" << std::endl;
    float color[] = {1, 2, 3};
    float opacity[] = {1, 2};
    VtkVisul visul;
    visul.setColor(color, 3, opacity, 2);
    visul.InsertArray(serverArr, totalDim);
    visul.setCamera(0, 1, 0, -0.5, -0.5, 210);
    visul.render(clientNX, clientNY, clientNZ, 2, 2, 2, 0, 0, 0);
    t_end = std::chrono::high_resolution_clock::now();
    elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time Taken To Render : " + std::to_string(elapsed_time_ms) + " ms" + " & " + std::to_string(elapsed_time_ms / 1000) + " s" << std::endl;
    t_start = std::chrono::high_resolution_clock::now();

    std::cout << "250 Tiles 2mb Get Image" << std::endl;
    visul.getImage(1);

    t_end = std::chrono::high_resolution_clock::now();
    elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time Taken To Get Image : " + std::to_string(elapsed_time_ms) + " ms" + " & " + std::to_string(elapsed_time_ms / 1000) + " s" << std::endl;  */
 
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------

    /* int XYChunk = 64;
    int ZChunk = 128;
    HDF5Reader readerClient = HDF5Reader("500mb_2mb.hdf5");

    std::ostringstream name;
    name << "0/MipMaps/DATA/DATA_XY_" << 1 << "_Z_" << 1;
    readerClient.openDataset(name.str());
    readerClient.setDimensions();

    int clientNX = readerClient.getXdimension();
    int clientNY = readerClient.getYdimension();
    int clientNZ = readerClient.getZdimension();

    int xChunks = 1 + ((clientNX - 1) / XYChunk);
    int yChunks = 1 + ((clientNY - 1) / XYChunk);
    int zChunks = 1 + ((clientNZ - 1) / ZChunk);
    int tileNumDim = xChunks * yChunks * zChunks;
    int *tileNum = new int[tileNumDim];
    int count = 0;
    for (int i = 0; i < tileNumDim; i++)
    {
        tileNum[i] = i + 1;
        count++;
    }
    std::cout << "Tile Num " << count << std::endl;
    Tiles clientTiles = Tiles();
    std::cout << "500 Tiles 2mb Read 500mb file" << std::endl;
    clientTiles.readTiles(tileNum, tileNumDim, readerClient, xChunks, yChunks, zChunks);

    std::cout << "500 Tiles 2mb Read Reconstruct" << std::endl;
    float *serverArr;
    int totalDim = clientNX * clientNY * clientNZ;
    serverArr = new float[totalDim];
    clientTiles.combineArray(serverArr, clientNX, clientNY, clientNZ, 0, 0, 0);

    std::chrono::high_resolution_clock::time_point t_end, t_start;
    double elapsed_time_ms;
    t_start = std::chrono::high_resolution_clock::now();

    std::cout << "500 Tiles 2mb Read Render" << std::endl;
    float color[] = {1, 2, 3};
    float opacity[] = {1, 2};
    VtkVisul visul;
    visul.setColor(color, 3, opacity, 2);
    visul.InsertArray(serverArr, totalDim);
    visul.setCamera(0, 1, 0, -0.5, -0.5, 210);
    visul.render(clientNX, clientNY, clientNZ, 2, 2, 2, 0, 0, 0);
    t_end = std::chrono::high_resolution_clock::now();
    elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time Taken To Render : " + std::to_string(elapsed_time_ms) + " ms" + " & " + std::to_string(elapsed_time_ms / 1000) + " s" << std::endl;
    t_start = std::chrono::high_resolution_clock::now();

    std::cout << "500 Tiles 2mb Get Image" << std::endl;
    visul.getImage(1);

    t_end = std::chrono::high_resolution_clock::now();
    elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time Taken To Get Image : " + std::to_string(elapsed_time_ms) + " ms" + " & " + std::to_string(elapsed_time_ms / 1000) + " s" << std::endl;  
 */
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------

    /* int XYChunk = 64;
    int ZChunk = 128;
    HDF5Reader readerClient = HDF5Reader("750mb_2mb.hdf5");

    std::ostringstream name;
    name << "0/MipMaps/DATA/DATA_XY_" << 1 << "_Z_" << 1;
    readerClient.openDataset(name.str());
    readerClient.setDimensions();

    int clientNX = readerClient.getXdimension();
    int clientNY = readerClient.getYdimension();
    int clientNZ = readerClient.getZdimension();

    int xChunks = 1 + ((clientNX - 1) / XYChunk);
    int yChunks = 1 + ((clientNY - 1) / XYChunk);
    int zChunks = 1 + ((clientNZ - 1) / ZChunk);
    int tileNumDim = xChunks * yChunks * zChunks;
    int *tileNum = new int[tileNumDim];
    int count = 0;
    for (int i = 0; i < tileNumDim; i++)
    {
        tileNum[i] = i + 1;
        count++;
    }
    std::cout << "Tile Num " << count << std::endl;
    Tiles clientTiles = Tiles();
    std::cout << "750 Tiles 2mb Read 750 file" << std::endl;
    clientTiles.readTiles(tileNum, tileNumDim, readerClient, xChunks, yChunks, zChunks);

    std::cout << "750 Tiles 2mb Read Reconstruct" << std::endl;
    float *serverArr;
    int totalDim = clientNX * clientNY * clientNZ;
    serverArr = new float[totalDim];
    clientTiles.combineArray(serverArr, clientNX, clientNY, clientNZ, 0, 0, 0);

    std::chrono::high_resolution_clock::time_point t_end, t_start;
    double elapsed_time_ms;
    t_start = std::chrono::high_resolution_clock::now();

    std::cout << "750 Tiles 2mb Read Render" << std::endl;
    float color[] = {1, 2, 3};
    float opacity[] = {1, 2};
    VtkVisul visul;
    visul.setColor(color, 3, opacity, 2);
    visul.InsertArray(serverArr, totalDim);
    visul.setCamera(0, 1, 0, -0.5, -0.5, 210);
    visul.render(clientNX, clientNY, clientNZ, 2, 2, 2, 0, 0, 0);
    t_end = std::chrono::high_resolution_clock::now();
    elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time Taken To Render : " + std::to_string(elapsed_time_ms) + " ms" + " & " + std::to_string(elapsed_time_ms / 1000) + " s" << std::endl;
    t_start = std::chrono::high_resolution_clock::now();

    std::cout << "750 Tiles 2mb Get Image" << std::endl;
    visul.getImage(1);

    t_end = std::chrono::high_resolution_clock::now();
    elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time Taken To Get Image : " + std::to_string(elapsed_time_ms) + " ms" + " & " + std::to_string(elapsed_time_ms / 1000) + " s" << std::endl;   */

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------

/*     int XYChunk = 64;
    int ZChunk = 128;
    HDF5Reader readerClient = HDF5Reader("1000mb_2mb.hdf5");

    std::ostringstream name;
    name << "0/MipMaps/DATA/DATA_XY_" << 1 << "_Z_" << 1;
    readerClient.openDataset(name.str());
    readerClient.setDimensions();

    int clientNX = readerClient.getXdimension();
    int clientNY = readerClient.getYdimension();
    int clientNZ = readerClient.getZdimension();

    int xChunks = 1 + ((clientNX - 1) / XYChunk);
    int yChunks = 1 + ((clientNY - 1) / XYChunk);
    int zChunks = 1 + ((clientNZ - 1) / ZChunk);
    int tileNumDim = xChunks * yChunks * zChunks;
    int *tileNum = new int[tileNumDim];
    int count = 0;
    for (int i = 0; i < tileNumDim; i++)
    {
        tileNum[i] = i + 1;
        count++;
    }
    std::cout << "Tile Num " << count << std::endl;
    Tiles clientTiles = Tiles();
    std::cout << "1000 Tiles 2mb Read 1000 file" << std::endl;
    clientTiles.readTiles(tileNum, tileNumDim, readerClient, xChunks, yChunks, zChunks);

    std::cout << "1000 Tiles 2mb Read Reconstruct" << std::endl;
    float *serverArr;
    int totalDim = clientNX * clientNY * clientNZ;
    serverArr = new float[totalDim];
    clientTiles.combineArray(serverArr, clientNX, clientNY, clientNZ, 0, 0, 0);

    std::chrono::high_resolution_clock::time_point t_end, t_start;
    double elapsed_time_ms;
    t_start = std::chrono::high_resolution_clock::now();

    std::cout << "1000 Tiles 2mb Read Render" << std::endl;
    float color[] = {1, 2, 3};
    float opacity[] = {1, 2};
    VtkVisul visul;
    visul.setColor(color, 3, opacity, 2);
    visul.InsertArray(serverArr, totalDim);
    visul.setCamera(0, 1, 0, -0.5, -0.5, 210);
    visul.render(clientNX, clientNY, clientNZ, 2, 2, 2, 0, 0, 0);
    t_end = std::chrono::high_resolution_clock::now();
    elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time Taken To Render : " + std::to_string(elapsed_time_ms) + " ms" + " & " + std::to_string(elapsed_time_ms / 1000) + " s" << std::endl;
    t_start = std::chrono::high_resolution_clock::now();

    std::cout << "1000 Tiles 2mb Get Image" << std::endl;
    visul.getImage(1);

    t_end = std::chrono::high_resolution_clock::now();
    elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time Taken To Get Image : " + std::to_string(elapsed_time_ms) + " ms" + " & " + std::to_string(elapsed_time_ms / 1000) + " s" << std::endl;  */

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------

/*     int XYChunk = 64;
    int ZChunk = 128;
    HDF5Reader readerClient = HDF5Reader("2000mb_2mb.hdf5");

    std::ostringstream name;
    name << "0/MipMaps/DATA/DATA_XY_" << 1 << "_Z_" << 1;
    readerClient.openDataset(name.str());
    readerClient.setDimensions();

    int clientNX = readerClient.getXdimension();
    int clientNY = readerClient.getYdimension();
    int clientNZ = readerClient.getZdimension();

    int xChunks = 1 + ((clientNX - 1) / XYChunk);
    int yChunks = 1 + ((clientNY - 1) / XYChunk);
    int zChunks = 1 + ((clientNZ - 1) / ZChunk);
    int tileNumDim = xChunks * yChunks * zChunks;
    int *tileNum = new int[tileNumDim];
    int count = 0;
    for (int i = 0; i < tileNumDim; i++)
    {
        tileNum[i] = i + 1;
        count++;
    }
    std::cout << "Tile Num " << count << std::endl;
    Tiles clientTiles = Tiles();
    std::cout << "2000 Tiles 2mb Read 2000 file" << std::endl;
    clientTiles.readTiles(tileNum, tileNumDim, readerClient, xChunks, yChunks, zChunks);

    std::cout << "2000 Tiles 2mb Read Reconstruct" << std::endl;
    float *serverArr;
    int totalDim = clientNX * clientNY * clientNZ;
    serverArr = new float[totalDim];
    clientTiles.combineArray(serverArr, clientNX, clientNY, clientNZ, 0, 0, 0);

    std::chrono::high_resolution_clock::time_point t_end, t_start;
    double elapsed_time_ms;
    t_start = std::chrono::high_resolution_clock::now();

    std::cout << "2000 Tiles 2mb Read Render" << std::endl;
    float color[] = {1, 2, 3};
    float opacity[] = {1, 2};
    VtkVisul visul;
    visul.setColor(color, 3, opacity, 2);
    visul.InsertArray(serverArr, totalDim);
    visul.setCamera(0, 1, 0, -0.5, -0.5, 210);
    visul.render(clientNX, clientNY, clientNZ, 2, 2, 2, 0, 0, 0);
    t_end = std::chrono::high_resolution_clock::now();
    elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time Taken To Render : " + std::to_string(elapsed_time_ms) + " ms" + " & " + std::to_string(elapsed_time_ms / 1000) + " s" << std::endl;
    t_start = std::chrono::high_resolution_clock::now();

    std::cout << "2000 Tiles 2mb Get Image" << std::endl;
    visul.getImage(1);

    t_end = std::chrono::high_resolution_clock::now();
    elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time Taken To Get Image : " + std::to_string(elapsed_time_ms) + " ms" + " & " + std::to_string(elapsed_time_ms / 1000) + " s" << std::endl;   */

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------
        //-----------------------------------------------------------------------------------------------------------------------------------------------------------------
            //-----------------------------------------------------------------------------------------------------------------------------------------------------------------
                //-----------------------------------------------------------------------------------------------------------------------------------------------------------------

    /* int XYChunk = 64;
    int ZChunk = 64;
    HDF5Reader readerClient = HDF5Reader("lesgo2.hdf5");

    std::ostringstream name;
    name << "0/MipMaps/DATA/DATA_XY_" << 1 << "_Z_" << 1;
    readerClient.openDataset(name.str());
    readerClient.setDimensions();

    int clientNX = readerClient.getXdimension();
    int clientNY = readerClient.getYdimension();
    int clientNZ = readerClient.getZdimension();

    int xChunks = 1 + ((clientNX - 1) / XYChunk);
    int yChunks = 1 + ((clientNY - 1) / XYChunk);
    int zChunks = 1 + ((clientNZ - 1) / ZChunk);
    int tileNumDim = xChunks * yChunks * zChunks;
    int *tileNum = new int[tileNumDim];
    int count = 0;
    for (int i = 0; i < tileNumDim; i++)
    {
        tileNum[i] = i + 1;
        count++;
    }
    std::cout << "Tile Num " << count << std::endl;
    Tiles clientTiles = Tiles();
    std::cout << "500 Tiles 1mb Read 500mb file" << std::endl;
    clientTiles.readTiles(tileNum, tileNumDim, readerClient, xChunks, yChunks, zChunks);

    std::cout << "500 Tiles 1mb Read Reconstruct" << std::endl;
    float *serverArr;
    int totalDim = clientNX * clientNY * clientNZ;
    serverArr = new float[totalDim];
    clientTiles.combineArray(serverArr, clientNX, clientNY, clientNZ, 0, 0, 0);

    std::chrono::high_resolution_clock::time_point t_end, t_start;
    double elapsed_time_ms;
    t_start = std::chrono::high_resolution_clock::now();

    std::cout << "500 Tiles 1mb Read Render" << std::endl;
    float color[] = {1, 2, 3};
    float opacity[] = {1, 2};
    VtkVisul visul;
    visul.setColor(color, 3, opacity, 2);
    visul.InsertArray(serverArr, totalDim);
    visul.setCamera(0, 1, 0, -0.5, -0.5, 210);
    visul.render(clientNX, clientNY, clientNZ, 1, 1, 1, 0, 0, 0);
    t_end = std::chrono::high_resolution_clock::now();
    elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time Taken To Render : " + std::to_string(elapsed_time_ms) + " ms" + " & " + std::to_string(elapsed_time_ms / 1000) + " s" << std::endl;

    
    t_start = std::chrono::high_resolution_clock::now();

    std::cout << "500 Tiles 1mb Get Image" << std::endl;
    visul.getImage(1);

    t_end = std::chrono::high_resolution_clock::now();
    elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time Taken To Get Image : " + std::to_string(elapsed_time_ms) + " ms" + " & " + std::to_string(elapsed_time_ms / 1000) + " s" << std::endl; 


 */











    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------
    /*  NDAVis::LogKeeper log = NDAVis::LogKeeper("Time Taken To Read 1 Client Tiles", true);
    log.endLog(false);

    log.UpdateLog("Time Taken To Read 2 Client Tiles", true);

    log.endLog(false); */

/*     float color[] ={1,2,3};
    float opacity[] ={1,2};
    NDAVis::Controller contollerObj = Controller();
    contollerObj.setFile("lesgo2.hdf5");

    contollerObj.startServerRender(0, 0, 0, 0, 0, 0, color,3,opacity,2);

    contollerObj.setCameraView(0,1,0,-0.5,-0.5,210);
    contollerObj.getImage();
    
    contollerObj.setNewCordinates(42374751,42375033,42651951,42652233,1232244751,123225033,123501951,123502233); */

    return 0;
}
