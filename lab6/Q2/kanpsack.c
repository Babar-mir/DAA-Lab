#include <stdio.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int main()
{
    int n, capacity;

    printf("Enter number of items: ");
    scanf("%d", &n);

    printf("Enter knapsack capacity: ");
    scanf("%d", &capacity);

    int weight[n];
    int profit[n];

    printf("Enter weights of %d items:\n", n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &weight[i]);
    }

    printf("Enter profits of %d items:\n", n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &profit[i]);
    }

    int dp[n + 1][capacity + 1];

    /* Initialize DP table */
    for (int i = 0; i <= n; i++)
    {
        for (int w = 0; w <= capacity; w++)
        {
            dp[i][w] = 0;
        }
    }

    /* Fill DP table */
    for (int i = 1; i <= n; i++)
    {
        for (int w = 1; w <= capacity; w++)
        {
            if (weight[i - 1] <= w)
            {
                dp[i][w] = max(
                    profit[i - 1] + dp[i - 1][w - weight[i - 1]],
                    dp[i - 1][w]
                );
            }
            else
            {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    printf("\nMaximum Profit = %d\n", dp[n][capacity]);

    return 0;
}