#include <stdio.h>
#include <stdlib.h>

void selectionSort(int A[], int n, long long *comparisons)
{
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;

        for (int j = i + 1; j < n; j++)
        {
            (*comparisons)++;

            if (A[j] < A[minIndex])
                minIndex = j;
        }

        if (minIndex != i)
        {
            int temp = A[i];
            A[i] = A[minIndex];
            A[minIndex] = temp;
        }
    }
}

void printArray(int A[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);

    printf("\n");
}

int main()
{
    int n;

    printf("Enter n: ");
    scanf("%d", &n);

    int *A = malloc(n * sizeof(int));

    if (A == NULL)
        return 1;

    printf("Enter elements:\n");

    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    long long comparisons = 0;

    selectionSort(A, n, &comparisons);

    printf("\nSorted array:\n");
    printArray(A, n);

    printf("\nNumber of comparisons = %lld\n",
           comparisons);

    printf("Theoretical comparisons = %lld\n",
           (long long)n * (n - 1) / 2);

    free(A);

    return 0;
}