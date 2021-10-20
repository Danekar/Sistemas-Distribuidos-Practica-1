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
                
                    recvMSG(clientID,(void**)&data,&dataLen);
                 
                    recvMSG(clientID,(void**)&dataLen2,&dataLen);
                    cout<<dataLen2<<"\n";
              	
                filemanagerImp->writeFile(filename,data,strlen(data));
                
                
               
                }break;
                
                case FREE_LISTED_FILES:
                {
                	
                char* buff=nullptr;
              
                int tamanoDeVector=0;
                    vector<string*>* flist=new vector<string*>();
                    
                   
                    
                    	recvMSG(clientID,(void**)&buff,&dataLen);
			memcpy(&tamanoDeVector,buff,dataLen);
			delete buff;
			cout<<"Tamaño del vector: "<<tamanoDeVector<<"\n";
                    
                    for(unsigned int i=0;i<tamanoDeVector;++i){
			//recibimos el nombre del fichero
			cout<<"4.1\n";
   			recvMSG(clientID,(void**)&buff,&dataLen);
   			//creamos un nuevo STRING PUNTERO(no se si esto es etico o no)
   			cout<<"4.2\n";
   			string *filename = new string;
   			//le metemos lo que tenia el buffer que es un CHAR PUNTERO y el filename un STRING PUNTERO y los unimos con append
   			cout<<"4.3\n";
			filename->append(buff);
			//por ultimo metemos el vector de STRING PUNTERO en el VECTOR DE STRING DE PUNTERO.
			cout<<"4.4\n";
   			flist->push_back(filename);   	   	
			cout<<"4.5\n";
			//limpimos el buffer
			delete buff;
   			}
                    cout<<"4.6\n";
     
     
 
                    filemanagerImp->freeListedFiles(flist);
                    cout<<"4.7\n";
                    
                
                }break;      	  
                case OP_EXIT:
                {
                cout<<"5.1\n";
                    salir=true;
                    cout<<"5.2\n";
                    char opOK=OP_OK;
                    cout<<"5.3\n";
                    sendMSG(clientID,(void*)&opOK,sizeof(char));
                    cout<<"5.4\n";
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
