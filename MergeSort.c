//
// Created by omar_swidan on 20/11/18.
//

#include <zconf.h>
#include <bits/types/FILE.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "MergeSort.h"

void execMergeSort(){

    pair* inputPair=getUnsortedArray();
    int *arr=inputPair->first;
    mergeSortArgs args;
    args.arr=arr;
    args.low=0;
    args.high=(int)inputPair->second-1;
    pthread_t tid;
    pthread_create(&tid,NULL,mergeSort,&args);
    pthread_join(tid,NULL);

    for (int i = 0; i < (int)inputPair->second; ++i) {
        printf("%d ",arr[i]);
    }
}
pair *getUnsortedArray() {
    FILE* inputFile=fopen("./inputMerge","r");//open the input file
    int length = 0;

    fscanf(inputFile,"%d",&length);//input the length of the array
    int *inputArray=malloc(length*sizeof(int));//allocate the array
    for (int i = 0; i < length; ++i)
        fscanf(inputFile,"%d",&inputArray[i]);//input the velues of the array

    pair *input=malloc(sizeof(pair*));
    input->first=inputArray;
    input->second=(void*)length;

    return input;
}


void merge(int *arr, int low, int mid, int high) {
        int i, j, k;
        int n1 = mid - low + 1;
        int n2 =  high - mid;

        int L[n1], R[n2]; //create left and right arrays

        for (i = 0; i < n1; i++)//add the data to the left array
            L[i] = arr[low + i];
        for (j = 0; j < n2; j++)//add the data to the right array
            R[j] = arr[mid + 1+ j];

        i = 0;
        j = 0;
        k = low;
        while (i < n1 && j < n2)//merge the left and the right into the parent array
        {
            if (L[i] <= R[j]) {
                arr[k] = L[i];
                i++;
            }
            else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }


        while (i < n1){//copy the remaining elements of the left array if available
            arr[k] = L[i];
            i++;
            k++;
        }

        while (j < n2){ //copy the remaining elements of the right array if available

            arr[k] = R[j];
            j++;
            k++;
        }
    }


void* mergeSort(void* args) {
    mergeSortArgs* sortArgs=(mergeSortArgs*)args;
    if (sortArgs->low < sortArgs->high)
    {

        int mid = sortArgs->low+(sortArgs->high-sortArgs->low)/2;

        mergeSortArgs args1={sortArgs->arr, sortArgs->low, mid};
        pthread_t tid1;
        pthread_create(&tid1,NULL,mergeSort,&args1);

        mergeSortArgs args2={sortArgs->arr, mid+1, sortArgs->high};
        pthread_t tid2;
        pthread_create(&tid2,NULL,mergeSort,&args2);

        pthread_join(tid1,NULL);
        pthread_join(tid2,NULL);
        merge(sortArgs->arr, sortArgs->low, mid, sortArgs->high);
    }
   pthread_exit(NULL);
}


