//Daniel Khomyakov y Eduardo Sebastian de Erice

#include "multmatrix_imp.h"

multMatrix_imp::multMatrix_imp(int clientID){

	multMatrix* matrixImp = new multMatrix();
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
					char* buff = nullptr;
					
					//Creacion de matriz para guardar la leida
					matrix_t* matrizLeer = new matrix_t;
					
					//recibir nombre fichero
					recvMSG(clientID,(void**)&buff,&dataLen);
				
					matrizLeer = matrixImp->readMatrix(buff);
					delete buff;

					//enviar matriz
					sendMSG(clientID,(void*)&matrizLeer->rows,sizeof(int));
					sendMSG(clientID,(void*)&matrizLeer->cols,sizeof(int));
					sendMSG(clientID,(void*)matrizLeer->data,sizeof(int)*matrizLeer->rows*matrizLeer->cols);
					delete matrizLeer;	
					
				}break;
				case MULT_MATRIX:
				{
					char* m1buff = nullptr;
					char* m2buff = nullptr;
					matrix_t* matrizResultado = new matrix_t;
					//Creacon de matrices para guardar las matrices recibidas
					matrix_t* m1 = new matrix_t;
					matrix_t* m2 = new matrix_t;

					//recibe rows m1
					recvMSG(clientID,(void**)&m1buff, &dataLen);
					memcpy(&m1->rows,m1buff,sizeof(int));
					delete m1buff;
					
					//recibe cols m1
					recvMSG(clientID,(void**)&m1buff, &dataLen);
					memcpy(&m1->cols,m1buff,sizeof(int));
					delete m1buff;
					
					//recibe data m1
					recvMSG(clientID,(void**)&m1buff, &dataLen);
					m1->data = (int*)m1buff;
					
					//recibe rows m2
					recvMSG(clientID,(void**)&m2buff, &dataLen);
					memcpy(&m2->rows,m2buff,sizeof(int));
					delete m2buff;
					
					//recibe cols m2
					recvMSG(clientID,(void**)&m2buff, &dataLen);
					memcpy(&m2->cols,m2buff,sizeof(int));
					delete m2buff;
					
					//recibe data m2
					recvMSG(clientID,(void**)&m2buff, &dataLen);
					m2->data = (int*)m2buff;

					//guarda la matriz resultado en una nueva matriz
					matrizResultado = matrixImp->multMatrices(m1, m2);
					delete m1buff;
					delete m2buff;
					delete m1;
					delete m2;

				
					//envia al cliente la matriz por partes
					sendMSG(clientID,(void*)&matrizResultado->rows,sizeof(int));
					sendMSG(clientID,(void*)&matrizResultado->cols,sizeof(int));
					sendMSG(clientID,(void*)&matrizResultado->data,sizeof(int)*matrizResultado->rows*matrizResultado->cols);
					delete matrizResultado;
					
				}break;
				
				case WRITE_MATRIX:
				{
					matrix_t* matrizEscribir = new matrix_t;
					char* fileName = nullptr;
					char* buff = nullptr;

					//recibir nombre del fichero
					recvMSG(clientID,(void**)&fileName, &dataLen);//

					//recibe rows matriz escribir
					recvMSG(clientID,(void**)&buff, &dataLen);
					memcpy(&matrizEscribir->rows,buff,sizeof(int));
					delete buff;
					//recibe cols matrizEscribir
					recvMSG(clientID,(void**)&buff, &dataLen);
					memcpy(&matrizEscribir->cols,buff,sizeof(int));
					delete buff;
					//recibe data matrizEscribir
					recvMSG(clientID,(void**)&buff, &dataLen);
					matrizEscribir->data = (int*)buff;
					

					matrixImp->writeMatrix(matrizEscribir, fileName);
					delete buff;
					delete matrizEscribir;
					delete fileName;
				}break;
				case CREATE_I_MATRIX:
				{
					int rows = 0;
					int cols = 0;
					char* buff = nullptr;
					matrix_t* matrizIdentidad = new matrix_t;

					//recibe los parametros
					recvMSG(clientID,(void**)&buff, &dataLen);
					memcpy(&rows,buff,sizeof(int));
					delete buff;
					
					recvMSG(clientID,(void**)&buff, &dataLen);
					memcpy(&cols,buff,sizeof(int));
					delete buff;

					
					matrizIdentidad = matrixImp->createIdentity(rows,cols);

					//devolver al cliente la matriz
					sendMSG(clientID,(void*)&matrizIdentidad->rows,sizeof(int));
					sendMSG(clientID,(void*)&matrizIdentidad->cols,sizeof(int));
					sendMSG(clientID,(void*)matrizIdentidad->data,sizeof(int)*matrizIdentidad->rows*matrizIdentidad->cols);
					delete matrizIdentidad;	
				}break;
				case CREATE_R_MATRIX:
				{
					
					int rows = 0;
					int cols = 0;
					char* buff = nullptr;					
					matrix_t* matrizRandom = new matrix_t;

					//recibe los parametros					
					recvMSG(clientID,(void**)&buff, &dataLen);					
					memcpy(&rows,buff,sizeof(int));
					delete buff;
					
					recvMSG(clientID,(void**)&buff, &dataLen);					
					memcpy(&cols,buff,sizeof(int));				
					delete buff;

					matrizRandom = matrixImp->createRandMatrix(rows, cols);
					
					//devolver al cliente la matriz					
					sendMSG(clientID,(void*)&matrizRandom->rows,sizeof(int));
					sendMSG(clientID,(void*)&matrizRandom->cols,sizeof(int));
					sendMSG(clientID,(void*)matrizRandom->data,sizeof(int)*matrizRandom->rows*matrizRandom->cols);
					delete matrizRandom;
				}break;
				case EXIT_MATRIX:
				{
					salir=true;
					char opOK=OP_OK;
					std::cout<<"Cliente "<< clientID<<" se ha desconectado\n";
					sendMSG(clientID,(void*)&opOK,sizeof(char));
				}break;
				
				default:
					std::cout<<"Error, tipo operacion no valido\n";
				break;
				
			}
		}
		
	
	}
	
}
