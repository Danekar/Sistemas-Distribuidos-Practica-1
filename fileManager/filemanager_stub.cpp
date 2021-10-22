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
	char* buff = nullptr;filemanager_stub.cpp:87:
	int dataLen = 0;
	int tamanoDeVector=0;
	
	
	
	
	
	vector<string*>* flist=new vector<string*>();
	
	sendMSG(serverID,(void*)&msg,sizeof(char));
	
	//Pillamos el tamaño del vector
	recvMSG(serverID,(void**)&buff,&dataLen);
	memcpy(&tamanoDeVector,buff,dataLen);
	delete buff;
	
	
	//Vemos cuantas iteraciones seran mirando pues el tamañao que conseguimos anteriormente y por cada iteracion le vamos metiendo un nuevo 		string al vector de strings
	for(unsigned int i=0;i<tamanoDeVector;++i){
	//recibimos el nombre del fichero
   	recvMSG(serverID,(void**)&buff,&dataLen);
   	//creamos un nuevo STRING PUNTERO(no se si esto es etico o no)
   	string *filename = new string;
   	//le metemos lo que tenia el buffer que es un CHAR PUNTERO y el filename un STRING PUNTERO y los unimos con append
	filename->append(buff);
	//por ultimo metemos el vector de STRING PUNTERO en el VECTOR DE STRING DE PUNTERO.
   	flist->push_back(filename);   	   	
	
	//limpimos el buffer
	delete buff;
   	}

	
	return flist;
}

void FileManager_stub::readFile(char* fileName, char* &data, unsigned long int & dataLength){
	char msg = READ_FILES;
	char* buff = nullptr;
	int dataLen = 0;

	//Envio del Mensaje de opciones
	sendMSG(serverID,(void*)&msg,sizeof(char));

	//Envio del nombre del fichero
	sendMSG(serverID,(void*)fileName, strlen(fileName));

	//Recibir conetnido del fichero
	recvMSG(serverID,(void**)&data,&dataLen);

	//memcpy(data, buff, dataLen);
	//cout<<data<<"\n";
	//delete buff;

	//Recibir tamaño del fichero
	recvMSG(serverID,(void**)&dataLength,&dataLen);

	//memcpy(&dataLength, buff, dataLen);
//	cout<<dataLength<<"\n";
//	delete buff;

	
}

void FileManager_stub::writeFile(char* fileName, char* data, unsigned long int dataLength){
	char msg = WRITE_FILES;
	


	//Envio del Mensaje de opciones
	sendMSG(serverID,(void*)&msg,sizeof(char));
	
	//Envio del nombre del fichero
	sendMSG(serverID,(void*)fileName, strlen(fileName)+1);
	//Envio de contenido del fichero
	
	sendMSG(serverID,(void*)data,strlen(data)+1);
	//Envio tamaño del fichero
	
	sendMSG(serverID,(void*)&dataLength,sizeof(unsigned long int));
	
}

void FileManager_stub::freeListedFiles(vector<string*>* fileList){
	char msg = FREE_LISTED_FILES;
	char* buff = nullptr;
	int dataLen = 0;
	 

	//Envio del Mensaje de opciones
	sendMSG(serverID,(void*)&msg,sizeof(char));
	
	 int tamano = fileList->size();
	 cout<<tamano<<"\n";
         sendMSG(serverID,(void*)&tamano, sizeof(int));

	for(unsigned int i=0;i<fileList->size();++i){
          cout<<"4.2\n";
      	sendMSG(serverID,(void*)fileList->at(i)->c_str(), strlen(fileList->at(i)->c_str()));
   	}
}

FileManager_stub::~FileManager_stub(){
	char msg = OP_EXIT;
	cout<<"5.1\n";
	//Envio del mensaje de opción
	sendMSG(serverID,(void*)&msg,sizeof(char));
	char* buff=nullptr;
	int dataLen=0;
	char state=0;
	cout<<"5.2\n";
	//Recibir respuesta del servidor
	recvMSG(serverID,(void**)&buff,&dataLen);
	memcpy(&state,buff,sizeof(char));
	delete buff;
	cout<<"5.3\n";
	if(state!=OP_OK){
		std::cout<<"ERROR cerrando conexion\n";
	}
}
