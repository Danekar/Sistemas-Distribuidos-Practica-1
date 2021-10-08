#include "multmatrix_imp.h"

multMatrix_imp::multMatrix_imp(int clientID){

	matrixImp = new multMatrix();
	//inicializar estados, extra...
	salir=false;
	this->clientID=clientID;

}

multMatrix_imp::~multMatrix_imp(){
	delete matrixImp;	
	closeConnection(clientID);
}

void multMatrix_imp::exec(){
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
				case READ_MATRIX:
				{
					char* nombreFich = nullptr;
					matrix_t* matrizLeer = new matrix_t;
					//recibir nombre fichero
					recvMSG(clientID,(void**)&nombreFich,&dataLen);
					matrizLeer = matrixImp->readMatrix(nombreFich);
					//enviar matriz
					sendMSG(clientID,(void*)&matrizLeer->rows,sizeof(int));
					sendMSG(clientID,(void*)&matrizLeer->cols,sizeof(int));
					sendMSG(clientID,(void*)matrizLeer->data,sizeof(int)*matrizLeer->rows*matrizLeer->cols);
					delete matrizLeer;	
					
				}break;
				case MULT_MATRIX:
				{
					
					
				}break;
				
				case WRITE_MATRIX:
				{
					
				}break;
				case CREATE_I_MATRIX:
				{
					
				}break;
				case CREATE_R_MATRIX:
				{
					
				}break;
				case EXIT_MATRIX:
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