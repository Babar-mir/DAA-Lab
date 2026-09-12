#include <stdio.h>

#define MAX 50

long long dp[MAX];
int split[MAX];

void hanoi3(int n, char source, char destination, char auxiliary)
{
    if (n == 0)
        return;

    hanoi3(n - 1, source, auxiliary, destination);

    printf("Move disk %d from %c to %c\n",
           n, source, destination);

    hanoi3(n - 1, auxiliary, destination, source);
}

void hanoi4(int n,
            char source,
            char destination,
            char auxiliary1,
            char auxiliary2)
{
    if (n == 0)
        return;

    if (n == 1)
    {
        printf("Move disk 1 from %c to %c\n",
               source, destination);
        return;
    }

    int k = split[n];

    /* Move n-k smaller disks using four pegs */
    hanoi4(n - k,
           source,
           auxiliary1,
           destination,
           auxiliary2);

    /* Move k larger disks using three pegs */
    hanoi3(k,
           source,
           destination,
           auxiliary2);

    /* Move n-k smaller disks to destination */
    hanoi4(n - k,
           auxiliary1,
           destination,
           source,
           auxiliary2);
}

int main()
{
    int n;

    printf("Enter number of disks: ");
    scanf("%d", &n);

    if (n <= 0 || n >= MAX)
    {
        printf("Invalid number of disks.\n");
        return 0;
    }

    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i <= n; i++)
    {
        dp[i] = 9223372036854775807LL;

        for (int k = 1; k < i; k++)
        {
            long long threePegMoves =
                (1LL << k) - 1;

            long long moves =
                2 * dp[i - k] + threePegMoves;

            if (moves < dp[i])
            {
                dp[i] = moves;
                split[i] = k;
            }
        }
    }

    printf("\nMinimum number of moves = %lld\n", dp[n]);

    if (n <= 10)
    {
        printf("\nSequence of moves:\n");

        hanoi4(n, 'A', 'D', 'B', 'C');
    }
    else
    {
        printf("\nMove sequence not displayed because it becomes very large.\n");
    }

    return 0;
}