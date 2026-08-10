#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_K 128
#define MAX_N 10000

/* ---------------------------------------------------------
   Merge two sorted arrays.
   Result must have enough space for n1 + n2 elements.
   --------------------------------------------------------- */
void merge_two(const int *a, int n1,
               const int *b, int n2,
               int *result)
{
    int i = 0, j = 0, p = 0;

    while (i < n1 && j < n2)
    {
        if (a[i] <= b[j])
            result[p++] = a[i++];
        else
            result[p++] = b[j++];
    }

    while (i < n1)
        result[p++] = a[i++];

    while (j < n2)
        result[p++] = b[j++];
}

/* ---------------------------------------------------------
   Create k sorted arrays, each with n elements.

   Each array contains non-overlapping increasing values.
   They are individually sorted, but the arrays are not
   globally sorted relative to one another.
   --------------------------------------------------------- */
int **create_sorted_arrays(int k, int n)
{
    int **arrays = malloc(k * sizeof(int *));

    if (arrays == NULL)
        return NULL;

    for (int i = 0; i < k; i++)
    {
        arrays[i] = malloc(n * sizeof(int));

        if (arrays[i] == NULL)
        {
            for (int j = 0; j < i; j++)
                free(arrays[j]);

            free(arrays);
            return NULL;
        }

        /*
            Make every individual array sorted.
            The starting value is shifted so arrays are not
            already globally ordered.
        */
        int start = (k - i) * (n + 10);

        for (int j = 0; j < n; j++)
            arrays[i][j] = start + 2 * j;
    }

    return arrays;
}

void free_sorted_arrays(int **arrays, int k)
{
    for (int i = 0; i < k; i++)
        free(arrays[i]);

    free(arrays);
}

/* ---------------------------------------------------------
   METHOD 1
   Sequential merging.

   Start with A1.
   Merge A1+A2.
   Merge result with A3.
   Continue until Ak.
   --------------------------------------------------------- */
int *method1(int **arrays, int k, int n)
{
    int current_size = n;

    int *current = malloc(n * sizeof(int));
    if (current == NULL)
        return NULL;

    for (int i = 0; i < n; i++)
        current[i] = arrays[0][i];

    for (int i = 1; i < k; i++)
    {
        int new_size = current_size + n;

        int *next = malloc(new_size * sizeof(int));
        if (next == NULL)
        {
            free(current);
            return NULL;
        }

        merge_two(current, current_size,
                  arrays[i], n,
                  next);

        free(current);
        current = next;
        current_size = new_size;
    }

    return current;
}

/* ---------------------------------------------------------
   Generic Method 2 implementation with explicit sizes.
   --------------------------------------------------------- */
int *method2_generic(int **arrays, int k, int n)
{
    int count = k;

    int **current = malloc(k * sizeof(int *));
    int *sizes = malloc(k * sizeof(int));

    if (current == NULL || sizes == NULL)
    {
        free(current);
        free(sizes);
        return NULL;
    }

    for (int i = 0; i < k; i++)
    {
        current[i] = arrays[i];
        sizes[i] = n;
    }

    while (count > 1)
    {
        int new_count = (count + 1) / 2;

        int **next = malloc(new_count * sizeof(int *));
        int *new_sizes = malloc(new_count * sizeof(int));

        if (next == NULL || new_sizes == NULL)
        {
            free(next);
            free(new_sizes);
            free(current);
            free(sizes);
            return NULL;
        }

        int p = 0;

        for (int i = 0; i + 1 < count; i += 2)
        {
            int new_size = sizes[i] + sizes[i + 1];

            next[p] = malloc(new_size * sizeof(int));

            if (next[p] == NULL)
            {
                for (int j = 0; j < p; j++)
                    free(next[j]);

                free(next);
                free(new_sizes);
                free(current);
                free(sizes);
                return NULL;
            }

            merge_two(current[i], sizes[i],
                      current[i + 1], sizes[i + 1],
                      next[p]);

            /*
                current[i] and current[i+1] are newly allocated
                results from previous rounds, except during the
                first round where they point to input arrays.
            */
            if (sizes[i] != n || sizes[i + 1] != n)
            {
                /*
                    A pointer belongs to a previous merge round.
                    Free it only if it is not one of the original
                    input arrays.
                */
            }

            new_sizes[p] = new_size;
            p++;
        }

        /* Carry an unpaired array to the next round. */
        if (count % 2 != 0)
        {
            next[p] = current[count - 1];
            new_sizes[p] = sizes[count - 1];
            p++;
        }

        /*
            Free all previous-round merged arrays.
            Original input arrays have size exactly n and are
            preserved. However, a merged array can also have
            size n only when it is an original array, so this
            condition is sufficient for this program.
        */
        for (int i = 0; i < count; i++)
        {
            if (sizes[i] != n)
                free(current[i]);
        }

        free(current);
        free(sizes);

        current = next;
        sizes = new_sizes;
        count = new_count;
    }

    int *result = current[0];

    free(current);
    free(sizes);

    return result;
}

