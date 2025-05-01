#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

void randomNum(int *array, int n, int min, int max){
    for(int i=0; i<n; i++){
        array[i] = min + rand()%(max - min + 1);
    }
}