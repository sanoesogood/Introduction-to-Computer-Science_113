/**
 * format: UTF-8
 * backup: https://github.com/sanoesogood/Introduction-to-Computer-Science_113/blob/main/bubble_sort/bubble_sort.cpp
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubblesort(int *data, int n);
void display(int *data, int n);

int compare = 0;    // 比較次數 (for loop execute count)
int least_compare = 0;    // 陣列排序完當下的比較次數
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

    printf("compare times: %d\n", compare);
    printf("least compare times: %d\n", least_compare);
    printf("exchange times: %d\n", exchange);
    printf("theoretical times (worst case): %d\n", n*(n-1)/2);

    delete [] data;

    return 0;
}


void bubblesort(int *data, int n){
    int i, j, temp;
    bool is_exchange = false;

    for(j=n-2; j>=0; j--){
        is_exchange = 0;

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
            compare++;
        }
        if(!is_exchange){
            least_compare = compare - (j + 1);    // 因為 for 迴圈中, 從 i=0 到 i<=j, 共執行 j+1 次
            break;
        }
    }
}

void display(int *data, int n){
    for(int i=0; i<n; i++)
        printf("%d ", data[i]);
    printf("\n");
}
