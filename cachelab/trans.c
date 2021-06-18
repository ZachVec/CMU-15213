/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);
void trans32x32(int A[32][32], int B[32][32]) {
    /*
     * s = 5, E = 1, b = 5
     * 32 * 32: miss cnt < 300
     */
    int x1, x2, x3, x4, x5, x6, x7, x8;
    for(int i = 0; i < 32; i+=8) {
        for(int j = 0; j < 32; j += 8) {
            for(int i1 = i; i1 < i + 8; i1++) {
                x1 =   A[i1][j];
                x2 = A[i1][j+1];
                x3 = A[i1][j+2];
                x4 = A[i1][j+3];
                x5 = A[i1][j+4];
                x6 = A[i1][j+5];
                x7 = A[i1][j+6];
                x8 = A[i1][j+7];
                B[j][i1]   = x1;
                B[j+1][i1] = x2;
                B[j+2][i1] = x3;
                B[j+3][i1] = x4;
                B[j+4][i1] = x5;
                B[j+5][i1] = x6;
                B[j+6][i1] = x7;
                B[j+7][i1] = x8;
            }
        }
    }
}
/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N]) {
    /* M rows, N columns
     * s = 5, E = 1, b = 5
     * 32 * 32: miss cnt < 300
     * 64 * 64: miss cnt < 1300
     * 61 * 67: miss cnt < 2000
     */
    
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            // B[j][i] = A[j][i]
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

