#include "filemanager_stub.h"

FileManager_stub::FileManager_stub(){
	char* ip=NULL;
	ip=new char[strlen(IP_SERVER)+1];
	memcpy(ip,IP_SERVER,strlen(IP_SERVER)+1);

	std::cout<<"INICIANDO CLIENTE\n";

	serverID=initClient(ip,PORT_SERVER);
	if(serverID==-1)
	{
		std::cout<<"CACA";
	}
	
	delete ip;
}

vector<string*>* FileManager_stub::listFiles(){
	return NULL;
}

void FileManager_stub::readFile(char* fileName, char* &data, unsigned long int & dataLength){

}

void FileManager_stub::writeFile(char* fileName, char* data, unsigned long int dataLength){
	
}

void FileManager_stub::freeListedFiles(vector<string*>* fileList){

}