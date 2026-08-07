#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* returns index of first 1, or n if the array is all 0's */
int linearFindPartition(const int arr[], int n)
{
    for (int i = 0; i < n; i++)
        if (arr[i] == 1) return i;
    return n;
}

/* returns index of first 1, or n if the array is all 0's */
int binaryFindPartition(const int arr[], int n)
{
    int lo = 0, hi = n;   /* search space [0, n]; n means "no 1 found" */
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == 1)
            hi = mid;        /* first 1 is at mid or to its left */
        else
            lo = mid + 1;    /* first 1 must be to the right of mid */
    }
    return lo;
}

void makeTestArray(int arr[], int n, int partitionIndex)
{
    for (int i = 0; i < n; i++)
        arr[i] = (i < partitionIndex) ? 0 : 1;
}

void reportResult(const char *arrLabel, int idx, int n)
{
    if (idx == n)
        printf("%s: array is all 0's (no partition point).\n", arrLabel);
    else if (idx == 0)
        printf("%s: array is all 1's, partition point = 0.\n", arrLabel);
    else
        printf("%s: partition point (first 1) at index %d.\n", arrLabel, idx);
}

int main(void)
{
    printf(" Q5: Find the Partition Point (0's then 1's)\n");

    /* --- 1. Let the user try their own array --- */
    int n;
    printf("Enter array size: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > 100000) {
        printf("Invalid size.\n");
        return 1;
    }
    int *arr = (int *)malloc(sizeof(int) * n);
    printf("Enter the %d elements (0's followed by 1's):\n", n);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    int idxLinear = linearFindPartition(arr, n);
    int idxBinary = binaryFindPartition(arr, n);
    reportResult("Linear search", idxLinear, n);
    reportResult("Binary search", idxBinary, n);
    free(arr);

    /* --- 2. Auto-generated experiment: compare #comparisons --- */

    printf("Comparison count on generated arrays (partition at n/2):\n");
    printf("%-10s %-18s %-18s\n", "Size n", "Linear (worst)", "Binary (worst)");
    printf("-----------------------------------------------------\n");

    for (n = 1000; n <= 100000; n *= 10) {
        int *big = (int *)malloc(sizeof(int) * n);
        makeTestArray(big, n, n / 2);

        /* worst case comparisons: linear = O(n), binary = O(log2 n) */
        int worstLinear = n;                 /* if partition were at the end */
        int worstBinary = 0;
        for (int size = n; size > 0; size /= 2) worstBinary++;

        printf("%-10d %-18d %-18d\n", n, worstLinear, worstBinary);
        free(big);
    }

    return 0;
}