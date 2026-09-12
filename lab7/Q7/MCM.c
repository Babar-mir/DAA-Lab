#include <stdio.h>
#include <limits.h>

#define MAX 100

long long dp[MAX][MAX];
int split[MAX][MAX];

void printOptimalParenthesis(int i, int j)
{
    if (i == j)
    {
        printf("A%d", i);
        return;
    }

    printf("(");

    printOptimalParenthesis(i, split[i][j]);

    printOptimalParenthesis(split[i][j] + 1, j);

    printf(")");
}

int main()
{
    int n;

    printf("Enter number of dimensions: ");
    scanf("%d", &n);

    if (n < 2 || n >= MAX)
    {
        printf("Invalid input.\n");
        return 0;
    }

    int p[n];

    printf("Enter %d dimensions:\n", n);

    for (int i = 0; i < n; i++)
        scanf("%d", &p[i]);

    /*
       dp[i][j] = minimum cost of multiplying
                  Ai through Aj
    */

    for (int i = 1; i < n; i++)
        dp[i][i] = 0;

    for (int length = 2; length < n; length++)
    {
        for (int i = 1; i < n - length + 1; i++)
        {
            int j = i + length - 1;

            dp[i][j] = LLONG_MAX;

            for (int k = i; k < j; k++)
            {
                long long cost =
                    dp[i][k]
                    + dp[k + 1][j]
                    + (long long)p[i - 1]
                      * p[k]
                      * p[j];

                if (cost < dp[i][j])
                {
                    dp[i][j] = cost;
                    split[i][j] = k;
                }
            }
        }
    }

    printf("\nMinimum number of scalar multiplications = %lld\n",
           dp[1][n - 1]);

    printf("Optimal ordering = ");

    printOptimalParenthesis(1, n - 1);

    printf("\n");

    return 0;
}