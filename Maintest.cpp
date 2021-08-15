

#include "HDF5Reader.h"
#include <iostream>
#include <string>
#include <chrono>
#include "LogKeeper.h"
#include "VtkVisul.h"
#include "vtkAutoInit.h"
#include <iterator>

using namespace NDAVis;
VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2);
int main()
{
    NDAVis::LogKeeper log = NDAVis::LogKeeper("Time Taken To Open HDF5 File", true);
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
        *ptr = static_cast <float> (rand())*10 / static_cast <float> (RAND_MAX);
        ptr++;
    }

    log.UpdateLog("Time Taken To Insert Array to VTK", true);
    NDAVis::VtkVisul visul = NDAVis::VtkVisul();
    visul.InsertArray(arr, totalDim);
    log.endLog(false);

    log.UpdateLog("Time Taken To Render VTK", true);
    visul.render(reader.getXdimension(), reader.getYdimension(), reader.getZdimension(), 2, 2, 2, 50, 50, 50);
    log.endLog(false);

    return 0;
}
