#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "multmatrix_stub.h"

int main (int argc, char** argv){

	multMatrix_stub* mulMatrix = new multMatrix_stub();

	std::cout<<"1\n";
	matrix_t* m1= mulMatrix->createRandMatrix(5,5);
	std::cout<<"2\n";
  	matrix_t* m2= mulMatrix->createIdentity(5,5);
   	std::cout<<"3\n";
   	matrix_t* mres=mulMatrix->multMatrices(m1,m2);
   	std::cout<<"4\n";
   	mulMatrix->writeMatrix(mres,"resultado.txt");
    	std::cout<<"5\n";
    	matrix_t* m3=mulMatrix->readMatrix("resultado.txt");
    	std::cout<<"6\n";
    	matrix_t* mres2=mulMatrix->multMatrices(m1,m3);
    	std::cout<<"7\n";
    	mulMatrix->writeMatrix(mres2,"resultado2.txt");
	std::cout<<"He terminado todos los procesos\n";


    delete m1;
    delete m2;
    delete mres;
    delete m3; 
    delete mres2;
    delete mulMatrix;
    std::cout<<"He eleminado todo\n";
    //mulMatrix->~multMatrix_stub();
    std::cout<<"He cerrado la coneccion\n";
	return 0;
}
