#define DEBUG 0

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "..\utils\utils.h"

void mergesort (int *array, int from, int to);
void merge(int *array, int from, int to);

int n = 9;

int main(){
    int *a = new int[n];

    srand(time(NULL));
    randomNum(a, n, -10, 10);

    printf("array: ");
    for(int i=0; i<n; i++){
        printf("%d ", a[i]);
    }
    printf("\n");

    mergesort(a, 0, n-1);

    printf("sorted array: ");
    for(int i=0; i<n; i++){
        printf("%d ", a[i]);
    }

    return 0;
}

void mergesort(int *array, int from, int to){
    int mid;

    if(from == to) return;

    mid = (from + to)/2;

    #if DEBUG
    for(int from=0; from<n; from++){
        printf("%d ", array[from]);
    }
    printf(" %d %d", from, to);
    printf("\n");
    #endif

    mergesort(array, from, mid);
    mergesort(array, mid+1, to);
    merge(array, from, to);

    return;
}

void merge(int *array, int from, int to){
    int mid = (from + to) / 2;
    int l = from, r = mid + 1;
    int idx = from;
    int *temp = new int[n];

    #if DEBUG
    printf("\nmerge... ");
    printf("%d %d\n", from, to);
    printf("left array: ");
    for(int j=from; j<=mid; j++){
        printf("%d ", array[j]);
    }
    printf("\n");

    printf("right array: ");
    for(int j=mid+1; j<=to; j++){
        printf("%d ", array[j]);
    }
    printf("\n");
    #endif

    while (l <= mid && r <= to) {
        if(array[l] <= array[r]) temp[idx++] = array[l++];
        else                     temp[idx++] = array[r++];
    }
    while (l <= mid) temp[idx++] = array[l++];
    while (r <= to)  temp[idx++] = array[r++];
    for (int k=from; k<=to; k++) array[k] = temp[k];

    #if DEBUG
    printf("==> ");
    for(int j=from; j<=to; j++){
        printf("%d ", array[j]);
    }
    printf("\n");
    printf("-----merge finished-----\n");
    #endif
}
