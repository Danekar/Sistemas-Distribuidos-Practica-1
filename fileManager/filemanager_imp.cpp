#include "filemanager_imp.h"

FileManager_imp::FileManager_imp(int clientID, string path){
    filemanagerImp = new FileManager(path);
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
            	
            	
            	   vector<string*>* flist=new vector<string*>();
            	
            	
            	   flist = filemanagerImp->listFiles();
  
  
            	   int tamano = flist->size();
            	   sendMSG(clientID,(void*)&tamano, sizeof(int));
            	
            	  for(unsigned int i=0;i<flist->size();++i){
            	 
       	  sendMSG(clientID,(void*)flist->at(i)->c_str(), strlen(flist->at(i)->c_str()));
   		 }
   		 
    	       
            	}break;
                case READ_FILES:
                {
                    char* buff=nullptr;
                    char* filename=nullptr;
                    char* data=nullptr;
                    unsigned long int dataLen2 =0;
               
                    recvMSG(clientID,(void**)&buff,&dataLen);
                 
               	
                    //memcpy(&filename, buff, dataLen);
                    //delete buff;
                 
          cout<<buff<<"\n";
                    filemanagerImp->readFile(buff,data,dataLen2);
                   
 
                    sendMSG(clientID,(void*)&data, sizeof(char)*sizeof(dataLen2));

                    sendMSG(clientID,(void*)&dataLen2,sizeof(unsigned long int));

            		cout<<data<<"\n";
                    delete filename;
                    delete data;
           
                
                }break;             
                case WRITE_FILES:
                {
                    char* buff=nullptr;
                    char* filename=nullptr;
                    char* data=nullptr;
                    unsigned long int dataLen2=0;
                    
                    recvMSG(clientID,(void**)&filename,&dataLen);
                   // memcpy(&filename, buff, dataLen);
                    //delete buff;
                    
                    recvMSG(clientID,(void**)&data,&dataLen);
                    //memcpy(&filename, buff, dataLen);
                    //delete buff;

                    recvMSG(clientID,(void**)&dataLen2,&dataLen);
                   // memcpy(&dataLen2, buff, dataLen);
                    delete buff;
              
                    filemanagerImp->writeFile(filename,data,dataLen2);
                
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
