#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    int n, V;

    printf("Enter number of coin denominations: ");
    scanf("%d", &n);

    int *coins = (int *)malloc(n * sizeof(int));

    printf("Enter coin denominations:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &coins[i]);
    }

    printf("Enter target amount: ");
    scanf("%d", &V);

    int *dp = (int *)malloc((V + 1) * sizeof(int));

    dp[0] = 0;

    for (int i = 1; i <= V; i++) {
        dp[i] = INF;
    }

    for (int amount = 1; amount <= V; amount++) {
        for (int i = 0; i < n; i++) {
            if (coins[i] <= amount && dp[amount - coins[i]] != INF) {
                dp[amount] = min(dp[amount],
                                 dp[amount - coins[i]] + 1);
            }
        }
    }

    if (dp[V] == INF)
        printf("Minimum number of coins = -1\n");
    else
        printf("Minimum number of coins = %d\n", dp[V]);

    free(coins);
    free(dp);

    return 0;
}