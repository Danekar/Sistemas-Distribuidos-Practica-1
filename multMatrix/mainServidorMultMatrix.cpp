//Daniel Khomyakov y Eduardo Sebastian de Erice

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <thread>
#include "multmatrix_imp.h"

using namespace std;

void threadClient(int clientID){
	multMatrix_imp* multmatrixImp = new multMatrix_imp(clientID);
	multmatrixImp->exec();
	delete multmatrixImp;
}

int main (int argc, char** argv){
	int idSocket = 0;
	idSocket = initServer(3301);

	while(true)
	{
	
		if(checkNewConnections()){
		
			int clientID=getNewConnection();	
			thread* newThread=new thread(threadClient,clientID);
			newThread->detach();
		}
	}

	return 0;
}