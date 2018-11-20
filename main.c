//
// Created by omar_swidan on 20/11/18.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "MatrixIO.h"
#include "MergeSort.h"

void matrixMultiplicationCompare();
int main() {
    matrixMultiplicationCompare();
    execMergeSort();
    return 0;

}
void matrixMultiplicationCompare(){
    pair* matrices=getInput();
    clock_t beginElementWise=clock();
    executeElementWise(matrices,beginElementWise);


    clock_t beginRowWise=clock();
    executeRowWise(matrices,beginRowWise);



    free(((matrix*)(matrices->first))->mat);
    free(((matrix*)(matrices->second))->mat);
    free(matrices->first);
    free(matrices->second);
}