#include <stdio.h>
#include <limits.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int main()
{
    int eggs, floors;

    printf("Enter number of eggs: ");
    scanf("%d", &eggs);

    printf("Enter number of floors: ");
    scanf("%d", &floors);

    if (eggs <= 0 || floors < 0)
    {
        printf("Invalid input.\n");
        return 0;
    }

    int dp[eggs + 1][floors + 1];


    for (int e = 0; e <= eggs; e++)
        dp[e][0] = 0;

    if (floors >= 1)
    {
        for (int e = 1; e <= eggs; e++)
            dp[e][1] = 1;
    }

    for (int f = 1; f <= floors; f++)
        dp[1][f] = f;

    for (int e = 2; e <= eggs; e++)
    {
        for (int f = 2; f <= floors; f++)
        {
            dp[e][f] = INT_MAX;

            for (int x = 1; x <= f; x++)
            {
                int trials = 1 + max(
                    dp[e - 1][x - 1],
                    dp[e][f - x]
                );

                if (trials < dp[e][f])
                    dp[e][f] = trials;
            }
        }
    }

    printf("\nMinimum number of droppings required = %d\n",
           dp[eggs][floors]);

    return 0;
}