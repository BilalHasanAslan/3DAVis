
#include "LogKeeper.h"
#include "FileManager.h"
using namespace NDAVis;

int main()
{
    NDAVis::FileManager fileManager;
    char *fileNames [fileManager.getNumberOfFiles()];
    fileManager.getFileNames(fileNames);
    return 0;
}