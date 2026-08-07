#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RANGE 2000000   /* numbers are generated in [0, RANGE) */

void generateUniqueArray(int arr[], int n)
{
    int *pool = (int *)malloc(sizeof(int) * RANGE);
    for (int i = 0; i < RANGE; i++) pool[i] = i;

    for (int i = 0; i < n; i++) {
        int j = i + rand() % (RANGE - i);
        int t = pool[i]; pool[i] = pool[j]; pool[j] = t;
        arr[i] = pool[i];
    }
    free(pool);
}

void copyArray(const int src[], int dst[], int n)
{
    for (int i = 0; i < n; i++) dst[i] = src[i];
}

/* ---------- Method 1: brute force ---------- */
int bruteForceHasDuplicate(const int arr[], int n, long long *comparisons)
{
    long long cmp = 0;
    int found = 0;
    for (int i = 0; i < n - 1 && !found; i++) {
        for (int j = i + 1; j < n; j++) {
            cmp++;
            if (arr[i] == arr[j]) { found = 1; break; }
        }
    }
    *comparisons = cmp;
    return found;
}

/* ---------- Method 2: sort + adjacent scan ---------- */
int intCompare(const void *a, const void *b)
{
    return (*(const int *)a - *(const int *)b);
}

int sortBasedHasDuplicate(int arr[], int n)
{
    qsort(arr, n, sizeof(int), intCompare);
    for (int i = 0; i < n - 1; i++)
        if (arr[i] == arr[i + 1]) return 1;
    return 0;
}

/* ---------- Method 3: hashing / presence array ---------- */
int hashBasedHasDuplicate(const int arr[], int n)
{
    unsigned char *seen = (unsigned char *)calloc(RANGE, sizeof(unsigned char));
    if (!seen) { printf("Allocation failed.\n"); exit(1); }

    int found = 0;
    for (int i = 0; i < n; i++) {
        if (seen[arr[i]]) { found = 1; break; }
        seen[arr[i]] = 1;
    }
    free(seen);
    return found;
}

int main(void)
{
    srand((unsigned int)time(NULL));

    FILE *fp = fopen("duplicate_analysis.csv", "w");
    if (!fp) { printf("Could not open CSV file for writing.\n"); return 1; }
    fprintf(fp, "n,BruteForceComparisons,BruteForceTimeSec,SortTimeSec,HashTimeSec\n");


    printf(" Q6: Element Uniqueness - Brute Force vs Sort vs Hashing\n");

    printf("%-8s %-16s %-12s %-12s %-12s\n",
           "n", "BruteCmps", "Brute(s)", "Sort(s)", "Hash(s)");
    printf("--------------------------------------------------------\n");

    int sizes[] = {500, 1000, 2000, 4000, 8000, 16000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int s = 0; s < numSizes; s++) {
        int n = sizes[s];
        int *original = (int *)malloc(sizeof(int) * n);
        int *a = (int *)malloc(sizeof(int) * n);
        int *b = (int *)malloc(sizeof(int) * n);

        generateUniqueArray(original, n);   /* no duplicates: true worst case for brute force */

        long long bruteCmp;
        clock_t t0 = clock();
        bruteForceHasDuplicate(original, n, &bruteCmp);
        double bruteTime = (double)(clock() - t0) / CLOCKS_PER_SEC;

        copyArray(original, a, n);
        t0 = clock();
        sortBasedHasDuplicate(a, n);
        double sortTime = (double)(clock() - t0) / CLOCKS_PER_SEC;

        copyArray(original, b, n);
        t0 = clock();
        hashBasedHasDuplicate(b, n);
        double hashTime = (double)(clock() - t0) / CLOCKS_PER_SEC;

        printf("%-8d %-16lld %-12.6f %-12.6f %-12.6f\n",
               n, bruteCmp, bruteTime, sortTime, hashTime);
        fprintf(fp, "%d,%lld,%.6f,%.6f,%.6f\n",
                n, bruteCmp, bruteTime, sortTime, hashTime);

        free(original); free(a); free(b);
    }

    fclose(fp);

    return 0;
}