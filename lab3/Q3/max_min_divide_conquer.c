#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int min;
    int max;
} Result;

long long comparisons = 0;

/* Divide-and-conquer function. */
Result maxMinDC(const int a[], int n)
{
    Result result;

    if (n == 1)
    {
        result.min = a[0];
        result.max = a[0];
        return result;
    }

    if (n == 2)
    {
        comparisons++;

        if (a[0] < a[1])
        {
            result.min = a[0];
            result.max = a[1];
        }
        else
        {
            result.min = a[1];
            result.max = a[0];
        }

        return result;
    }

    int mid = n / 2;

    Result left = maxMinDC(a, mid);
    Result right = maxMinDC(a + mid, n - mid);

    comparisons++;

    result.max = (left.max > right.max)
               ? left.max
               : right.max;

    comparisons++;

    result.min = (left.min < right.min)
               ? left.min
               : right.min;

    return result;
}
Result maxMinPairwise(const int a[], int n)
{
    if (n == 1)
    {
        Result r = {a[0], a[0]};
        return r;
    }

    if (n == 2)
    {
        Result r;

        comparisons++;

        if (a[0] < a[1])
        {
            r.min = a[0];
            r.max = a[1];
        }
        else
        {
            r.min = a[1];
            r.max = a[0];
        }

        return r;
    }

    int pairs = n / 2;

    int *larger = malloc(pairs * sizeof(int));
    int *smaller = malloc(pairs * sizeof(int));

    if (larger == NULL || smaller == NULL)
    {
        free(larger);
        free(smaller);

        Result error = {0, 0};
        return error;
    }

    for (int i = 0; i < pairs; i++)
    {
        int x = a[2 * i];
        int y = a[2 * i + 1];

        comparisons++;

        if (x > y)
        {
            larger[i] = x;
            smaller[i] = y;
        }
        else
        {
            larger[i] = y;
            smaller[i] = x;
        }
    }

    Result maxResult = maxMinPairwise(larger, pairs);
    Result minResult = maxMinPairwise(smaller, pairs);

    Result result;

    result.max = maxResult.max;
    result.min = minResult.min;

    if (n % 2 != 0)
    {
        int last = a[n - 1];

        comparisons++;
        if (last > result.max)
            result.max = last;

        comparisons++;
        if (last < result.min)
            result.min = last;
    }

    free(larger);
    free(smaller);

    return result;
}

void test(int a[], int n)
{
    comparisons = 0;

    Result r = maxMinDC(a, n);

    printf("n = %d\n", n);
    printf("Minimum = %d\n", r.min);
    printf("Maximum = %d\n", r.max);
    printf("Comparisons = %lld\n", comparisons);
    printf("3n/2 = %.1f\n", 1.5 * n);

    if (comparisons <= (3LL * n) / 2)
        printf("Bound satisfied: YES\n");
    else
        printf("Bound satisfied: NO\n");

    printf("\n");
}

int main(void)
{
    int n1;
    printf("enter the nuber of elements of first array; ");
    scanf("%d",&n1);
    int a1[n1];
    for(int i=0;i<n1;i++){
        scanf("%d",&a1[i]);
    }
    int n2;
    printf("enter the nuber of elements of first array; ");
    scanf("%d",&n2);
    int a2[n2];
    for(int i=0;i<n2;i++){
        scanf("%d",&a2[i]);
    }

    test(a1, n1);
    test(a2, n2);

    /*
     * Generate data for experimental validation.
     */
    FILE *fp = fopen("max_min_comparisons.dat", "w");

    if (fp == NULL)
    {
        printf("Could not create max_min_comparisons.dat\n");
        return 1;
    }

    fprintf(fp, "# n comparisons theoretical_3n_over_2\n");

    for (int n = 2; n <= 1024; n *= 2)
    {
        int *a = malloc(n * sizeof(int));

        if (a == NULL)
            break;

        for (int i = 0; i < n; i++)
            a[i] = (i * 37) % (n * 10);

        comparisons = 0;

        Result r = maxMinDC(a, n);

        (void)r;

        fprintf(fp, "%d %lld %.1f\n",
                n,
                comparisons,
                1.5 * n);

        free(a);
    }

    fclose(fp);

    printf("Data written to max_min_comparisons.dat\n");

    return 0;
}
