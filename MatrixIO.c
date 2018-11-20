
#include "MatrixIO.h"
#include <stdio.h>
#include <bits/time.h>



pair *getInput() {
    FILE *input = fopen("./input.txt", "r");//open the input file
    char mADimensions[MAX_FIRST_LINE];//an array that will contain the dimensions of the first matrix

    fgets(mADimensions, MAX_FIRST_LINE, input);//get dimensiions of first matrix


    int rowACount = mADimensions[0] - '0', columnACount = mADimensions[2] - '0';
    int **matrixA = (int **) malloc(rowACount * sizeof(int *)); //allocate first matrix

    char *row = malloc(MAX_COLUMNS);//temp to get the line from the file in it

    for (int i = 0; i < rowACount; ++i) { //loop to read the matrix

        fgets(row, MAX_COLUMNS, input);

        tokenizer(row, matrixA, i, columnACount); //tokenize each line and add the result in matrixA
    }

    char mBDimensions[MAX_FIRST_LINE];

    fgets(mBDimensions, MAX_FIRST_LINE, input);

    int rowBCount = mADimensions[0] - '0', columnBCount = mADimensions[2] - '0';
    int **matrixB = (int **) malloc(rowBCount * sizeof(int *));


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


    row[rowLen * 2 - 1] = '\0'; //remove the last '\n' in the line
    matrix[rowNum] = malloc(sizeof(int) * rowLen);//allocate the columns of the first row of the matrix

    int i = 0, j = 0;
    while (row[i] != '\0') {//loop to remove spaces and add in the matrix the numbers

        if (row[i] != ' ') {
            matrix[rowNum][j] = row[i] - '0';
            j++;
        }

        i++;
    }

}

void printMatrix(int **matrix, int rowCount, int columnCount,clock_t time,int procedureNumber) {
    FILE* outFile=fopen("./output","a");

    for (int i = 0; i < rowCount; ++i) {
        for (int j = 0; j < columnCount; ++j) {
            fprintf(outFile,"%d ", matrix[i][j]);
        }
        fprintf(outFile,"\n");
    }

    fprintf(outFile, "End%d %f milliseconds\n", procedureNumber, (double)time * 1000 / CLOCKS_PER_SEC);

}
