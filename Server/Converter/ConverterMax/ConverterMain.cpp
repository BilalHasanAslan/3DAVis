#include <iostream>
#include <string>
#include "Converter.h"

using namespace NDAVis;
int main()
{    
    
    std::string inputFileName;
    std::string outputFileName;
    std::cout<<"Input FITS File name"<< std::endl;
    std::cin>>inputFileName;
    std::cout<<"Output HDF5 File name"<< std::endl;
    std::cin>>outputFileName;
    NDAVis::Converter converter = NDAVis::Converter(inputFileName, outputFileName);
    converter.convert();
    return 0;
}