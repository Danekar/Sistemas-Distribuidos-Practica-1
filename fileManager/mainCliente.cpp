#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "filemanager_stub.h"

using namespace std;

int main (int argc, char** argv){


	cout<<"Estoy en el main\n";
    FileManager_stub *fm=new FileManager_stub();
    cout<<"He creado el file manager\n";
    vector<string*>* vfiles=fm->listFiles();
    cout<<"Lista de ficheros en el directorio de prueba:\n";
    for(unsigned int i=0;i<vfiles->size();++i)
    {
        cout<<"Fichero: "<<vfiles->at(i)->c_str()<<endl;
    }
    cout<<"Leyendo el primer fichero del directorio de prueba:\n";

    char* data=nullptr;
    //char cosa[]="jorge";
    //char* dataEscribir=cosa;
    unsigned long int fileLen=0;
    fm->readFile(&(*(vfiles->at(0)))[0],data,fileLen);
    cout<<"Escribiendo el primer fichero del directorio de prueba:\n";
    cout<<"Esto es el fileLen en el main: "<<fileLen<<"\n";
    fm->writeFile(&(*(vfiles->at(0)))[0],data,fileLen);
    cout<<"Liberando lista de ficheros:\n";
    fm->freeListedFiles(vfiles);
    cout<<"Liberando datos de fichero leído:\n";
   fm->~FileManager_stub();
   delete[] data;
cout<<"Confirmadisimo\n";

   
	return 0;
}
