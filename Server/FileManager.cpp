#include "FileManager.h"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

namespace NDAVis
{   
    //Returns Number Of Files that are preprocessed
    /*
    The FileManager class is a class that manages the HDF5 files. It has a function that returns the number of files in the file list.
    
    Args:
      None
    Returns:
      The number of files in the file list.
    */
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
    /*
    Reads in the file names from the file "FileList.txt" and stores them in a vector.
    
    Args:
      fileNames: A vector of strings that contains the names of the files to be read.
      infile: The file that contains the list of files to be read.
    Returns:
      A vector of strings.
    */
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
