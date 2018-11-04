
#include "MatrixInput.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//TODO don't forget to free the pointer !!!!
pair *getInput() {
    FILE *input = fopen("./input.txt", "r");//open the input file
    char mADimensions[MAX_FIRST_LINE];//an array that will contain the dimensions of the first matrix

    fgets(mADimensions, MAX_FIRST_LINE, input);


    int rowACount = mADimensions[0] - '0', columnACount = mADimensions[2] - '0';
    int **matrixA = (int **) malloc(columnACount * sizeof(int *));

    char *row = malloc(MAX_COLUMNS);

    for (int i = 0; i < rowACount; ++i) {

        fgets(row, MAX_COLUMNS, input);

        tokenizer(row, matrixA, i, columnACount);
    }

    char mBDimensions[MAX_FIRST_LINE];

    fgets(mBDimensions, MAX_FIRST_LINE, input);

    int rowBCount = mADimensions[0] - '0', columnBCount = mADimensions[2] - '0';
    int **matrixB = (int **) malloc(columnBCount * sizeof(int *));


    for (int i = 0; i < rowBCount; ++i) {

        fgets(row, MAX_COLUMNS, input);

        tokenizer(row, matrixB, i, columnBCount);
    }
    pair * matrices=malloc(sizeof(pair));
    matrix *matrix1 = malloc(sizeof(matrix));
    matrix1->mat = matrixA;
    matrix1->rowCount = rowACount;
    matrix1->columnCount = columnACount;

    matrix *matrix2 = malloc(sizeof(matrix));
    matrix2->mat = matrixB;
    matrix2->rowCount = rowBCount;
    matrix2->columnCount = columnBCount;

    matrices->first=matrix1;
    matrices->second=matrix2;
    return matrices;

}

void tokenizer(char *row, int **matrix, int rowNum, int rowLen) {


    row[rowLen * 2 - 1] = NULL;
    matrix[rowNum] = malloc(sizeof(int) * MAX_COLUMNS);

    int i = 0, j = 0;
    while (row[i] != NULL) {

        if (row[i] != ' ') {
            matrix[rowNum][j] = row[i] - '0';
            j++;
        }

        i++;
    }
    matrix[rowNum][i] = NULL;
}

void printMatrix(int **matrix, int rowCount, int columnCount) {
    for (int i = 0; i < rowCount; ++i) {
        for (int j = 0; j < columnCount; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

}
