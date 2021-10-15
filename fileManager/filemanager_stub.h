#ifndef FILEMANAGER_STUB_H
#define FILEMANAGER_STUB_H

#include "filemanager.h"

using namespace std;

#define IP_SERVER "127.0.0.1"
#define PORT_SERVER 3301

class FileManager_stub
{
private:
    int serverID;
public:
    FileManager_stub();
    vector<string*>* listFiles();
    void readFile(char* fileName, char* &data, unsigned long int & dataLength);
    void writeFile(char* fileName, char* data, unsigned long int dataLength);
    void freeListedFiles(vector<string*>* fileList);
};

#endif // FILEMANAGER_STUB_H
