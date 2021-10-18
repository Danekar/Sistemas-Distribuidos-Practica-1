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
