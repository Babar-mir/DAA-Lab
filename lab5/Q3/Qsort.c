#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);

    return i + 1;
}

int randomizedPartition(int arr[], int low, int high)
{
    int randomIndex = low + rand() % (high - low + 1);

    swap(&arr[randomIndex], &arr[high]);

    return partition(arr, low, high);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pivot = randomizedPartition(arr, low, high);

        quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }
}

int main()
{
    int n;
    char inputFile[100];
    char outputFile[100];

    printf("Enter number of random elements: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid number of elements.\n");
        return 0;
    }

    printf("Enter input file name: ");
    scanf("%s", inputFile);

    printf("Enter output file name: ");
    scanf("%s", outputFile);

    int arr[n];

    srand(time(NULL));

    /* Generate random numbers */
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 1000;
    }

    /* Store random elements in input file */
    FILE *fp = fopen(inputFile, "w");

    if (fp == NULL)
    {
        printf("Error opening input file.\n");
        return 0;
    }

    for (int i = 0; i < n; i++)
    {
        fprintf(fp, "%d ", arr[i]);
    }

    fclose(fp);

    /* Read elements from file */
    fp = fopen(inputFile, "r");

    if (fp == NULL)
    {
        printf("Error reading input file.\n");
        return 0;
    }

    for (int i = 0; i < n; i++)
    {
        fscanf(fp, "%d", &arr[i]);
    }

    fclose(fp);

    printf("\nRandom elements:\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    /* Quick Sort */
    quickSort(arr, 0, n - 1);

    printf("\n\nSorted elements:\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    /* Store sorted elements */
    fp = fopen(outputFile, "w");

    if (fp == NULL)
    {
        printf("\nError opening output file.\n");
        return 0;
    }

    for (int i = 0; i < n; i++)
    {
        fprintf(fp, "%d ", arr[i]);
    }

    fclose(fp);

    printf("\n\nSorted elements stored in %s\n", outputFile);

    return 0;
}