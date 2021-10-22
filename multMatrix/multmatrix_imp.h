//Daniel Khomyakov y Eduardo Sebastian de Erice

#ifndef MULTMATRIX_IMP_H
#define MULTMATRIX_IMP_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "multmatrix.h"
#include "utils.h"

#define READ_MATRIX 'R'
#define MULT_MATRIX 'M'
#define WRITE_MATRIX 'W'
#define EXIT_MATRIX 'E'
#define CREATE_I_MATRIX 'I'
#define CREATE_R_MATRIX 'C'
#define OP_OK 'O'

class multMatrix_imp{
private:
    multMatrix* matrixImp = NULL;
    bool salir = false;
    int clientID=0;
public:
    multMatrix_imp(int clientID);
    ~multMatrix_imp();
    void exec();
};

#endif // MULTMATRIX_H
