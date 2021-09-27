#ifndef FILE_MANAGER_H_
#define FILE_MANAGER_H_

#include <string>
#include <vector>

namespace NDAVis
{
    class FileManager
    {
    public:
        std::string _filename;
        
        void getFileNames(std::vector<std::string> *fileNames);
        int getNumberOfFiles();
    };
}

#endif //FILE_MANAGER_H_