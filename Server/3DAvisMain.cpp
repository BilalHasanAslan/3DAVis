#include "LogKeeper.h"
#include "FileManager.h"
#include "Server.h"
#include <string>
#include <vector>
#include <iostream>
//#include "vtkAutoInit.h"

using namespace NDAVis;

//VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2);
int main()
{
   

    //FileManager
    NDAVis::FileManager fileManager;
    //Number Of the Files that are preprocessed
    int numberOfFiles = fileManager.getNumberOfFiles();
    //Name Of the Files that are preprocessed
    std::vector<std::string> fileNames;
    fileManager.getFileNames(&fileNames);

    //Testing Will be deleted Later

    //Testing for Number Of Files
    std::cout << "Number Of Files: " << std::endl;
    std::cout << numberOfFiles << std::endl;

    //Testing for File Names
    std::cout << "File Names: " << std::endl;
    for (auto it = fileNames.begin(); it != fileNames.end(); it++)
    {
        std::cout << *it << std::endl;
    }

    NDAVis::Server server;
    server.runServer();
    

    return 0;


}
