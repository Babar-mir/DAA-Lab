#include <stdio.h>

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
    int n, k;

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

    printf("Enter K: ");
    scanf("%d", &k);

    if (k < 1 || k > n)
    {
        printf("Invalid value of K.\n");
        return 0;
    }

    int result = quickSelect(arr, 0, n - 1, k);

    printf("The %dth smallest element is: %d\n", k, result);

    return 0;
}