//
// Created by omar_swidan on 10/10/18.
//

#ifndef SIMPLESHELL_INPUT_H
#define SIMPLESHELL_INPUT_H
#define MAX_FIRST_LINE 5
#define MAX_ROWS 20
#define MAX_COLUMNS 20
#define delimiter " "

#include "MatrixMultiplication.h"
pair* getInput();
void tokenizer(char * row,int **matrix,int rowNum,int rawLen);
void printMatrix(int **matrix,int rowCount,int columnCount);
#endif //SIMPLESHELL_INPUT_H
