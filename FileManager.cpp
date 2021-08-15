#include "FileManager.h"
#include <fstream>
#include <string>

namespace NDAVis
{
    int getNumberOfFiles()
    {
        std::ifstream infile("\HDF5Data\FileList.txt");
        std::string line;
        int c = 0;
        while (std::getline(infile, line))
        {

            c++;
        }
        infile.close();
        return c;
    }

    void getFileNames(char** arr)
    {   
        int c = 0;
        char* temp = arr;
        std::ifstream infile("\HDF5Data\FileList.txt");
        std::string line;
        while (std::getline(infile, line))
        {
            arr[c] = line;
            c++;
        }
        infile.close();
    }
}
