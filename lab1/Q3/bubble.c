#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_N 2000

/* ---- input generators ---- */

void makeSorted(int arr[], int n)
{
    for (int i = 0; i < n; i++) arr[i] = i;
}

void makeReverseSorted(int arr[], int n)
{
    for (int i = 0; i < n; i++) arr[i] = n - i;
}

void makeRandom(int arr[], int n)
{
    for (int i = 0; i < n; i++) arr[i] = rand() % (n * 10 + 1);
}

/* sorted, but with a single pair swapped near the middle */
void makeNearlySorted(int arr[], int n)
{
    makeSorted(arr, n);
    if (n > 3) {
        int a = n / 2, b = a + 1;
        int t = arr[a]; arr[a] = arr[b]; arr[b] = t;
    }
}

void copyArray(const int src[], int dst[], int n)
{
    for (int i = 0; i < n; i++) dst[i] = src[i];
}

/* ---- the two bubble sort variants, each returns #comparisons ---- */

long long bubbleSortEarlyExit(int arr[], int n)
{
    long long cmp = 0;
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - i - 1; j++) {
            cmp++;
            if (arr[j] > arr[j + 1]) {
                int t = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = t;
                swapped = 1;
            }
        }
        if (!swapped) break;      /* array already sorted, stop early */
    }
    return cmp;
}

long long bubbleSortFullPasses(int arr[], int n)
{
    long long cmp = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            cmp++;
            if (arr[j] > arr[j + 1]) {
                int t = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = t;
            }
        }
        /* no early-exit check: always completes all n-1 passes */
    }
    return cmp;
}

void runCase(FILE *fp, const char *label, const int original[], int n)
{
    int a[MAX_N], b[MAX_N];
    copyArray(original, a, n);
    copyArray(original, b, n);

    long long earlyCmp = bubbleSortEarlyExit(a, n);
    long long fullCmp  = bubbleSortFullPasses(b, n);

    printf("%-14s %-8d %-16lld %-16lld\n", label, n, earlyCmp, fullCmp);
    fprintf(fp, "%s,%d,%lld,%lld\n", label, n, earlyCmp, fullCmp);
}

int main(void)
{
    srand((unsigned int)time(NULL));

    FILE *fp = fopen("bubble_sort_analysis.csv", "w");
    if (!fp) { printf("Could not open CSV file for writing.\n"); return 1; }
    fprintf(fp, "InputType,ArraySize,EarlyExitComparisons,FullPassComparisons\n");


    printf(" Q3: Bubble Sort - Early Exit vs Always-Full-Passes\n");

    printf("%-14s %-8s %-16s %-16s\n", "InputType", "n", "EarlyExit", "FullPasses");
    printf("----------------------------------------------------------------\n");

    int arr[MAX_N];
    for (int n = 100; n <= 1000; n += 100) {
        makeSorted(arr, n);        runCase(fp, "Sorted", arr, n);
        makeNearlySorted(arr, n);  runCase(fp, "NearlySorted", arr, n);
        makeRandom(arr, n);        runCase(fp, "Random", arr, n);
        makeReverseSorted(arr, n); runCase(fp, "Reverse", arr, n);
        printf("----------------------------------------------------------------\n");
    }

    fclose(fp);

    return 0;
}