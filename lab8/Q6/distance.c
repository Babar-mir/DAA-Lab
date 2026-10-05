#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min3(int a, int b, int c) {
    int result = a;

    if (b < result)
        result = b;

    if (c < result)
        result = c;

    return result;
}

int main() {
    char A[1000], B[1000];

    printf("Enter source string: ");
    scanf("%s", A);

    printf("Enter target string: ");
    scanf("%s", B);

    int m = strlen(A);
    int n = strlen(B);

    int **dp = (int **)malloc((m + 1) * sizeof(int *));

    for (int i = 0; i <= m; i++) {
        dp[i] = (int *)malloc((n + 1) * sizeof(int));
    }

    // Initialization
    for (int i = 0; i <= m; i++)
        dp[i][0] = i;

    for (int j = 0; j <= n; j++)
        dp[0][j] = j;

    // DP table
    for (int i = 1; i <= m; i++) {

        for (int j = 1; j <= n; j++) {

            if (A[i - 1] == B[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else {
                dp[i][j] = 1 + min3(
                    dp[i - 1][j],     // deletion
                    dp[i][j - 1],     // insertion
                    dp[i - 1][j - 1]  // substitution
                );
            }
        }
    }

    printf("\nMinimum Edit Distance = %d\n", dp[m][n]);

    // Store traceback operations
    char **operations =
        (char **)malloc((m + n + 1) * sizeof(char *));

    int count = 0;

    int i = m;
    int j = n;

    while (i > 0 || j > 0) {

        if (i > 0 && j > 0 &&
            A[i - 1] == B[j - 1] &&
            dp[i][j] == dp[i - 1][j - 1]) {

            operations[count] = (char *)malloc(100 * sizeof(char));

            sprintf(operations[count],
                    "Keep '%c'",
                    A[i - 1]);

            count++;

            i--;
            j--;
        }

        else if (i > 0 && j > 0 &&
                 dp[i][j] == dp[i - 1][j - 1] + 1) {

            operations[count] = (char *)malloc(100 * sizeof(char));

            sprintf(operations[count],
                    "Substitute '%c' -> '%c'",
                    A[i - 1],
                    B[j - 1]);

            count++;

            i--;
            j--;
        }

        else if (i > 0 &&
                 dp[i][j] == dp[i - 1][j] + 1) {

            operations[count] = (char *)malloc(100 * sizeof(char));

            sprintf(operations[count],
                    "Delete '%c'",
                    A[i - 1]);

            count++;

            i--;
        }

        else {

            operations[count] = (char *)malloc(100 * sizeof(char));

            sprintf(operations[count],
                    "Insert '%c'",
                    B[j - 1]);

            count++;

            j--;
        }
    }

    printf("\nTraceback:\n");

    // Reverse operations because traceback starts at the end
    for (int k = count - 1; k >= 0; k--) {
        printf("%s\n", operations[k]);
        free(operations[k]);
    }

    free(operations);

    for (i = 0; i <= m; i++) {
        free(dp[i]);
    }

    free(dp);

    return 0;
}