/* ---------------------------------------------------------
   Generate arrays.
   --------------------------------------------------------- */
int **generate_input(int k, int n)
{
    int **arrays = malloc(k * sizeof(int *));

    if (arrays == NULL)
        return NULL;

    for (int i = 0; i < k; i++)
    {
        arrays[i] = malloc(n * sizeof(int));

        if (arrays[i] == NULL)
        {
            for (int j = 0; j < i; j++)
                free(arrays[j]);

            free(arrays);
            return NULL;
        }

        /*
            Interleaved ranges make each array sorted while
            ensuring that elements from different arrays overlap.
        */
        for (int j = 0; j < n; j++)
            arrays[i][j] = j * k + i;
    }

    return arrays;
}

/* ---------------------------------------------------------
   Benchmark Method 1.
   --------------------------------------------------------- */
double benchmark_method1(int k, int n, int repetitions)
{
    double total = 0.0;

    for (int r = 0; r < repetitions; r++)
    {
        int **arrays = generate_input(k, n);

        if (arrays == NULL)
            return -1.0;

        clock_t start = clock();

        int *result = method1(arrays, k, n);

        clock_t end = clock();

        if (result == NULL)
        {
            free_sorted_arrays(arrays, k);
            return -1.0;
        }

        total += (double)(end - start) / CLOCKS_PER_SEC;

        free(result);
        free_sorted_arrays(arrays, k);
    }

    return (total / repetitions) * 1000000.0;
}

/* ---------------------------------------------------------
   Benchmark Method 2.
   --------------------------------------------------------- */
double benchmark_method2(int k, int n, int repetitions)
{
    double total = 0.0;

    for (int r = 0; r < repetitions; r++)
    {
        int **arrays = generate_input(k, n);

        if (arrays == NULL)
            return -1.0;

        clock_t start = clock();

        int *result = method2_generic(arrays, k, n);

        clock_t end = clock();

        if (result == NULL)
        {
            free_sorted_arrays(arrays, k);
            return -1.0;
        }

        total += (double)(end - start) / CLOCKS_PER_SEC;

        free(result);
        free_sorted_arrays(arrays, k);
    }

    return (total / repetitions) * 1000000.0;
}

/* ---------------------------------------------------------
   Verify correctness.
   --------------------------------------------------------- */
int is_sorted(int *a, int size)
{
    for (int i = 1; i < size; i++)
    {
        if (a[i - 1] > a[i])
            return 0;
    }

    return 1;
}

void correctness_test(void)
{
    int k = 4;
    int n = 5;

    int **arrays = generate_input(k, n);

    int *r1 = method1(arrays, k, n);
    int *r2 = method2_generic(arrays, k, n);

    printf("\nCorrectness test:\n");
    printf("Method 1 sorted: %s\n",
           is_sorted(r1, k * n) ? "YES" : "NO");

    printf("Method 2 sorted: %s\n",
           is_sorted(r2, k * n) ? "YES" : "NO");

    printf("Result: ");

    for (int i = 0; i < k * n; i++)
        printf("%d ", r1[i]);

    printf("\n");

    free(r1);
    free(r2);
    free_sorted_arrays(arrays, k);
}

/* ---------------------------------------------------------
   Main benchmark.
   --------------------------------------------------------- */
int main(void)
{
    /*
        Keep n fixed and vary k to experimentally observe:

        Method 1:  O(n k^2)
        Method 2:  O(n k log k)
    */

    const int n = 1000;

    /*
        Powers of two are convenient for Method 2:
        k/2 -> k/4 -> ... -> 1
    */
    int k_values[] = {
        2, 4, 8, 16, 32, 64, 128
    };

    int number_of_values =
        sizeof(k_values) / sizeof(k_values[0]);

    const int repetitions = 3;

    FILE *fp = fopen("q3_comparison.dat", "w");

    if (fp == NULL)
    {
        printf("Error opening q3_comparison.dat\n");
        return 1;
    }

    correctness_test();

    fprintf(fp,
            "# k method1_us method2_us\n");

    printf("\nBenchmark:\n");
    printf("n = %d\n\n", n);

    for (int i = 0; i < number_of_values; i++)
    {
        int k = k_values[i];

        double t1 = benchmark_method1(
            k, n, repetitions);

        double t2 = benchmark_method2(
            k, n, repetitions);

        if (t1 < 0 || t2 < 0)
        {
            printf("Memory allocation failed at k = %d\n", k);
            break;
        }

        fprintf(fp,
                "%d %.4f %.4f\n",
                k, t1, t2);

        printf(
            "k = %d | Method 1 = %.4f us | Method 2 = %.4f us\n",
            k, t1, t2);
    }

    fclose(fp);

    printf("\nData written to q3_comparison.dat\n");

    return 0;
}
