#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int arr[], int n, int i)
{
    int largest = i;

    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
    {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest])
    {
        largest = right;
    }

    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);

        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n)
{
    /* Build Max Heap */
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }

    /* Extract elements from heap */
    for (int i = n - 1; i > 0; i--)
    {
        swap(&arr[0], &arr[i]);

        heapify(arr, i, 0);
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

    /* Generate random elements */
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 1000;
    }

    /* Store elements in input file */
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

    /* Heap Sort */
    heapSort(arr, n);

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