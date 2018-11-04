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
    matrix *output=malloc(sizeof(matrix));


    int outputColumnCount=((matrix*)(matrices->first))->rowCount;
    int **outMatrix=malloc(outputColumnCount*sizeof(int*));
    output->mat=outMatrix;


    pthread_t tid;
    matrixMultiplicationArgs *args=malloc(sizeof(matrixMultiplicationArgs));
    args->matrices=*matrices;
    args->output=output;
    args->row=0;
    args->column=0;

    pthread_create(&tid,NULL,getProductElement,(void*)args);

    pthread_join(tid,NULL);


    pthread_exit(NULL);

}
void* getProductElement(void* args){
    matrixMultiplicationArgs *matArgs=(matrixMultiplicationArgs*)args;

    int outputRowCount=((matrix*)matArgs->matrices.first)->rowCount;
    int outputColumnCount=((matrix*)matArgs->matrices.second)->columnCount;
    int **matrix1=((matrix*)matArgs->matrices.first)->mat;
    int **matrix2= ((matrix*)matArgs->matrices.second)->mat;

    int sum=0;
    for (int i = 0; i < outputRowCount; ++i)
        sum+=matrix1[matArgs->row][i]*matrix2[i][matArgs->column];

    if ((matArgs->output->mat)[matArgs->row]==NULL)
        (matArgs->output->mat)[matArgs->row]=malloc(outputColumnCount*sizeof(int));

    ((matArgs->output)->mat)[matArgs->row][matArgs->column]=sum;

    pthread_exit(NULL);

}
