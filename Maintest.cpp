

#include "HDF5Reader.h"
#include <iostream>
#include <string>
#include <chrono>
#include "LogKeeper.h"

using namespace NDAVis;

int main()
{   
    NDAVis::LogKeeper log = NDAVis::LogKeeper("Time Taken To Open HDF5 File",true);
    NDAVis::HDF5Reader reader = NDAVis::HDF5Reader("test.hdf5");
    log.endLog(false);

    log.UpdateLog("Time Taken To Open Dataset",true);
    reader.openDataset("0/DATA");
    log.endLog(false);

    log.UpdateLog("Time Taken To Set Dimensions",true);
    reader.setDimensions();
    log.endLog(false);

    log.UpdateLog("Time Taken To Read Set Chunk",true);
    reader.readDataset(20, 20, 20, 128, 350, 500);
    log.endLog(false);

    

    return 0;
}
