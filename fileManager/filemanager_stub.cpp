#include "filemanager_stub.h"

using namespace std;

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
	char msg = LIST_FILES;
	char* buff = nullptr;
	int dataLen = 0;
	
	cout<<"1.1\n";
	vector<string*>* flist=new vector<string*>();
	cout<<"1.2\n";
	sendMSG(serverID,(void*)&msg,sizeof(char));
	
	cout<<"1.3\n";
	recvMSG(serverID,(void**)&buff,&dataLen);
	cout<<"1.3.1\n";
	memcpy(&flist,buff,dataLen);
	delete buff;
	cout<<"1.4\n";
	
	return flist;
}

void FileManager_stub::readFile(char* fileName, char* &data, unsigned long int & dataLength){

}

void FileManager_stub::writeFile(char* fileName, char* data, unsigned long int dataLength){
	
}

void FileManager_stub::freeListedFiles(vector<string*>* fileList){

}
