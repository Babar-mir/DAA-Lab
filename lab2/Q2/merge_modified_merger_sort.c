#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_N 1000000

/* =========================================================
   NORMAL MERGE SORT
   ========================================================= */

void merge(int a[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = a[left + i];

    for (int i = 0; i < n2; i++)
        R[i] = a[mid + 1 + i];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            a[k++] = L[i++];
        else
            a[k++] = R[j++];
    }

    while (i < n1)
        a[k++] = L[i++];

    while (j < n2)
        a[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSort(int a[], int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    mergeSort(a, left, mid);
    mergeSort(a, mid + 1, right);

    merge(a, left, mid, right);
}


/* =========================================================
   3-WAY MERGE SORT
   ========================================================= */

void merge3(int a[], int left, int mid1, int mid2, int right)
{
    int n = right - left + 1;

    int *temp = malloc(n * sizeof(int));

    int i = left;
    int j = mid1 + 1;
    int k = mid2 + 1;
    int p = 0;

    while (i <= mid1 || j <= mid2 || k <= right)
    {
        int value;
        int source;

        if (i <= mid1 &&
            (j > mid2 || a[i] <= a[j]) &&
            (k > right || a[i] <= a[k]))
        {
            value = a[i++];
            source = 1;
        }
        else if (j <= mid2 &&
                 (k > right || a[j] <= a[k]))
        {
            value = a[j++];
            source = 2;
        }
        else
        {
            value = a[k++];
            source = 3;
        }

        temp[p++] = value;
    }

    for (int x = 0; x < n; x++)
        a[left + x] = temp[x];

    free(temp);
}

void mergeSort3(int a[], int left, int right)
{
    if (left >= right)
        return;

    int n = right - left + 1;

    /*
       Divide into three approximately equal parts.
    */

    int third = n / 3;

    int mid1 = left + third - 1;
    int mid2 = left + 2 * third - 1;

    /*
       Handle small arrays where n < 3.
    */

    if (third == 0)
    {
        int mid = left + (right - left) / 2;

        mergeSort3(a, left, mid);
        mergeSort3(a, mid + 1, right);

        merge(a, left, mid, right);

        return;
    }

    mergeSort3(a, left, mid1);
    mergeSort3(a, mid1 + 1, mid2);
    mergeSort3(a, mid2 + 1, right);

    merge3(a, left, mid1, mid2, right);
}


/* =========================================================
   UTILITY FUNCTIONS
   ========================================================= */

void generateArray(int a[], int n)
{
    for (int i = 0; i < n; i++)
        a[i] = rand();
}

double measureMergeSort(int original[], int n)
{
    int *a = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        a[i] = original[i];

    clock_t start = clock();

    mergeSort(a, 0, n - 1);

    clock_t end = clock();

    free(a);

    return ((double)(end - start) / CLOCKS_PER_SEC) * 1000000.0;
}

double measureMergeSort3(int original[], int n)
{
    int *a = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        a[i] = original[i];

    clock_t start = clock();

    mergeSort3(a, 0, n - 1);

    clock_t end = clock();

    free(a);

    return ((double)(end - start) / CLOCKS_PER_SEC) * 1000000.0;
}


/* =========================================================
   MAIN
   ========================================================= */

int main()
{
    srand(42);

    int sizes[] =
    {
        1000,2000,5000,10000,20000,50000,100000,200000,500000,1000000
    };

    int count = sizeof(sizes) / sizeof(sizes[0]);

    FILE *fp = fopen("merge_comparison.dat", "w");

    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    fprintf(fp, "# n merge_sort modified_merge_sort\n");

    for (int i = 0; i < count; i++)
    {
        int n = sizes[i];

        int *a = malloc(n * sizeof(int));

        if (a == NULL)
        {
            printf("Memory allocation failed for n = %d\n", n);
            break;
        }

        generateArray(a, n);

        double normalTime = measureMergeSort(a, n);
        double modifiedTime = measureMergeSort3(a, n);

        fprintf(fp, "%d %.4f %.4f\n",
                n,
                normalTime,
                modifiedTime);

        printf("n = %d | Merge Sort = %.4f us | 3-Way Merge Sort = %.4f us\n",
               n,
               normalTime,
               modifiedTime);

        free(a);
    }

    fclose(fp);

    printf("\nData written to merge_comparison.dat\n");

    return 0;
}