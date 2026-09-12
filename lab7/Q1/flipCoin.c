#include <stdio.h>

long long minimumMoves(int n)
{
    long long totalCoins = (long long)n * (n + 1) / 6;

    return totalCoins ;
}

int main()
{
    int n;

    printf("Enter number of rows in the coin triangle: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid number of rows.\n");
        return 0;
    }

    long long totalCoins = (long long)n * (n + 1) / 2;
    long long moves = minimumMoves(n);

    printf("\nTotal number of coins = %lld\n", totalCoins);
    printf("Minimum number of moves = %lld\n", moves);

    return 0;
}