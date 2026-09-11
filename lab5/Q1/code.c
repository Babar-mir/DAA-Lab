#include <stdio.h>
#include <stdlib.h>

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

int quickSelect(int arr[], int low, int high, int k)
{
    if (low == high)
        return arr[low];

    int pivotIndex = partition(arr, low, high);

    int position = pivotIndex - low + 1;

    if (k == position)
        return arr[pivotIndex];

    if (k < position)
        return quickSelect(arr, low, pivotIndex - 1, k);

    return quickSelect(arr, pivotIndex + 1, high, k - position);
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid number of elements.\n");
        return 0;
    }

    int arr[n];

    printf("Enter %d elements:\n", n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    if (n % 2 != 0)
    {
        int k = n / 2 + 1;

        int median = quickSelect(arr, 0, n - 1, k);

        printf("Median = %d\n", median);
    }
    else
    {
        int k1 = n / 2;
        int k2 = n / 2 + 1;

        int median1 = quickSelect(arr, 0, n - 1, k1);
        int median2 = quickSelect(arr, 0, n - 1, k2);

        double median = (median1 + median2) / 2.0;

        printf("Median = %.2lf\n", median);
    }

    return 0;
}