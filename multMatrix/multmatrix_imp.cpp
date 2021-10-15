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
					//Creacion de matriz para guardar la leida
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
					char* buff = nullptr;
					matrix_t* matrizResultado = new matrix_t;
					//Creacon de matrices para guardar las matrices recibidas
					matrix_t* m1 = new matrix_t;
					matrix_t* m2 = new matrix_t;

					std::cout<<"Servidor recibo row de m1 \n";
					//recibe rows m1
					recvMSG(clientID,(void**)&buff, &dataLen);
					memcpy(&m1->rows,buff,sizeof(int));
					delete buff;
					
					std::cout<<"Servidor recibo col de m1 \n";
					//recibe cols m1
					recvMSG(clientID,(void**)&buff, &dataLen);
					memcpy(&m1->cols,buff,sizeof(int));
					delete buff;
					
					std::cout<<"Servidor recibo data de m1 \n";
					//recibe data m1
					recvMSG(clientID,(void**)&buff, &dataLen);
					memcpy(&m1->data,buff,sizeof(int));
					delete buff;


					std::cout<<"Servidor recibo row de m2 \n";
					//recibe rows m2
					recvMSG(clientID,(void**)&buff, &dataLen);
					memcpy(&m2->rows,buff,sizeof(int));
					delete buff;
					
					std::cout<<"Servidor recibo col de m2 \n";
					//recibe cols m2
					recvMSG(clientID,(void**)&buff, &dataLen);
					memcpy(&m2->cols,buff,sizeof(int));
					delete buff;
					
					std::cout<<"Servidor recibo data de m2 \n";
					//recibe data m2
					recvMSG(clientID,(void**)&buff, &dataLen);
					memcpy(&m2->data,buff,sizeof(int));
					delete buff;

					
					std::cout<<"Estoy enseñando cosas \n";
					std::cout<<"Fila de m1: "<<m1->rows<<" con columnas: "<<m1->cols<<" Con le primer dato: "<<m1->data[0]<<std::endl;
					for(int i = 0;i<m1->rows*m1->cols;i++){
						std::cout<<m1->data[i]<<" ";	
					}
					std::cout<<"\n";
					std::cout<<"Servidor multiplicando...\n";
					//guarda la matriz resultado en una nueva matriz
					matrizResultado = matrixImp->multMatrices(m1, m2);
					//Borramos memoria que no utilicemos más
					std::cout<<"Servidor Eliminando\n";
					delete m1;
					delete m2;
					
					
					//envia al cliente la matriz por partes
					std::cout<<"Servidor enviando row\n";
					sendMSG(clientID,(void*)&matrizResultado->rows,sizeof(int));
					
					std::cout<<"Servidor enviando col\n";
					sendMSG(clientID,(void*)&matrizResultado->cols,sizeof(int));
					
					std::cout<<"Servidor enviando data\n";
					sendMSG(clientID,(void*)matrizResultado->data,sizeof(int)*matrizResultado->rows*matrizResultado->cols);
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
					memcpy(&matrizEscribir->data,buff,sizeof(int));
					delete buff;

					matrixImp->writeMatrix(matrizEscribir, fileName);
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
