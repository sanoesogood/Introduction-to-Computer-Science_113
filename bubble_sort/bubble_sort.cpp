/**
 * format: UTF-8
 * backup: https://github.com/sanoesogood/Introduction-to-Computer-Science_113/blob/main/bubble_sort/bubble_sort.cpp
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubblesort(int *data, int n);
void display(int *data, int n);

int comparison = 0;    // 比較次數 (for loop execution count)
int exchange = 0;

int main(){
    int *data = nullptr;
    int n;

    /* set random seed */
    srand(time(NULL));

    /**
     * new array
     * random value: 100 ~ 999
     */
    printf("the number of array elements: ");
    scanf("%d", &n);
    data = new int[n];

    for(int i=0; i<n; i++){
        data[i] = 100 + (rand() % 900);
    }
    
    printf("array:\n");
    display(data, n);
    printf("\n");

    /* sort */
    bubblesort(data, n);

    /* output */
    printf("sorted array by bubble sort:\n");
    display(data, n);
    printf("\n");

    printf("comparison times: %d\n", comparison);
    printf("exchange times: %d\n", exchange);
    printf("theoretical comparison times (worst case): %d\n", n*(n-1)/2);

    delete [] data;

    return 0;
}


void bubblesort(int *data, int n){
    int i, j, temp;
    bool is_exchange = false;

    for(j=n-2; j>=0; j--){
        is_exchange = false;

        /* scan */
        for(i=0; i<=j; i++){
            if(data[i] > data[i+1]){
                /* exchange */
                temp = data[i];
                data[i] = data[i+1];
                data[i+1] = temp;

                is_exchange = true;
                exchange++;
            }
            comparison++;
        }
        if(!is_exchange){
            break;
        }
    }
}

void display(int *data, int n){
    for(int i=0; i<n; i++)
        printf("%d ", data[i]);
    printf("\n");
}
