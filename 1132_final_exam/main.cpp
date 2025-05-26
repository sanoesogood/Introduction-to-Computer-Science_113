/**
 * backup: 
 * https://github.com/sanoesogood/Introduction-to-Computer-Science_113/blob/main/1132_final_exam/main.cpp
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DEBUG 1
// 可切換排序方法 ('q': quick sort, 'm': merge sort, 'b': bubble sort)
#define METHOD 'q'

#define SORT_METHOD(arr, n, from, to, method) \
    do{ \
        if((method) == 'q') qsort(arr, from, to); \
        else if((method) == 'm') msort(arr, n, from, to); \
        else if((method) == 'b') bsort(arr, from, to); \
    }while(0)

#define printStd(std, label) \
    printf("%f %f %f %f %f (%s)\n", \
            std.excellent, \
            std.aboveAverage, \
            std.average, \
            std.belowAverage, \
            std.poor, \
            (label) \
    );

// 五標
typedef struct{
    float excellent;
    float aboveAverage;
    float average;
    float belowAverage;
    float poor;
} std_t;

typedef struct{
    char name[8];
    int midterm;
    int finalexam;
} student_t;

void qsort(int *arr, int from, int to);
void msort(int *arr, int n, int from, int to);
void bsort(int *arr, int from, int to);

int  split(int *arr, int from, int to);
void merge(int *arr, int n, int f1, int t1, int f2, int t2);
float sumArr(int *arr, int from, int to);
std_t examStd(int *arr, int n);

int main(){
    const char inputPath [] = "abc.txt";
    const char outputPath[] = "cba.txt";
    student_t *gradeSheet = NULL;
    int *gradeArr = NULL;  // 暫存成績
    unsigned int n;  // student 總數
    std_t midtermStd, finalStd;

    // 開啟檔案
    FILE *finput = fopen(inputPath, "r");
    if(finput == NULL){
        perror(inputPath);
        return 1;
    }
    FILE *foutput = fopen(outputPath, "w");
    if(foutput == NULL){
        perror(outputPath);
        fclose(finput);
        return 1;
    }

    // 讀入 data 並用陣列儲存
    fscanf(finput, "%u", &n);
    if(n < 4){
        printf("n must be a positive integer and grater than or equal to 4.");
        fclose(finput);
        fclose(foutput);
        return 1;
    }

    gradeSheet = new student_t[n];
    gradeArr = new int[n];

    for(int i=0; i<n; i++){
        fscanf(finput, "%7s %d %d",
               gradeSheet[i].name,
               &gradeSheet[i].midterm,
               &gradeSheet[i].finalexam
        );
    }

    // 先將期中考分數由低到高排序，並計算五標
    // (老師上課有說, 頂標最低分數: 前25%的平均, 前: 前50%, 均: 所有人, 後: 後50%, 底: 後25%)
    for(int i=0; i<n; i++){
        gradeArr[i] = gradeSheet[i].midterm;
    }
    SORT_METHOD(gradeArr, n, 0, n-1, METHOD);
    midtermStd = examStd(gradeArr, n);

    // 再將期末考分數由低到高排序，並計算五標
    for(int i=0; i<n; i++){
        gradeArr[i] = gradeSheet[i].finalexam;
    }
    SORT_METHOD(gradeArr, n, 0, n-1, METHOD);
    finalStd = examStd(gradeArr, n);

    #if(DEBUG)
    printStd(midtermStd, "midterm");
    printStd(finalStd, "final exam");
    #endif

    // 找出期中考均標以上，期末考底標以上的學生，並寫入 cba.txt
    for(int i=0; i<n; i++){
        if( gradeSheet[i].midterm >= midtermStd.average &&
            gradeSheet[i].finalexam >= finalStd.poor){
            fprintf(foutput, "%s %d %d\n", 
                    gradeSheet[i].name, 
                    gradeSheet[i].midterm, 
                    gradeSheet[i].finalexam
            );
        }
    }

    // 記得關閉！
    fclose(finput);
    fclose(foutput);
    delete[] gradeSheet;
    delete[] gradeArr;

    return 0;
}

float sumArr(int *arr, int from, int to){
    float sum = 0;
    for(int i=from; i<=to; i++){
        sum += arr[i];
    }
    return sum;
}

/**
 * 計算考試五標 (頂前均後底)
 */
std_t examStd(int *arr, int n){
    std_t std;
    unsigned int p25, p50;

    // 四捨五入
    p25 = (unsigned int)round(n * 0.25);
    p50 = (unsigned int)round(n * 0.50);

    std.excellent = sumArr(arr, n-p25, n-1) / p25;
    std.aboveAverage = sumArr(arr, n-p50, n-1) / p50;
    std.average = sumArr(arr, 0, n-1) / n;
    std.belowAverage = sumArr(arr, 0, p50-1) / p50;
    std.poor = sumArr(arr, 0, p25-1) / p25;
    
    // for(int i=0; i<3; i++){
    //     if(i == 0){
    //         p = n;
    //         std[2] = sumArr(arr, 0, p-1) / p;
    //     }
    //     else{
    //         p = (unsigned int)round(n * (1./(2*i)));
    //         std[2-i] = sumArr(arr, 0, p-1) / p;
    //         std[2+i] = sumArr(arr, n-p, n-1) / p;
    //     }
    // }
    return std;
}

void qsort(int *arr, int from, int to){
    if(from >= to) return;
    int k = split(arr, from, to);

    qsort(arr, from, k-1);
    qsort(arr, k+1, to);
}

int split(int *array, int from, int to){
    int pivot = array[from];
    int temp;
    int left = from; int right = to;
    int k = from;

    /* 比 pivot 小的數字會依次排在 from+1, from+2, ...的位置, 直到比較到 to 時結束
       此時位置 k 的左邊都是比 pivot 小的數字, 右邊都是比 pivot 大的數字
       而且位置 k 的數比 pivot 小, 這時只要交換位置 k 與 pivot 的資料, 就可以達成
       pivot 左邊都是比自己小的數, 右邊都是比自己大的數的目的了 (省記憶體)
    */
    for(int i=from+1; i<=to; i++){
        if(array[i] < pivot){
            k++;  // from+1, from+2, ...
            temp = array[i];
            array[i] = array[k];
            array[k] = temp;
        }
    }
    array[from] = array[k];
    array[k] = pivot;

    return  k;
}

void msort(int *a, int n, int from, int to){
    if(from == to) return;
    int mid = (from + to)/2;

    msort(a, n, from, mid);
    msort(a, n, mid+1, to);
    merge(a, n, from, mid, mid+1, to);
}

void merge(int *a, int n, int f1, int t1, int f2, int t2){
    int *b = new int[n];
    int p1 = f1;
    int p2 = f2;
    int idx = f1;

    while(p1 <= t1 && p2 <= t2){
        if(a[p1] >= a[p2]) b[idx++] = a[p2++];
        else               b[idx++] = a[p1++];
    }
    while(p1 <= t1) b[idx++] = a[p1++];
    while(p2 <= t2) b[idx++] = a[p2++];

    for(int i=f1; i <= t2; i++) a[i] = b[i];
    delete [] b;
}

void bsort(int *a, int from, int to){
    if(to == from) return;
    int i, temp;

    for(i=from; i<to; i++){
        if(a[i+1] < a[i]){
            temp = a[i+1];
            a[i+1] = a[i];
            a[i] = temp;
        }
    }
    return bsort(a, from, to-1);
}
