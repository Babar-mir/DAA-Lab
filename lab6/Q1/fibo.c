#include <stdio.h>
#include <stdlib.h>

long long fibonacci(int n)
{
    if (n == 0)
        return 0;

    if (n == 1)
        return 1;

    long long dp[n + 1];

    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i <= n; i++)
    {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    return dp[n];
}

int main()
{
    int n;

    printf("Enter the value of n: ");
    scanf("%d", &n);

    if (n < 0)
    {
        printf("Invalid input.\n");
        return 0;
    }

    printf("The %dth Fibonacci number is: %lld\n",
           n, fibonacci(n));

    return 0;
}