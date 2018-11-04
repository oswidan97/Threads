#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "MatrixInput.h"

//
// Created by omar_swidan on 03/11/18.
//
void executeElementWise() {
    pair* matrices=getInput();
    matrix* matrix1= (matrix *) ((matrices->first));
    matrix* matrix2= (matrix *) ((matrices->second));
    pthread_t tid;
    matrixMultiplicationArgs *args=malloc(sizeof(matrixMultiplicationArgs));
    args->matrices=*matrices;
    args->row=0;
    args->column=0;

    //pthread_create(&tid,NULL,getProductElement,(void*)args);

}
void* getProductElement(void* args){
    matrixMultiplicationArgs *matArgs=(matrixMultiplicationArgs*)args;
    int **matrix1=matArgs->matrices.first;
    int **matrix2=matArgs->matrices.second;


}
