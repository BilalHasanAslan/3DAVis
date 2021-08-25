

#include "HDF5Reader.h"
#include <iostream>
#include <string>
#include <chrono>
#include "LogKeeper.h"
#include "VtkVisul.h"
#include "vtkAutoInit.h"
#include <iterator>
#include "Converter.h"
#include "HDF53DConstructor.h"

using namespace NDAVis;
VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2);
int main()
{
    /*      NDAVis::LogKeeper log = NDAVis::LogKeeper("Time Taken To Open HDF5 File", true);
    NDAVis::HDF5Reader reader = NDAVis::HDF5Reader("test.hdf5");
    log.endLog(false);
    std::cout << "lol" << std::endl;
    log.UpdateLog("Time Taken To Open Dataset", true);
    reader.openDataset("0/DATA");
    log.endLog(false);

    log.UpdateLog("Time Taken To Set Dimensions", true);
    reader.setDimensions();
    log.endLog(false);

    int totalDim = reader.getXdimension() * reader.getYdimension() * reader.getZdimension();

    float *arr = new float[totalDim];
    log.UpdateLog("Time Taken To Read Set Chunk", true);
    reader.readDataset(arr, reader.getXdimension(), reader.getYdimension(), reader.getZdimension(), 0, 0, 0);
    log.endLog(false);

    float* ptr = arr;
    for (int i = 0; i < totalDim; i++)
    {
        *ptr = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        ptr++;
    }
    visul.setColor(1);
    log.UpdateLog("Time Taken To Insert Array to VTK", true);
    NDAVis::VtkVisul visul = NDAVis::VtkVisul();
    visul.InsertArray(arr, totalDim);
    log.endLog(false);

    log.UpdateLog("Time Taken To Render VTK", true);
    visul.render(reader.getXdimension(), reader.getYdimension(), reader.getZdimension(), 2, 2, 2, 50, 50, 50);
    log.endLog(false);  */

    /*       std::string inputFileName;
    std::string outputFileName;
    std::cout<<"Input FITS File name"<< std::endl;
    std::cin>>inputFileName;
    std::cout<<"Output HDF5 File name"<< std::endl;
    std::cin>>outputFileName;
    NDAVis::Converter converter = NDAVis::Converter(inputFileName, outputFileName);
    converter.convert();    */

/*     NDAVis::HDF53DConstructor constructor = HDF53DConstructor();
    constructor.setFile("nocunk2.hdf5");
    constructor.renderServer(0, 0, 0, 0, 0, 0, 1);
    constructor.setNewCordinates(5*7*5,1,1,1,1,1,1,1); */
 
    int totalDim = 640*640*640;
    float *arr = new float[640*640*640];
    float* ptr = arr;
    for (int i = 0; i < totalDim; i++)
    {
        *ptr = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        ptr++;
    }
    NDAVis::VtkVisul visul = NDAVis::VtkVisul();
    visul.setColor(1);
    visul.InsertArray(arr, totalDim);
    visul.setCamera(1, 1, 1, 1, 1, 1);
    visul.render(640,640,640,2,2,2,0,0,0); 
 
    return 0;
}
