//Daniel Khomyakov y Eduardo Sebastian de Erice

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "filemanager_stub.h"

using namespace std;

int main (int argc, char** argv){

	bool bucle=true;
	bool encontrado=false;
	int opcion=0;
	unsigned long int fileLen=0;
	string op;
	char yN;
	char* archivoSub=new char;
	char* archivoDes=new char;
	char* data=nullptr;
	
    FileManager_stub *fm=new FileManager_stub();
    FileManager *client = new FileManager("./");
   
    vector<string*>* vfiles=fm->listFiles();
    vector<string*>* cfiles=client->listFiles();
    
   
    
   
   
    while(bucle){
    	opcion=0;
    	 cout<<"Elige una opcion: \n"<<"- Ls\n"<<"- Upload\n"<<"- Download\n"<<"- Exit\n";
    	 
   		cin>>op;
   		if(op=="Ls"){
   			opcion=1;
   		}else if(op=="Upload"){
   			opcion=2;
   		}else if(op=="Download"){
   			opcion=3;
   		}else if(op=="Exit"){
   			opcion=4;
   		}else{
   			opcion=5;
   		}
   
  	
    	
    	switch (opcion){
    	
    	
    	case 1:{
    	cout<<"Lista de ficheros en el directorio de prueba:\n";
   	 for(unsigned int i=0;i<vfiles->size();++i)
    	{
        cout<<"Fichero: "<<vfiles->at(i)->c_str()<<endl;
    	}
    	
    	
    	}break;
    	
    	case 2:{
    	while(encontrado==false){
    	cout<<"Escriba el archivo quiere subir: ";
    	cin>>archivoSub;
    	for(unsigned int i=0;i<cfiles->size();++i){
        	if(strcmp(archivoSub,cfiles->at(i)->c_str())==0){
        		encontrado=true;
        		cout<<"Archivo subiendose...\n";
       		client->readFile(archivoSub,data,fileLen);
       		fm->writeFile(archivoSub,data,fileLen);
       		cout<<"Archivo subido\n";
       	 }
        
    	}
    	
    	if(encontrado==false){
    		cout<<"\nNo se ha encontrado el fichero que quiere descargar, ¿ quiere seguir buscando ? [presione N para no y cualquier otro para seguir]\n";
    		cin>>yN;
    		if(yN=='N'){
    		encontrado=true;
    	}
    	}
    	
    	
    	
    	}
    	}break;
    	
    	case 3:{
    	while(encontrado==false){
    	cout<<"Escriba el archivo que quiere descargar: ";
    	cin>>archivoDes;
    	
    	 for(unsigned int i=0;i<vfiles->size();++i){
        	if(strcmp(archivoDes,vfiles->at(i)->c_str())==0){
        		encontrado=true;
        		cout<<"Archivo descargandose...\n";
       		fm->readFile(archivoDes,data,fileLen);
       		client->writeFile(archivoDes,data,fileLen);
       		cout<<"Archivo descargado\n";
       	 }
        
    	}
    	
    	if(encontrado==false){
    		cout<<"\nNo se ha encontrado el fichero que quiere descargar, ¿ quiere seguir buscando ? [presione N para no y cualquier otro para seguir]\n";
    		cin>>yN;
    		if(yN=='N'){
    		encontrado=true;
    	}
    	}
    	
    	
    	
    	}
    	
    	
    	}break;
    	
    	case 4:{
    	cout<<"Cerrando el processo\n";
    	bucle=false;
 
    	}break;  
    	  	
    	default:{
    	cout<<"No ha elejido ninguna de las opciones anteriores, tenga en cuenta las mayusculas y minusculas\n";
    	}break;
    	
    	}
    	
    	vfiles=fm->listFiles();
    	cfiles=client->listFiles();
    	encontrado=false;
    }
    
    delete archivoSub;
    delete archivoDes;
    delete data;
    delete fm;
    delete client;
    delete vfiles;
    delete cfiles;

   
	return 0;
}
