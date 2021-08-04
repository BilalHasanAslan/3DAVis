
#include <string>
#include "HDF5Reader.h"
#include <typeinfo>
#include <iostream>
#include <chrono>

using namespace NDAVis;

int main()
{
    auto t_start = std::chrono::high_resolution_clock::now();
    NDAVis::HDF5Reader reader = NDAVis::HDF5Reader("test.hdf5");
    double elapsed_time_ms = std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - t_start).count();
    std::cout << "Time Taken To Open HDF5 File :" + std::to_string(elapsed_time_ms) + " ms" << std::endl;

    t_start = std::chrono::high_resolution_clock::now();
    reader.openDataset("0/DATA");
    elapsed_time_ms = std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - t_start).count();
    std::cout << "Time Taken To Open Dataset :" + std::to_string(elapsed_time_ms) + " ms" << std::endl;

    t_start = std::chrono::high_resolution_clock::now();
    reader.setDimensions();
    elapsed_time_ms = std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - t_start).count();
    std::cout << "Time Taken To Set Dimensions :" + std::to_string(elapsed_time_ms) + " ms" << std::endl;

    t_start = std::chrono::high_resolution_clock::now();
    reader.readDataset(100,100,100,100,100,100);
    elapsed_time_ms = std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - t_start).count();
    std::cout << "Time Taken To Set Dimensions :" + std::to_string(elapsed_time_ms) + " ms" << std::endl;

    return 0;
}
