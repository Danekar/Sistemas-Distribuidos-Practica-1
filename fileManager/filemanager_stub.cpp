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
	char msg = READ_FILES;
	char* buff = nullptr;
	int dataLen = 0;

	//Envio del Mensaje de opciones
	sendMSG(serverID,(void*)&msg,sizeof(char));

	//Envio del nombre del fichero
	sendMSG(serverID,(void*)&fileName, sizeof(char)*strlen(fileName));

	//Recibir conetnido del fichero
	recvMSG(serverID,(void**)&buff,&dataLen);
	memcpy(&data, buff, dataLen);
	delete buff;
	//Recibir tamaño del fichero
	recvMSG(serverID,(void**)&buff,&dataLen);
	memcpy(&dataLength, buff, dataLen);
	delete buff;
	
}

void FileManager_stub::writeFile(char* fileName, char* data, unsigned long int dataLength){
	char msg = WRITE_FILES;
	char* buff = nullptr;

	//Envio del Mensaje de opciones
	sendMSG(serverID,(void*)&msg,sizeof(char));

	//Envio del nombre del fichero
	sendMSG(serverID,(void*)&fileName, sizeof(char)*strlen(fileName));
	//Envio de contenido del fichero
	sendMSG(serverID,(void*)&data, sizeof(char)*strlen(data));
	//Envio tamaño del fichero
	sendMSG(serverID,(void*)&dataLength,sizeof(long int)*sizeof(dataLength));

}

void FileManager_stub::freeListedFiles(vector<string*>* fileList){
	char msg = FREE_LISTED_FILES;
	char* buff = nullptr;
	int dataLen = 0;
	int numFiles = sizeof(fileList);

	//Envio del Mensaje de opciones
	sendMSG(serverID,(void*)&msg,sizeof(char));

	sendMSG(serverID,(void*)&fileList, sizeof(char)*sizeof(fileList));
}

FileManager_stub::~FileManager_stub(){
	char msg = OP_EXIT;
	//Envio del mensaje de opción
	sendMSG(serverID,(void*)&msg,sizeof(char));
	char* buff=nullptr;
	int dataLen=0;
	char state=0;
	
	//Recibir respuesta del servidor
	recvMSG(serverID,(void**)&buff,&dataLen);
	memcpy(&state,buff,sizeof(char));
	delete buff;
	
	if(state!=OP_OK){
		std::cout<<"ERROR cerrando conexion\n";
	}
}
