#ifndef FILE_MANAGER_H_
#define FILE_MANAGER_H_

#include <string>

namespace NDAVis{
class FileManager{
public:
std::string _filename;
void getFileNames(char** arr);
int getNumberOfFiles();


};
}


#endif //FILE_MANAGER_H_