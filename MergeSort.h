//
// Created by omar_swidan on 20/11/18.
//

#ifndef THREADS_MERGESORT_H
#define THREADS_MERGESORT_H

#include "MatrixMultiplication.h"

pair *getUnsortedArray();
void execMergeSort();
void* mergeSort(void* args);
void merge(int arr[],int low,int mid,int high);
typedef struct mergeSortArgs{
    int* arr;
    int low;
    int high;

}mergeSortArgs;
#endif //THREADS_MERGESORT_H
