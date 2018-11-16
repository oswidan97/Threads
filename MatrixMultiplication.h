//
// Created by omar_swidan on 04/11/18.
//

#ifndef THREADS_MATRIXMULTIPLICATION_H
#define THREADS_MATRIXMULTIPLICATION_H
typedef struct pair{ //a generic pair
    void* first;
    void* second;
}pair;
typedef struct matrix{ //representation of a matrix
    int **mat;
    int rowCount;
    int columnCount;
}matrix;
typedef struct matrixMultiplicationArgs{

    pair *matrices;
    matrix* output;
    int row;
    int column;
}matrixMultiplicationArgs;
void executeElementWise();
void* getProductElement(void* args);
#endif //THREADS_MATRIXMULTIPLICATION_H
