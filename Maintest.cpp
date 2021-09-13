#include "HDF5Reader.h"
#include <iostream>
#include <string>
#include <chrono>
#include "LogKeeper.h"
#include "VtkVisul.h"
#include "vtkAutoInit.h"
#include <iterator>
#include "Converter.h"
#include "Controller.h"
#include <H5Cpp.h>

using namespace NDAVis;
VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2);
int main()
{
    /*NDAVis::LogKeeper log = NDAVis::LogKeeper("Time Taken To Open HDF5 File", true);
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

/*  std::string inputFileName;
    std::string outputFileName;
    std::cout<<"Input FITS File name"<< std::endl;
    std::cin>>inputFileName;
    std::cout<<"Output HDF5 File name"<< std::endl;
    std::cin>>outputFileName;
    NDAVis::Converter converter = NDAVis::Converter(inputFileName, outputFileName);
    converter.convert();  */
    float color[] ={1,2,3};
    float opacity[] ={1,2};
    NDAVis::Controller contollerObj = Controller();
    contollerObj.setFile("lesgo2.hdf5");
    contollerObj.startServerRender(0, 0, 0, 0, 0, 0, color,3,opacity,2);
    //contollerObj.setNewCordinates(5*7*5,1,1,1,1,1,1,1); 

/*     int totalDim = 640*640*640;
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
    visul.render(640,640,640,2,2,2,0,0,0);  */

/*  int totalDim = 10 * 10 * 10;
    float *arr = new float[10 * 10 * 10];
    float *ptr = arr;
    for (int i = 0; i < totalDim; i++)
    {
        *ptr = 1;
        
        ptr++;
    }

    H5::DataSet dataset;
    H5::H5File outputFile;
    H5::Group group;
    outputFile = H5::H5File("aweaweaweasdasd.hdf5", H5F_ACC_TRUNC);

    H5::FloatType floatType(H5::PredType::NATIVE_FLOAT);
    floatType.setOrder(H5T_ORDER_LE);
    group = outputFile.createGroup("0");
    std::vector<hsize_t> bufferDims = {10, 10, 10};
    std::string nameName = "lol";
    //createHdf5Dataset(dataset, group, mipMapName.str(), floatType, datasetDims, chunkDims)

    group = group.createGroup(nameName);
    auto dataSpace = H5::DataSpace(3, bufferDims.data());
    H5::DSetCreatPropList propList;
    propList.setChunk(3, bufferDims.data());
    dataset = group.createDataSet(nameName, floatType, dataSpace, propList);

    std::vector<hsize_t> count = {10, 10, 10};
    std::vector<hsize_t> start = {0, 0, 0};
    H5::DataSpace memSpace(3, bufferDims.data());
    auto fileSpace = dataset.getSpace();
    if (!count.empty() && !start.empty())
    {
        fileSpace.selectHyperslab(H5S_SELECT_SET, count.data(), start.data());
    }

    dataset.write(arr, H5::PredType::NATIVE_FLOAT, memSpace, fileSpace); */

    return 0;
}
