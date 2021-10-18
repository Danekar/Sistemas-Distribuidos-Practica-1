#include "filemanager_imp.h"

FileManager_imp::FileManager_imp(int clientID){
    FileManager* filemanagerImp = new FileManager("dirprueba");
    salir = false;
    this->clientID = clientID;
}

FileManager_imp::~FileManager_imp(){
    delete filemanagerImp;
    closeConnection(clientID);
}

void FileManager_imp::exec(){
    while(!salir)
    {
        //ejecutar
        //recibir tipo de operacion
        char* msg=NULL;
        int dataLen=0;
        char tipo_op=-1;

        recvMSG(clientID,(void**)&msg,&dataLen);
        if(dataLen!=1)
        {   
            std::cout<<"Error, tipo operacion no valido\n";
        }else
        {
            tipo_op=msg[0];
            delete msg;
            
            switch(tipo_op)
            { 
            
            	case LIST_FILES:
            	{
            	cout<<"1.1\n";
            	vector<string*>* flist=new vector<string*>();
            	cout<<"1.2\n";
            	flist = filemanagerImp->listFiles();
            	cout<<"1.3\n";
            	sendMSG(clientID,(void*)&flist,sizeof(vector<string*>));
            	cout<<"1.4\n";
            	
            	
            	}break;
            	
            	
            	
            	case READ_FILES:
            	{
            	char* buff=nullptr;
            	char* filename=nullptr;
            	char* data=nullptr;
            	unsigned long int* dataLen2 =nullptr;
            	recvMSG(clientID,(void**)&buff,&dataLen);
		memcpy(&filename, buff, dataLen);
		delete buff;
		
		filemanagerImp->readFile(filename,data,*dataLen2);
		sendMSG(clientID,(void*)&data, sizeof(char)*sizeof(dataLen2));
		sendMSG(clientID,(void*)&dataLen2,sizeof(unsigned long int));
		
            	delete filename;
            	delete data;
            	delete dataLen2;
            	
            	}break;
            	
            	case WRITE_FILES:
            	{
            	char* buff=nullptr;
            	char* filename=nullptr;
            	char* data=nullptr;
            	unsigned long int* dataLen2=nullptr;
            	
            	recvMSG(clientID,(void**)&buff,&dataLen);
		memcpy(&filename, buff, dataLen);
		delete buff;
		
		recvMSG(clientID,(void**)&buff,&dataLen);
		memcpy(&filename, buff, dataLen);
		delete buff;
		
		recvMSG(clientID,(void**)&buff,&dataLen);
		memcpy(&dataLen2, buff, dataLen);
		delete buff;
            	
            	filemanagerImp->writeFile(filename,data,*dataLen2);
            	
            	}break;
            	
            	case FREE_LISTED_FILES:
            	{
            	
            	vector<string*>* flist=new vector<string*>();
            	
            	recvMSG(clientID,(void**)&flist,&dataLen);
            	
            	filemanagerImp->freeListedFiles(flist);
            	delete flist;
            	
            	}break;
            	
            	  
                case EXIT_FILES:
                {
                    salir=true;
                    char opOK=OP_OK;
                    sendMSG(clientID,(void*)&opOK,sizeof(char));
                }break;
                default:
                    std::cout<<"Error, tipo operacion no valido\n";
                break;
                
            }
        }
    //switch (tipo_op)
        //si es suma
    }
}
