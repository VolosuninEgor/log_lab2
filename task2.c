#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100000

void shell(int *items, int count)
{
    int i, j, gap, k;
    int x, a[5];
    a[0] = 9; a[1] = 5; a[2] = 3; a[3] = 2; a[4] = 1;
    for (k = 0; k < 5; k++) {
        gap = a[k];
        for (i = gap; i < count; ++i) {
            x = items[i];
            for (j = i - gap; (j >= 0) && (x < items[j]); j = j - gap)
                items[j + gap] = items[j];
            items[j + gap] = x;
        }
    }
}

void qs(int *items, int left, int right)
{
    int i, j;
    int x, y;
    i = left; j = right;
    x = items[(left + right) / 2];
    do {
        while ((items[i] < x) && (i < right)) i++;
        while ((x < items[j]) && (j > left)) j--;
        if (i <= j) {
            y = items[i];
            items[i] = items[j];
            items[j] = y;
            i++; j--;
        }
    } while (i <= j);
    if (left < j) qs(items, left, j);
    if (i < right) qs(items, i, right);
}


void gen_random(int* arr) {
    for (int i = 0; i < N; ++i) {
        arr[i] = rand() % 1000 + 1;
    }
}


void gen_increasing(int* arr) {    // возрастающий
    arr[0] = rand() % 10 + 1;
    for (int i = 1; i < N; ++i) {
        arr[i] = arr[i-1] + rand() % 10 + 1;
    }
}

void gen_descending(int* arr) {    // убывающий
    arr[0] = 1000000 + (rand() % 9000000) + 1;
    for (int i = 1; i < N; ++i) {
        arr[i] = arr[i-1] - (rand() % 10 + 1);
    }
}

void gen_mix(int* arr){
    arr[0] = rand() % 10 + 1; 
    for (int i = 1; i < N/2; ++i) {
        arr[i] = arr[i-1] + rand() % 10 + 1;
    }
    for (int i = N/2; i < N; ++i) {
        arr[i] = arr[i-1] - (rand() % 10 + 1);
    }
}

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

double get_time_shell(int *arr)
{
    clock_t start = clock();
    shell(arr, N);
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

double get_time_qs(int *arr)
{
    clock_t start = clock();
    qs(arr, 0, N - 1);
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

double get_time_qsort(int *arr)
{
    clock_t start = clock();
    qsort(arr, N, sizeof(int), compare);
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

int main(void)
{
    srand(time(NULL));
    int *arr = (int*)malloc(N * sizeof(int)); 
    
    printf("N = %d\n", N);
    printf("тип массива:  shell     qs        qsort\n");

    gen_random(arr);
    printf("случайный:    %0.6f, %0.6f, %0.6f\n", get_time_shell(arr), get_time_qs(arr), get_time_qsort(arr));

    gen_increasing(arr);
    printf("возрастающий: %0.6f, %0.6f, %0.6f\n", get_time_shell(arr), get_time_qs(arr), get_time_qsort(arr));

    gen_descending(arr);
    printf("убывающий:    %0.6f, %0.6f, %0.6f\n",get_time_shell(arr), get_time_qs(arr), get_time_qsort(arr));

    gen_mix(arr);
    printf("воз+убыв      %0.6f, %0.6f, %0.6f\n",get_time_shell(arr), get_time_qs(arr), get_time_qsort(arr));

    free(arr);
    return 0;
}




