//Daniel Khomyakov y Eduardo Sebastian de Erice

#ifndef FILEMANAGER_IMP_H
#define FILEMANAGER_IMP_H

#include "filemanager.h"

#define LIST_FILES    	 'L'
#define READ_FILES      'R'
#define WRITE_FILES     'W'
#define EXIT_FILES      'E'
#define FREE_LISTED_FILES 'I'

#define OP_EXIT 'E'
#define OP_OK 'O'

using namespace std;

class FileManager_imp
{
private:
    FileManager* filemanagerImp = nullptr;
    bool salir = false;
    int clientID = 0;
public:
    FileManager_imp(int clientID, string path);
    ~FileManager_imp();
    void exec();
};

#endif // FILEMANAGER_IMP_H
