#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 * If left is lighter -> defective coin is in left half.
 * If right is lighter -> defective coin is in right half.
 * If they balance -> there is no defective coin.
 */

typedef enum {
    BALANCE = 0,
    LEFT_LIGHTER = -1,
    RIGHT_LIGHTER = 1
} Result;

Result weigh(const double weight[], const int left[],
             const int right[], int count)
{
    double left_weight = 0.0;
    double right_weight = 0.0;

    for (int i = 0; i < count; i++)
    {
        left_weight += weight[left[i]];
        right_weight += weight[right[i]];
    }

    const double EPS = 1e-9;

    if (left_weight < right_weight - EPS)
        return LEFT_LIGHTER;

    if (right_weight < left_weight - EPS)
        return RIGHT_LIGHTER;

    return BALANCE;
}

int findDefectiveCoin(const double weight[], int n,
                      int *weighings)
{
    int size = 1;

    while (size < n)
        size *= 2;

    int *candidate = malloc(size * sizeof(int));

    if (candidate == NULL)
        return -2;

    for (int i = 0; i < size; i++)
        candidate[i] = i;

    int current = size;

    while (current > 1)
    {
        int half = current / 2;

        int *left = malloc(half * sizeof(int));
        int *right = malloc(half * sizeof(int));

        if (left == NULL || right == NULL)
        {
            free(left);
            free(right);
            free(candidate);
            return -2;
        }
        for (int i = 0; i < half; i++)
        {
            left[i] = candidate[i];
            right[i] = candidate[half + i];
        }

        Result result = weigh(weight, left, right, half);
        (*weighings)++;

        free(left);
        free(right);

        if (result == BALANCE)
        {
            /*
             * Both halves balance. Since at most one coin is
             * defective, there is no defective coin.
             */
            free(candidate);
            return -1;
        }

        if (result == LEFT_LIGHTER)
        {
            for (int i = 0; i < half; i++)
                candidate[i] = candidate[i];
        }
        else
        {
            for (int i = 0; i < half; i++)
                candidate[i] = candidate[half + i];
        }

        current = half;
    }

    int answer = candidate[0];

    free(candidate);

    if (answer >= n)
        return -1;      /* selected dummy coin => no defect */

    return answer;
}

void printResult(int answer, int weighings)
{
    if (answer == -1)
        printf("No defective coin.\n");
    else
        printf("Defective coin: %d\n", answer + 1);

    printf("Number of weighings: %d\n", weighings);
}

int main(void)
{
    /*
     * Example 1: coin 7 is lighter.
     */
    int n = 13;

    double *weight = malloc(n * sizeof(double));

    if (weight == NULL)
        return 1;

    for (int i = 0; i < n; i++)
        weight[i] = 1.0;

    weight[6] = 0.9;  /* coin 7 is defective */

    int weighings = 0;

    int answer = findDefectiveCoin(weight, n, &weighings);

    printf("Example 1:\n");
    printResult(answer, weighings);

    free(weight);

    /*
     * Example 2: no defective coin.
     */
    n = 13;

    weight = malloc(n * sizeof(double));

    if (weight == NULL)
        return 1;

    for (int i = 0; i < n; i++)
        weight[i] = 1.0;

    weighings = 0;

    answer = findDefectiveCoin(weight, n, &weighings);

    printf("\nExample 2:\n");
    printResult(answer, weighings);

    free(weight);

    return 0;
}
