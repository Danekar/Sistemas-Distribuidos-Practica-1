//Daniel Khomyakov y Eduardo Sebastian de Erice

#include "multmatrix_stub.h"

multMatrix_stub::multMatrix_stub(){
	char* ip=NULL;
	ip=new char[strlen(IP_SERVER)+1];
	memcpy(ip,IP_SERVER,strlen(IP_SERVER)+1);

	std::cout<<"INICIANDO CLIENTE\n";

	serverID=initClient(ip,PORT_SERVER);
	if(serverID==-1)
	{
		std::cout<<"CACA";
	}
	
	delete ip;
}
matrix_t* multMatrix_stub::readMatrix(const char* fileName){
	char msg = READ_MATRIX;
	char* buff = nullptr;
	int dataLen = 0;
	matrix_t* matrizLeida=new matrix_t;

	//envio opcion
	sendMSG(serverID,(void*)&msg,sizeof(char));
	
	
	//Enviar nombre del archivo
	sendMSG(serverID, (void*)fileName, strlen(fileName)+1);

	//Recibe filas y columnas
	recvMSG(serverID,(void**)&buff, &dataLen);
	memcpy(&matrizLeida->rows,buff,sizeof(int));
	delete buff;
	recvMSG(serverID,(void**)&buff, &dataLen);
	memcpy(&matrizLeida->cols,buff,sizeof(int));
	delete buff;

	//Recibe el contenido de la Matriz
	recvMSG(serverID,(void**)&buff, &dataLen);
	matrizLeida->data = (int*)buff;
	
	return matrizLeida;

}
matrix_t *multMatrix_stub::multMatrices(matrix_t* m1, matrix_t *m2){
	char msg = MULT_MATRIX;
	char* buff = nullptr;
	int dataLen = 0;
	matrix_t* matrizResultado = new matrix_t;
	
	//Enviamos la opcion
	
	sendMSG(serverID,(void*)&msg,sizeof(char));

	
	//Enviamos las columnas, filas y datos de la matriz m1 respectivamente.
	sendMSG(serverID,(void*)&m1->rows,sizeof(int));
	sendMSG(serverID,(void*)&m1->cols,sizeof(int));
	sendMSG(serverID,(void*)&m1->data,sizeof(int)*m1->rows*m1->cols);
	
	
	//Enviamos las columnas, filas y datos de la matriz m2 respectivamente.
	sendMSG(serverID,(void*)&m2->rows,sizeof(int));
	sendMSG(serverID,(void*)&m2->cols,sizeof(int));
	sendMSG(serverID,(void*)&m2->data,sizeof(int)*m2->rows*m2->cols);
	
	//recibe rows
	
	recvMSG(serverID,(void**)&buff, &dataLen);
	
	memcpy(&matrizResultado->rows,buff,sizeof(int));
	
	
	delete buff;
	

	
	
	//recibe cols
	recvMSG(serverID,(void**)&buff, &dataLen);
	memcpy(&matrizResultado->cols,buff,sizeof(int));
	delete buff;
	
	
	//recibe data
	recvMSG(serverID,(void**)&buff, &dataLen);
	//memcpy(&matrizResultado->data,buff,sizeof(int));
	matrizResultado->data = (int*)buff;
	delete buff;
	
	
	return matrizResultado;
}
void multMatrix_stub::writeMatrix(matrix_t* m, const char *fileName){
	char msg = WRITE_MATRIX;
	char* buff = nullptr;
	int dataLen = 0;
	
	//Enviamos la opcion
	sendMSG(serverID,(void*)&msg,sizeof(char));
	//Enviar nombre del archivo
	sendMSG(serverID, (void*)fileName, strlen(fileName)+1);
	
	//Enviamso las filas, columans y datos de la matriz
	sendMSG(serverID,(void*)&m->rows,sizeof(int));
	sendMSG(serverID,(void*)&m->cols,sizeof(int));
	sendMSG(serverID,(void*)m->data,sizeof(int)*m->rows*m->cols);

}
multMatrix_stub::~multMatrix_stub(){
	char msg = EXIT_MATRIX;
	sendMSG(serverID,(void*)&msg,sizeof(char));

	//recibir resultado
	char* buff=nullptr;
	int dataLen=0;
	char state=0;
	
	recvMSG(serverID,(void**)&buff,&dataLen);
	memcpy(&state,buff,sizeof(char));
	delete buff;
	
	if(state!=OP_OK){
		std::cout<<"ERROR cerrando conexion\n";
	}
}
matrix_t* multMatrix_stub::createIdentity(int rows, int cols){
	char msg = CREATE_I_MATRIX;
	char* buff = nullptr;
	int dataLen = 0;
	matrix_t* matrizIdentidad = new matrix_t;
	
	//Enviamos la opcion
	sendMSG(serverID,(void*)&msg,sizeof(char));
		
	//Enviamso las filas y columnas respectivamente
	sendMSG(serverID,(void**)&rows,sizeof(int));
	sendMSG(serverID,(void**)&cols,sizeof(int));
	
	//Recibe filas y columnas
	recvMSG(serverID,(void**)&buff, &dataLen);
	memcpy(&matrizIdentidad->rows,buff,sizeof(int));
	delete buff;
	recvMSG(serverID,(void**)&buff, &dataLen);
	memcpy(&matrizIdentidad->cols,buff,sizeof(int));
	delete buff;	
	
	//recibe data m1
	recvMSG(serverID,(void**)&buff, &dataLen);
	matrizIdentidad->data = (int*)buff;
	
	return matrizIdentidad;
}
matrix_t* multMatrix_stub::createRandMatrix(int rows, int cols){
	char msg = CREATE_R_MATRIX;
	char* buff = nullptr;
	int dataLen = 0;
	matrix_t* matrizRandom = new matrix_t;
	
	//Enviamos la opcion
	sendMSG(serverID,(void*)&msg,sizeof(char));
		
	//Enviamso las filas y columnas respectivamente
	sendMSG(serverID,(void**)&rows,sizeof(int));
	sendMSG(serverID,(void**)&cols,sizeof(int));
	
	//Recibe filas y columnas
	recvMSG(serverID,(void**)&buff, &dataLen);
	memcpy(&matrizRandom->rows,buff,sizeof(int));
	delete buff;
	recvMSG(serverID,(void**)&buff, &dataLen);
	memcpy(&matrizRandom->cols,buff,sizeof(int));
	delete buff;

	//Recibe el contenido de la matriz
	recvMSG(serverID,(void**)&buff, &dataLen);
	matrizRandom->data = (int*)buff;	
	
	return matrizRandom;
}
