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
	//enviar 'R' y nombre del fichero
	char msg = READ_MATRIX;
	char* buff = nullptr;
	int dataLen = 0;
	matriz_t matrizLeida=NULL;
	//envio opcion
	sendMSG(serverID,(void*)&msg,sizeof(char));

	//Enviar nombre del archivo
	sendMSG(serverID, (void*)fileName, strlen(fileName)+1);
	//recibir matriz
	//recibe rows
	revMSG(serverID,(void**)&buff, sizeof(int));
	mempcy(matrizLeida->rows,buff,sizeof(int));
	delete buff;
	//recibe cols
	revMSG(serverID,(void**)&buff, sizeof(int));
	mempcy(matrizLeida->cols,buff,sizeof(int));
	delete buff;
	//recibe data
	revMSG(serverID,(void*)&buff, sizeof(int)*matreizLeida->rows*matrizLeida->cols);
	mempcy(matrizLeida->data,buff,sizeof(int)*matreizLeida->rows*matrizLeida->cols);
	delete buff;

	return matrizLeida;

}
matrix_t multMatrix_stub::multMatrices(matrix_t* m1, matrix_t *m2){

}
void multMatrix_stub::writeMatrix(matrix_t* m, const char *fileName){

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
matrix_t multMatrix_stub::createIdentity(int rows, int cols){

}
matrix_t multMatrix_stub::createRandMatrix(int rows, int cols){
	
}