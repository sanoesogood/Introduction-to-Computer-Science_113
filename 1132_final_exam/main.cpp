#define DEBUG 0

#include <stdio.h>
#include <stdlib.h>

void qsort(int *a, int from, int to);
void msort(int *a, int from, int to);
void bsort(int *a, int from, int to);

int  split(int *a, int from, int to);
void merge(int *a, int f1, int t1, int f2, int t2);
int sumArr(int *a, int from, int to);

typedef struct{
    char name[8];
    int midterm;
    int final;
} student;

student *gradeSheet;
int n;

int main(){
    student a;
    int *gradeArr;
    float range[5];
    float midtermStd[5], finalStd[5];  // 頂前均後底
    int p;  // 人數

    FILE *fp = fopen("abc.txt", "r");  // abc.txt 與主程式執行檔在同一個目錄下
    FILE *output = fopen("cba.txt", "w");

    fscanf(fp, "%d", &n);
    gradeSheet = new student[n];
    gradeArr = new int[n];

    // 讀入 data 並用陣列儲存
    if(fp == NULL)
        perror("this file does not exist");

    for(int i=0; i<n; i++){
        fscanf(fp, "%s", &a.name);
        fscanf(fp, "%d", &a.midterm);
        fscanf(fp, "%d", &a.final);
        gradeSheet[i] = a;
    }

    // 先將期中考分數由低到高排序，並計算五標)
    // (老師上課有說, 頂標最低分數: 前25%的平均, 前: 前50%, 均: 所有人, 後: 後50%, 底: 後25%)
    for(int i=0; i<n; i++){
        gradeArr[i] = gradeSheet[i].midterm;
    }
    qsort(gradeArr, 0, n-1);
    for(int i=0; i<3; i++){
        if(i == 0){
            p = n;
            midtermStd[2] = (float)sumArr(gradeArr, 0, p-1) / p;
        }
        else{
            p = n*(1./(2*i));
            midtermStd[2-i] = (float)sumArr(gradeArr, 0, p-1) / p;
            midtermStd[2+i] = (float)sumArr(gradeArr, n-p, n-1) / p;
        }
    }

    // 再將期末考分數由低到高排序，並計算五標
    for(int i=0; i<n; i++){
        gradeArr[i] = gradeSheet[i].final;
    }
    qsort(gradeArr, 0, n-1);
    for(int i=0; i<3; i++){
        if(i == 0){
            p = n;
            finalStd[2] = (float)sumArr(gradeArr, 0, p-1) / p;
        }
        else{
            p = n*(1./(2*i));
            finalStd[2-i] = (float)sumArr(gradeArr, 0, p-1) / p;
            finalStd[2+i] = (float)sumArr(gradeArr, n-p, n-1) / p;
        }
    }

    #if(DEBUG)
    for(int i=0; i<5; i++){
        printf("%f ", midtermStd[i]);
    }
    printf("\n");
    for(int i=0; i<5; i++){
        printf("%f ", finalStd[i]);
    }
    #endif

    // 找出期中考均標以上，期末考底標以上的學生，並寫入 cba.txt
    for(int i=0; i<n; i++){
        if( gradeSheet[i].midterm >= midtermStd[2] &&\
            gradeSheet[i].final   >= finalStd[0]
        ){
            fprintf(output, "%s ", gradeSheet[i].name);
            fprintf(output, "%d ", gradeSheet[i].midterm);
            fprintf(output, "%d\n", gradeSheet[i].final);
        }
    }

    // 記得關閉！
    fclose(fp);
    fclose(output);
    delete [] gradeSheet;
    delete [] gradeArr;

    return 0;
}

int sumArr(int *a, int from, int to){
    int sum = 0;
    for(int i=from; i<=to; i++){
        sum += a[i];
    }
    return sum;
}

void qsort(int *a, int from, int to){
    if(from >= to) return;
    int k = split(a, from, to);
    
    qsort(a, from, k-1);
    qsort(a, k+1, to);
}

int split(int *a, int from, int to){
    int pivot = a[from];
    int temp;
    int left = from; int right = to;
    int k = from;

    for(int i=1; i<=to-from; i++){
        if(a[from+i] < pivot){
            k++;
            temp = a[from+i];
            a[from+i] = a[k];
            a[k] = temp;
        }
    }
    a[from] = a[k];
    a[k] = pivot;

    return  k;
}


void msort(int *a, int from, int to){
    if(from == to) return;
    int mid = (from + to)/2;

    msort(a, from, mid);
    msort(a, mid+1, to);
    merge(a, from, mid, mid+1, to);
}

void merge(int *a, int f1, int t1, int f2, int t2){
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
