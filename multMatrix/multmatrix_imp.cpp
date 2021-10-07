#include "multmatrix_imp.h"

multmatrix_imp::multmatrix_imp(int clientID){

	multMatrix = multmatrix();
	//inicializar estados, extra...
	salir=false;
	this->clientID=clientID;

}

multmatrix_imp::~multmatrix_imp(){
	delete multmatrix;
	closeConnection(clientID);
}

void multmatrix_imp::exec(){

}