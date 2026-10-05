#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int n;

    printf("Enter rod length: ");
    scanf("%d", &n);

    int *price = (int *)malloc((n + 1) * sizeof(int));
    int *dp = (int *)malloc((n + 1) * sizeof(int));
    int *cut = (int *)malloc((n + 1) * sizeof(int));

    price[0] = 0;

    printf("Enter prices for pieces of length 1 to %d:\n", n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &price[i]);
    }

    dp[0] = 0;

    for (int length = 1; length <= n; length++) {

        dp[length] = price[length];
        cut[length] = length;

        for (int firstCut = 1;
             firstCut < length;
             firstCut++) {

            if (price[firstCut] +
                dp[length - firstCut] > dp[length]) {

                dp[length] =
                    price[firstCut] +
                    dp[length - firstCut];

                cut[length] = firstCut;
            }
        }
    }

    printf("\nMaximum Revenue = %d\n", dp[n]);

    printf("Optimal pieces: ");

    int remaining = n;

    while (remaining > 0) {

        printf("%d ", cut[remaining]);

        remaining -= cut[remaining];
    }

    printf("\n");

    free(price);
    free(dp);
    free(cut);

    return 0;
}