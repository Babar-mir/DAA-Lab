#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#define INF DBL_MAX

int main() {
    int n;

    printf("Enter number of keys: ");
    scanf("%d", &n);

    int *keys = (int *)malloc(n * sizeof(int));

    double *p = (double *)malloc((n + 1) * sizeof(double));
    double *q = (double *)malloc((n + 1) * sizeof(double));

    printf("Enter %d sorted keys:\n", n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &keys[i - 1]);
    }

    printf("Enter successful search probabilities p1...p%d:\n", n);

    for (int i = 1; i <= n; i++) {
        scanf("%lf", &p[i]);
    }

    printf("Enter dummy search probabilities q0...q%d:\n", n);

    for (int i = 0; i <= n; i++) {
        scanf("%lf", &q[i]);
    }

    /*
        e[i][j] = minimum expected search cost
                  for keys i through j

        w[i][j] = sum of probabilities in the subtree
    */

    double **e =
        (double **)malloc((n + 2) * sizeof(double *));

    double **w =
        (double **)malloc((n + 2) * sizeof(double *));

    int **root =
        (int **)malloc((n + 2) * sizeof(int *));

    for (int i = 0; i <= n + 1; i++) {

        e[i] = (double *)malloc((n + 2) * sizeof(double));
        w[i] = (double *)malloc((n + 2) * sizeof(double));
        root[i] = (int *)malloc((n + 2) * sizeof(int));
    }

    // Empty subtrees
    for (int i = 1; i <= n + 1; i++) {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    // Compute OBST
    for (int length = 1; length <= n; length++) {

        for (int i = 1; i <= n - length + 1; i++) {

            int j = i + length - 1;

            e[i][j] = INF;

            w[i][j] =
                w[i][j - 1] +
                p[j] +
                q[j];

            for (int r = i; r <= j; r++) {

                double cost =
                    e[i][r - 1] +
                    e[r + 1][j] +
                    w[i][j];

                if (cost < e[i][j]) {
                    e[i][j] = cost;
                    root[i][j] = r;
                }
            }
        }
    }

    printf("\nMinimum Expected Search Cost = %.4lf\n",
           e[1][n]);

    printf("Root key = %d\n",
           keys[root[1][n] - 1]);

    printf("\nRoot information for subtrees:\n");

    for (int length = 1; length <= n; length++) {

        for (int i = 1; i <= n - length + 1; i++) {

            int j = i + length - 1;

            printf("Keys %d to %d -> Root = %d\n",
                   i,
                   j,
                   keys[root[i][j] - 1]);
        }
    }

    for (int i = 0; i <= n + 1; i++) {
        free(e[i]);
        free(w[i]);
        free(root[i]);
    }

    free(e);
    free(w);
    free(root);

    free(keys);
    free(p);
    free(q);

    return 0;
}