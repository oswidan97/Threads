#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <zconf.h>
#include "MatrixInput.h"

//
// Created by omar_swidan on 03/11/18.
//
void executeElementWise() {
    pair *matrices = getInput();


    matrix *output = (matrix*)malloc(sizeof(matrix)); //allocate the iutout matrix as a struct matrix


    int outputColumnCount = ((matrix *) (matrices->first))->rowCount;
    int outputRowCount = ((matrix *) (matrices->second))->columnCount;

    int **outMatrix = (int**)malloc(outputRowCount * sizeof(int *)); //allocate the number of rows of the output matrix 2d array

    //printf("%d %d",outputColumnCount,outputRowCount);
    for (int i = 0; i < outputRowCount; ++i)
        outMatrix[i]=(int *)malloc(outputColumnCount* sizeof(int));


    //add the attributes of the output struct matrix
    output->mat = outMatrix;
    output->rowCount = outputRowCount;
    output->columnCount = outputColumnCount;


    pthread_t tid[outputRowCount*outputRowCount];

    matrixMultiplicationArgs **args=(matrixMultiplicationArgs**)malloc(outputRowCount*outputColumnCount*sizeof(matrixMultiplicationArgs*));


    for (int i = 0; i < outputRowCount; ++i) {
        for (int j = 0; j < outputColumnCount; ++j) {
            args[i*outputColumnCount+j]=(matrixMultiplicationArgs*)malloc(sizeof(matrixMultiplicationArgs));
            args[i*outputColumnCount+j]->matrices = matrices;
            args[i*outputColumnCount+j]->output = output;
            args[i*outputColumnCount+j]->row = i;
            args[i*outputColumnCount+j]->column=j;
            pthread_create(&tid[i*outputColumnCount+j], NULL, getProductElement, (void *) args[i*outputColumnCount+j]);
        }
    }

    for (int k = 0; k < outputColumnCount * outputRowCount; ++k)//wait for all threads to finish execution
        pthread_join(tid[k], NULL);



    printMatrix(outMatrix,outputRowCount,outputColumnCount);


    free(outMatrix);
    free(output);
    free(((matrix*)(matrices->first))->mat);
    free(((matrix*)(matrices->second))->mat);
    free(matrices->first);
    free(matrices->second);
    free(matrices);
    for (int l = 0; l < outputRowCount*outputColumnCount; ++l)
        free(args[l]);
    free(args);
    pthread_exit(NULL);

}
void* getProductElement(void* args){
    matrixMultiplicationArgs *matArgs=(matrixMultiplicationArgs*)args;
    //printf("kk");
    int outputRowCount=matArgs->output->rowCount;


    int **matrix1=((matrix*)matArgs->matrices->first)->mat;
    int **matrix2= ((matrix*)matArgs->matrices->second)->mat;
    int **output=  matArgs->output->mat;

    int sum=0;//variable to hold the sum after each iteration
    for (int i = 0; i < outputRowCount; ++i)//calculate element
        sum+=matrix1[matArgs->row][i]*matrix2[i][matArgs->column];
    printf("element %d is %d\n",(matArgs->row)*outputRowCount+matArgs->column,sum);



    output[matArgs->row][matArgs->column]=sum;


   // printf("%d",output[matArgs->row][matArgs->column]);


    pthread_exit(NULL);

}
