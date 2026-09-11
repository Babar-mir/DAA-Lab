#include <stdio.h>
#include <limits.h>

int min(int a, int b)
{
    return (a < b) ? a : b;
}

int main()
{
    int n;

    printf("Enter N: ");
    scanf("%d", &n);

    if (n < 2)
    {
        printf("Invalid input.\n");
        return 0;
    }

    int arr[n];

    printf("Enter %d dimensions:\n", n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    /*
       dp[i][j] = minimum number of scalar multiplications
                  required to multiply matrices i through j
    */

    int dp[n][n];

    for (int i = 1; i < n; i++)
    {
        dp[i][i] = 0;
    }

    /* Chain length */
    for (int length = 2; length < n; length++)
    {
        for (int i = 1; i < n - length + 1; i++)
        {
            int j = i + length - 1;

            dp[i][j] = INT_MAX;

            for (int k = i; k < j; k++)
            {
                int cost = dp[i][k]
                         + dp[k + 1][j]
                         + arr[i - 1] * arr[k] * arr[j];

                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }

    printf("\nMinimum number of scalar multiplications = %d\n",
           dp[1][n - 1]);

    return 0;
}