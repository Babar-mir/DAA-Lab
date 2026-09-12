#include <stdio.h>
#include <stdlib.h>

void generateShots(int n, int shots[], int *count)
{
    *count = 0;

    if (n == 2)
    {
        shots[(*count)++] = 1;
        shots[(*count)++] = 1;
    }
    else if (n == 3)
    {
        shots[(*count)++] = 2;
        shots[(*count)++] = 2;
    }
    else
    {
        /* Forward sweep */
        for (int i = 2; i <= n - 1; i++)
            shots[(*count)++] = i;

        /* Backward sweep */
        for (int i = n - 1; i >= 2; i--)
            shots[(*count)++] = i;
    }
}

int main()
{
    int n;

    printf("Enter number of hiding spots: ");
    scanf("%d", &n);

    if (n <= 1)
    {
        printf("Invalid number of hiding spots.\n");
        return 0;
    }

    int maxShots = 2 * n;
    int shots[maxShots];

    int shotCount;

    generateShots(n, shots, &shotCount);

    int possible[n + 1];
    int nextPossible[n + 1];

    for (int i = 1; i <= n; i++)
        possible[i] = 1;

    int guaranteed = 0;
    int hitShot = -1;

    for (int s = 0; s < shotCount; s++)
    {
        int shot = shots[s];

        int numberPossible = 0;

        for (int i = 1; i <= n; i++)
        {
            if (possible[i])
                numberPossible++;
        }

        /*
           If the only possible position is the position
           being shot, the target is guaranteed to be hit.
        */
        if (numberPossible == 1 && possible[shot])
        {
            guaranteed = 1;
            hitShot = s + 1;
            break;
        }

        /* Assume this shot misses */
        for (int i = 1; i <= n; i++)
            nextPossible[i] = 0;

        possible[shot] = 0;

        /*
           Target moves to an adjacent position.
        */
        for (int i = 1; i <= n; i++)
        {
            if (possible[i])
            {
                if (i - 1 >= 1)
                    nextPossible[i - 1] = 1;

                if (i + 1 <= n)
                    nextPossible[i + 1] = 1;
            }
        }

        for (int i = 1; i <= n; i++)
            possible[i] = nextPossible[i];
    }

    printf("\nShooting sequence:\n");

    for (int i = 0; i < shotCount; i++)
        printf("%d ", shots[i]);

    printf("\n");

    if (guaranteed)
    {
        printf("\nThe target is guaranteed to be hit.\n");
        printf("Guaranteed hit occurs on shot %d.\n", hitShot);
    }
    else
    {
        printf("\nStrategy failed.\n");
    }

    printf("Number of shots used = %d\n", shotCount);

    return 0;
}