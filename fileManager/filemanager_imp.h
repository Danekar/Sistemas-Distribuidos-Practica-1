#ifndef FILEMANAGER_IMP_H
#define FILEMANAGER_IMP_H

#include "filemanager.h"

#define EXIT_FILEM 'E'
#define OP_OK 'O'

using namespace std;

class FileManager_imp
{
private:
    FileManager* filemanagerImp = nullptr;
    bool salir = false;
    int clientID = 0;
public:
    FileManager_imp(int clientID);
    ~FileManager_imp();
    void exec();
};

#endif // FILEMANAGER_IMP_H
