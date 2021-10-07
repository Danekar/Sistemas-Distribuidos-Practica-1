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

#define IP_SERVER "127.0.0.1"
#define PORT_SERVER 3301

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
    multMatrix_imp();
    matrix_t* readMatrix(const char* fileName);
    matrix_t *multMatrices(matrix_t* m1, matrix_t *m2);
    void writeMatrix(matrix_t* m, const char *fileName);
    ~multMatrix_imp();
    matrix_t *createIdentity(int rows, int cols);
    matrix_t *createRandMatrix(int rows, int cols);
};

#endif // MULTMATRIX_H
