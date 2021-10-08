#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "multmatrix_stub.h"

int main (int argc, char** argv){

	multMatrix_stub mulMatrix = new multMatrix_stub();

    matrix_t* m1= mulMatrix.createRandMatrix(5,5);
    matrix_t* m2= mulMatrix.createIdentity(5,5);
    matrix_t* mres=mulMatrix.multMatrices(m1,m2);
    mulMatrix.writeMatrix(mres,"resultado.txt");
    matrix_t* m3=mulMatrix.readMatrix("resultado.txt");
    matrix_t* mres2=mulMatrix.multMatrices(m1,m3);
    mulMatrix.writeMatrix(mres2,"resultado2.txt");



    freeMatrix(m1);
    freeMatrix(m2);
    freeMatrix(mres);
    freeMatrix(m3);
    freeMatrix(mres2);
    delete mulMatrix;
	return 0;
}