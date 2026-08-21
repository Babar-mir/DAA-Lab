#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int **allocMatrix(int n){
    int **M = malloc(n * sizeof(int *));
    for(int i = 0; i < n; i++) M[i] = malloc(n * sizeof(int));
    return M;
}
void freeMatrix(int n, int **M){ for(int i=0;i<n;i++) free(M[i]); free(M); }

void add(int n, int **A, int **B, int **C){
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) C[i][j]=A[i][j]+B[i][j];
}

void specialMultiply(int n, int **A, int **B, int **C){
    if(n == 1){ C[0][0] = A[0][0]*B[0][0]; return; }
    int m = n/2;
    int **A1=allocMatrix(m), **A2=allocMatrix(m);
    int **B1=allocMatrix(m), **B2=allocMatrix(m);
    int **P=allocMatrix(m), **Q=allocMatrix(m);
    int **R=allocMatrix(m), **S=allocMatrix(m);
    for(int i=0;i<m;i++) for(int j=0;j<m;j++){
        A1[i][j]=A[i][j]; A2[i][j]=A[i][j+m];
        B1[i][j]=B[i][j]; B2[i][j]=B[i][j+m];
    }
    specialMultiply(m,A1,B1,P); specialMultiply(m,A2,B2,Q); add(m,P,Q,R);
    specialMultiply(m,A1,B2,P); specialMultiply(m,A2,B1,Q); add(m,P,Q,S);
    for(int i=0;i<m;i++) for(int j=0;j<m;j++){
        C[i][j]=R[i][j]; C[i][j+m]=S[i][j];
        C[i+m][j]=S[i][j]; C[i+m][j+m]=R[i][j];
    }
    freeMatrix(m,A1); freeMatrix(m,A2); freeMatrix(m,B1); freeMatrix(m,B2);
    freeMatrix(m,P); freeMatrix(m,Q); freeMatrix(m,R); freeMatrix(m,S);
}

void generateSpecialMatrix(int n, int **M){
    if(n == 1){ M[0][0] = rand()%10; return; }
    int m = n/2;
    int **M1 = allocMatrix(m), **M2 = allocMatrix(m);
    generateSpecialMatrix(m, M1);
    generateSpecialMatrix(m, M2);
    for(int i=0;i<m;i++) for(int j=0;j<m;j++){
        M[i][j]=M1[i][j]; M[i][j+m]=M2[i][j];
        M[i+m][j]=M2[i][j]; M[i+m][j+m]=M1[i][j];
    }
    freeMatrix(m,M1); freeMatrix(m,M2);
}

int main(){
    int sizes[] = {2,4,8,16,32,64,128,256,512,1024,2048};
    int numSizes = sizeof(sizes)/sizeof(sizes[0]);
    int trials = 20; // repeat each size a few times and average, since
                      // small n finishes in well under a microsecond

    FILE *fp = fopen("timing_data.txt", "w");
    fprintf(fp, "# n\ttime(us)\n");

    srand(time(NULL));

    for(int s = 0; s < numSizes; s++){
        int n = sizes[s];
        int **A = allocMatrix(n);
        int **B = allocMatrix(n);
        int **C = allocMatrix(n);

        generateSpecialMatrix(n, A);
        generateSpecialMatrix(n, B);

        clock_t start = clock();
        for(int t = 0; t < trials; t++)
            specialMultiply(n, A, B, C);
        clock_t end = clock();

        double avgTime = ((double)(end - start)) / CLOCKS_PER_SEC * 1e6 / trials;

        printf("n = %5d | time = %10.3f us\n", n, avgTime);
        fprintf(fp, "%d\t%.6f\n", n, avgTime);

        freeMatrix(n, A); freeMatrix(n, B); freeMatrix(n, C);
    }

    fclose(fp);
    printf("\nData written to timing_data.txt\n");
    return 0;
}