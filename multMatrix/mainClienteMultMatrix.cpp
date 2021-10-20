#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "multmatrix_stub.h"

using namespace std;

bool comprobarIdentidad(int row, int col){
	bool esIdentidad = false;
	if(row == col){
		esIdentidad = true;
	}
	return esIdentidad;
}

int menu(int opciones){
	multMatrix_stub* mulMatrixExtra = new multMatrix_stub();
	bool salir = false;
	int row, col;
	matrix_t* m1RandClient= new matrix_t[1];
	matrix_t* m1IdenClient= new matrix_t[1];
	matrix_t* matrizCreadaClient= new matrix_t[1];

	do{
		cout<< "Elige de las opciones:\n";
		cout<< "1 - Crear una matriz aleatoria\n";
		cout<< "2 - Crear una matriz identidad\n";
		cout<< "3 - Crear una matriz\n";
		cout<< "0 - Salir\n";
		cin>>opciones;
		switch(opciones){
			case 1:
			{
				cout<<"Inserta las dimensiones de la matriz\n";
				cin >> row >> col;
				cout << "Generando matriz Aleatoria de "<< row << "," << col<< endl;
				if(row > 0 || col > 0){
					m1RandClient = mulMatrixExtra->createRandMatrix(row,col);
				}else{
					cout<< "La matriz tiene que tener dimesiones positivas\n";
				}			
			}
			break;
			case 2:
			{
				cout<<"Inserta las dimensiones de la matriz\n";
				cin >> row >> col;
				cout << "Generando matriz Identidad de "<< row << "," << col<< endl;
				if(row > 0 || col > 0){
					if(comprobarIdentidad(row, col)){
						m1IdenClient = mulMatrixExtra->createRandMatrix(row,col);
					}else{
						cout << "Una matriz identidad tiene el mismo numero de columnas y filas, prueba otravez.\n";
					}	
				}else{
					cout<< "La matriz tiene que tener dimesiones positivas\n";
				}						
			}
			break;
			case 3:
			{
				if(row > 0 || col > 0){
					matrizCreadaClient = new matrix_t[1];
					cout<<"Inserta las dimensiones de la matriz\n";
					cin >> row >> col;
					matrizCreadaClient->rows = row;
					matrizCreadaClient->cols = col;
					matrizCreadaClient->data = new int[row*col];
					cout<<"Inserta los datos\n";
					for(int i = 0; i < row*col; i++){
						cin>>matrizCreadaClient->data[i];
					}
				}else{
					cout<< "La matriz tiene que tener dimesiones positivas\n";
				}
				
			}
			break;
			case 0:
				salir= true;
			break;
			default:
				cout<<"Esa no es una opcion\n";
			break;
		}
	}while(!salir);
	return opciones;
}

int main (int argc, char** argv){
//Practica !
	multMatrix_stub* mulMatrix = new multMatrix_stub();

	matrix_t* m1= mulMatrix->createRandMatrix(5,5);
  	matrix_t* m2= mulMatrix->createIdentity(5,5);
   	matrix_t* mres=mulMatrix->multMatrices(m1,m2);
   	mulMatrix->writeMatrix(mres,"resultado.txt");
   	matrix_t* m3=mulMatrix->readMatrix("resultado.txt");    
   	matrix_t* mres2=mulMatrix->multMatrices(m1,m3);
   	mulMatrix->writeMatrix(mres2,"resultado2.txt");
	std::cout<<"He terminado todos los procesos\n";

	delete m1;
    delete m2;
    delete mres;
    delete m3; 
    delete mres2;
    delete mulMatrix;
//Extra
	int opciones = -1;	
	menu(opciones);
	return 0;
}
