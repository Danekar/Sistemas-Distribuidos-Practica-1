#ifndef MULTMATRIX_IMP_H
#define MULTMATRIX_IMP_H

#include "multmatrix.h"
#include "utils.h"

#define READ_MATRIX 'R'
#define MULT_MATRIX 'M'
#define WRITE_MATRIX 'W'
#define EXIT_ATRIX 'E'
#define CREATE_I_MATRIX 'I'
#define CREATE_R_MATRIX 'C'

typedef struct matrix_t
{
    int rows;
    int cols;
    int* data;
}matrix_t;

class multMatrix
{
private:
    multmatrix* multMatrix = nullptr;
    bool salir = false;
    int clientID=0;
public:
    multmatrix_imp(int clientID);
    ~multmatrix_imp();
    void exec();
};

#endif // MULTMATRIX_H
