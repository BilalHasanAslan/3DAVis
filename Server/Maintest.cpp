#include "HDF5Reader.h"
#include <iostream>
#include <string>
#include <chrono>
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
    NDAVis::LogKeeper log = NDAVis::LogKeeper("Time Taken To Open HDF5 File", true);

    log.endLog(false);

    log.UpdateLog("Time Taken To Open Dataset", true);

    log.endLog(false);

    float color[] ={1,2,3};
    float opacity[] ={1,2};
    NDAVis::Controller contollerObj = Controller();
    contollerObj.setFile("lesgo2.hdf5");
    contollerObj.startServerRender(0, 0, 0, 0, 0, 0, color,3,opacity,2);



    return 0;
}
