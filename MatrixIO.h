//
// Created by omar_swidan on 10/10/18.
//

#ifndef SIMPLESHELL_INPUT_H
#define SIMPLESHELL_INPUT_H
#define MAX_FIRST_LINE 50
#define MAX_ROWS 100
#define MAX_COLUMNS 100
#define delimiter " "

#include <stdlib.h>
#include "MatrixMultiplication.h"
pair* getInput();
void tokenizer(char * row,int **matrix,int rowNum,int columnCount);
void printMatrixInFile(int **matrix, int rowCount, int columnCount, clock_t time, int procedureNumber);
void printMatrix(int **matrix, int rowCount, int columnCount);
#endif //SIMPLESHELL_INPUT_H
