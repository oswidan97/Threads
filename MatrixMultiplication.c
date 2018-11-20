#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <zconf.h>
#include "MatrixIO.h"

//
// Created by omar_swidan on 03/11/18.
//
void executeElementWise(pair *matrices,clock_t beginTime) {



    matrix *output = (matrix*)malloc(sizeof(matrix)); //allocate the output matrix as a struct matrix


    int outputColumnCount = ((matrix *) (matrices->first))->rowCount;
    int outputRowCount = ((matrix *) (matrices->second))->columnCount;

    int **outMatrix = (int**)malloc(outputRowCount * sizeof(int *)); //allocate the number of rows of the output matrix 2d array


    for (int i = 0; i < outputRowCount; ++i)
        outMatrix[i]=(int *)malloc(outputColumnCount* sizeof(int));


    //add the attributes of the output struct matrix
    output->mat = outMatrix;
    output->rowCount = outputRowCount;
    output->columnCount = outputColumnCount;


    pthread_t tid[outputRowCount*outputRowCount];//array of thread ids

    //array of arguments each for a thread
    matrixMultiplicationArgs **args=(matrixMultiplicationArgs**)malloc(outputRowCount*outputColumnCount*sizeof(matrixMultiplicationArgs*));

    //initialize each argument and activate the threads
    for (int i = 0; i < outputRowCount; ++i) {
        for (int j = 0; j < outputColumnCount; ++j) {
            args[i*outputColumnCount+j]=(matrixMultiplicationArgs*)malloc(sizeof(matrixMultiplicationArgs));
            args[i*outputColumnCount+j]->matrices = matrices;
            args[i*outputColumnCount+j]->output = output;
            args[i*outputColumnCount+j]->row = i;
            args[i*outputColumnCount+j]->column=j;
            pthread_create(&tid[i * outputColumnCount + j], NULL, getOutputElement,
                           (void *) args[i * outputColumnCount + j]);
        }
    }

    for (int k = 0; k < outputColumnCount * outputRowCount; ++k)//wait for all threads to finish execution
        pthread_join(tid[k], NULL);





    clock_t endElementWise=clock();
    printMatrix(outMatrix,outputRowCount,outputColumnCount,endElementWise-beginTime,1);
    free(outMatrix);
    free(output);
    for (int l = 0; l < outputRowCount*outputColumnCount; ++l)
        free(args[l]);
    free(args);



    return;

}
void* getOutputElement(void *args){
    matrixMultiplicationArgs *matArgs=(matrixMultiplicationArgs*)args;

    int outputRowCount=matArgs->output->rowCount;


    int **matrix1=((matrix*)matArgs->matrices->first)->mat;
    int **matrix2= ((matrix*)matArgs->matrices->second)->mat;
    int **output=  matArgs->output->mat;
    int mat1ColumnCount=((matrix*)(matArgs->matrices->first))->columnCount;


    int sum=0;//variable to hold the sum after each iteration
    for (int i = 0; i < mat1ColumnCount; ++i)//calculate element
        sum+=matrix1[matArgs->row][i]*matrix2[i][matArgs->column];



    output[matArgs->row][matArgs->column]=sum;


    pthread_exit(NULL);

}

void executeRowWise(pair *matrices,clock_t beginTime) {

    matrix *output = (matrix*)malloc(sizeof(matrix)); //allocate the output matrix as a struct matrix


    int outputColumnCount = ((matrix *) (matrices->first))->rowCount;
    int outputRowCount = ((matrix *) (matrices->second))->columnCount;

    int **outMatrix = (int**)malloc(outputRowCount * sizeof(int *)); //allocate the number of rows of the output matrix 2d array


    for (int i = 0; i < outputRowCount; ++i)
        outMatrix[i]=(int *)malloc(outputColumnCount* sizeof(int));


    //add the attributes of the output struct matrix
    output->mat = outMatrix;
    output->rowCount = outputRowCount;
    output->columnCount = outputColumnCount;


    pthread_t tid[outputRowCount];

    matrixMultiplicationArgs **args=(matrixMultiplicationArgs**)malloc(outputRowCount*sizeof(matrixMultiplicationArgs*));

    //initialize each argument and activate the threads
    for (int i = 0; i < outputRowCount; ++i) {
            args[i]=(matrixMultiplicationArgs*)malloc(sizeof(matrixMultiplicationArgs));
            args[i]->matrices = matrices;
            args[i]->output = output;
            args[i]->row = i;
            args[i]->column=-1;
            pthread_create(&tid[i], NULL, getOutputRow, (void *) args[i]);

    }

    for (int k = 0; k < outputRowCount; ++k)//wait for all threads to finish execution
        pthread_join(tid[k], NULL);



    clock_t endRowWise=clock();
    printMatrix(outMatrix,outputRowCount,outputColumnCount,endRowWise-beginTime,2);

    free(outMatrix);
    free(output);
    free(matrices);
    for (int l = 0; l < outputRowCount; ++l)
        free(args[l]);
    free(args);




    return;


}

void* getOutputRow(void* args) {
    matrixMultiplicationArgs *matArgs=(matrixMultiplicationArgs*)args;

    int outputRowCount=matArgs->output->rowCount;


    int **matrix1=((matrix*)matArgs->matrices->first)->mat;
    int **matrix2= ((matrix*)matArgs->matrices->second)->mat;
    int **output=  matArgs->output->mat;
    int mat1ColumnCount=((matrix*)(matArgs->matrices->first))->columnCount;
    int mat2ColumnCount=((matrix*)(matArgs->matrices->second))->columnCount;
    int sum=0;//variable to hold the sum after each iteration

        for (int i = 0; i < mat2ColumnCount; ++i) {//calculate a row of the output matrix
            sum=0;
            for (int j = 0; j <mat1ColumnCount ; ++j)
                sum += matrix1[matArgs->row][j] * matrix2[j][i];//matArgs->row is the row of the first matrix used in this calculation
            output[matArgs->row][i]=sum;
        }







    pthread_exit(NULL);
}
