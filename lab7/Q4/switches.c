#include <stdio.h>

long long minimumMoves(int n)
{
    if (n == 1)
        return 1;

    if (n == 2)
        return 2;

    long long moves = 2;

    for (int i = 3; i <= n; i++)
    {
        if (i % 2 == 1)
            moves = 2 * moves + 1;
        else
            moves = 2 * moves;
    }

    return moves;
}

int main()
{
    int n;

    printf("Enter number of switches: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid number of switches.\n");
        return 0;
    }

    printf("\nMinimum number of moves = %lld\n",
           minimumMoves(n));

    return 0;
}