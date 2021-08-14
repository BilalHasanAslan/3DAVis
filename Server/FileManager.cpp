#include "FileManager.h"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

namespace NDAVis
{   
    //Returns Number Of Files that are preprocessed
    int FileManager::getNumberOfFiles()
    {
        std::ifstream infile("../HDF5Data/FileList.txt");
        std::string line;
        int c = 0;
        while (std::getline(infile, line))
        {
            c++;
        }
        infile.close();
        return c;
    }
    //Returns File Names that are preprocessed
    void FileManager::getFileNames(std::vector<std::string> *fileNames)
    {
        std::ifstream infile("../HDF5Data/FileList.txt");
        std::string line;
        while (std::getline(infile, line))
        {
            fileNames -> push_back(line);
        }
        infile.close();
    }
}
