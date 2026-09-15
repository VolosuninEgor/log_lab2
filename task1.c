#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void matrix_mul(int N) {
    int i = 0, j = 0, r;
    int **a, **b, **c, elem_c;    

    a = (int**)malloc(N * sizeof(int*));
    b = (int**)malloc(N * sizeof(int*));
    c = (int**)malloc(N * sizeof(int*));
    for (int k = 0; k < N; ++k){
        a[k] = (int*)malloc(N * sizeof(int));
        b[k] = (int*)malloc(N * sizeof(int));
        c[k] = (int*)malloc(N * sizeof(int));
    }

    srand(time(NULL)); 
    while (i < N) {
        while (j < N) {
            a[i][j] = rand() % 100 + 1;
            b[i][j] = rand() % 100 + 1;
            j++;
        }
        j = 0;
        i++;
    }

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            elem_c = 0;
            for (r = 0; r < N; r++) {
                elem_c = elem_c + a[i][r] * b[r][j];
            }
            c[i][j] = elem_c;
        }
    }
    
    for (int k = 0; k < N; ++k){
        free(a[k]);
        free(b[k]);
        free(c[k]);
    }
    free(a);
    free(b);
    free(c);
}


int main(void)
{
    int arr_n[11] = {100, 200, 400, 600, 800, 1000, 1200, 1400, 1600, 1800, 2000};    

    for (int i = 0; i < 11; ++i){
        double sr = 0.0;
        for (int j = 0; j < 3; ++j) {
            clock_t start, end; 
            start = clock();
            matrix_mul(arr_n[i]);
            end = clock();
            sr += (double)(end-start)/CLOCKS_PER_SEC;
        }
        sr /= 3;
        printf("%d n: %.3f s\n", arr_n[i], sr);
    }

    return 0;
}













