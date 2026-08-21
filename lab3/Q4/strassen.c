#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ---------- Matrix helpers (heap-allocated, sized exactly to n) ----------

int **allocMatrix(int n){
    int **M = malloc(n * sizeof(int *));
    for(int i = 0; i < n; i++)
        M[i] = malloc(n * sizeof(int));
    return M;
}

void freeMatrix(int n, int **M){
    for(int i = 0; i < n; i++)
        free(M[i]);
    free(M);
}

void add(int n, int **A, int **B, int **C){
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void subtract(int n, int **A, int **B, int **C){
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void standardMultiply(int n, int **A, int **B, int **C){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            C[i][j] = 0;
            for(int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
    }
}

// ---------- Strassen ----------

void strassen(int n, int **A, int **B, int **C){
    if(n <= 2){
        standardMultiply(n, A, B, C);
        return;
    }

    int m = n / 2;

    // every submatrix below is allocated at size m x m -- exactly what's
    // needed at this recursion level, not a fixed MAX x MAX like before.
    // this is the fix: stack usage per call is now O(1) (just pointers),
    // and heap usage per call is proportional to the actual submatrix size.
    int **A11 = allocMatrix(m), **A12 = allocMatrix(m);
    int **A21 = allocMatrix(m), **A22 = allocMatrix(m);

    int **B11 = allocMatrix(m), **B12 = allocMatrix(m);
    int **B21 = allocMatrix(m), **B22 = allocMatrix(m);

    int **P1 = allocMatrix(m), **P2 = allocMatrix(m), **P3 = allocMatrix(m);
    int **P4 = allocMatrix(m), **P5 = allocMatrix(m), **P6 = allocMatrix(m), **P7 = allocMatrix(m);

    int **T1 = allocMatrix(m), **T2 = allocMatrix(m);

    for(int i = 0; i < m; i++){
        for(int j = 0; j < m; j++){
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + m];
            A21[i][j] = A[i + m][j];
            A22[i][j] = A[i + m][j + m];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + m];
            B21[i][j] = B[i + m][j];
            B22[i][j] = B[i + m][j + m];
        }
    }

    add(m, A11, A22, T1);
    add(m, B11, B22, T2);
    strassen(m, T1, T2, P1);

    add(m, A21, A22, T1);
    strassen(m, T1, B11, P2);

    subtract(m, B12, B22, T2);
    strassen(m, A11, T2, P3);

    subtract(m, B21, B11, T2);
    strassen(m, A22, T2, P4);

    add(m, A11, A12, T1);
    strassen(m, T1, B22, P5);

    subtract(m, A21, A11, T1);
    add(m, B11, B12, T2);
    strassen(m, T1, T2, P6);

    subtract(m, A12, A22, T1);
    add(m, B21, B22, T2);
    strassen(m, T1, T2, P7);

    for(int i = 0; i < m; i++){
        for(int j = 0; j < m; j++){
            C[i][j]         = P1[i][j] + P4[i][j] - P5[i][j] + P7[i][j];
            C[i][j + m]     = P3[i][j] + P5[i][j];
            C[i + m][j]     = P2[i][j] + P4[i][j];
            C[i + m][j + m] = P1[i][j] - P2[i][j] + P3[i][j] + P6[i][j];
        }
    }

    // free everything allocated at this recursion level before returning --
    // without this, memory usage would balloon and eventually exhaust the
    // heap on large n, since nothing here was being freed before.
    freeMatrix(m, A11); freeMatrix(m, A12); freeMatrix(m, A21); freeMatrix(m, A22);
    freeMatrix(m, B11); freeMatrix(m, B12); freeMatrix(m, B21); freeMatrix(m, B22);
    freeMatrix(m, P1); freeMatrix(m, P2); freeMatrix(m, P3);
    freeMatrix(m, P4); freeMatrix(m, P5); freeMatrix(m, P6); freeMatrix(m, P7);
    freeMatrix(m, T1); freeMatrix(m, T2);
}

int main(){
    int n;

    printf("Enter matrix size (power of 2): ");
    scanf("%d", &n);

    int **A = allocMatrix(n);
    int **B = allocMatrix(n);
    int **C = allocMatrix(n);

    srand(time(NULL));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }

    printf("\nMatrix A:\n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            printf("%d ", A[i][j]);
        printf("\n");
    }

    printf("\nMatrix B:\n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            printf("%d ", B[i][j]);
        printf("\n");
    }

    strassen(n, A, B, C);

    printf("\nResult matrix (A x B):\n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            printf("%d ", C[i][j]);
        printf("\n");
    }

    freeMatrix(n, A);
    freeMatrix(n, B);
    freeMatrix(n, C);

    return 0;
}