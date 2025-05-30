#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 1000
#define NAME_LEN 50

typedef struct {
    char name[NAME_LEN];
    int midterm;
    int final;
} Student;

typedef struct {
    float excellent;
    float aboveAverage;
    float average;
    float belowAverage;
    float poor;
} ScoreStat;

Student students[MAX];
int midterms[MAX], finals[MAX];

int compare(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

float sum_range(int *arr, int from, int to) {
    float sum = 0;
    for (int i = from; i <= to; i++) sum += arr[i];
    return sum;
}

ScoreStat calculate_stats(int *arr, int n) {
    ScoreStat s;
    int p25 = (int)round(n * 0.25);
    int p50 = (int)round(n * 0.5);
    s.excellent = sum_range(arr, n - p25, n - 1) / p25;
    s.aboveAverage = sum_range(arr, n - p50, n - 1) / p50;
    s.average = sum_range(arr, 0, n - 1) / n;
    s.belowAverage = sum_range(arr, 0, p50 - 1) / p50;
    s.poor = sum_range(arr, 0, p25 - 1) / p25;
    return s;
}

int main() {
    FILE *file = fopen("abc.txt", "r");
    if (!file) {
        perror("Failed to open abc.txt");
        return 1;
    }

    int n;
    fscanf(file, "%d", &n);
    for (int i = 0; i < n; i++) {
        fscanf(file, "%s %d %d", students[i].name, &students[i].midterm, &students[i].final);
        midterms[i] = students[i].midterm;
        finals[i] = students[i].final;
    }
    fclose(file);

    qsort(midterms, n, sizeof(int), compare);
    qsort(finals, n, sizeof(int), compare);

    ScoreStat midStat = calculate_stats(midterms, n);
    ScoreStat finalStat = calculate_stats(finals, n);

    FILE *out = fopen("cba.txt", "w");
    for (int i = 0; i < n; i++) {
        if (students[i].midterm >= midStat.average &&
            students[i].final >= finalStat.poor) {
            fprintf(out, "%s %d %d\n", students[i].name, students[i].midterm, students[i].final);
        }
    }
    fclose(out);

    printf("Filtered students saved to cba.txt\n");
    return 0;
}