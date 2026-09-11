#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sortArray(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
        }
    }
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid size.\n");
        return 0;
    }

    int arr[n];

    printf("Enter %d elements:\n", n);

    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    /* (i) Maximum */
    int max = arr[0];

    for (int i = 1; i < n; i++)
    {
        if (arr[i] > max)
            max = arr[i];
    }

    printf("\n(i) Maximum element = %d\n", max);

    /* (ii) First and second largest */
    int largest = arr[0];
    int secondLargest = -2147483648;

    for (int i = 1; i < n; i++)
    {
        if (arr[i] > largest)
        {
            secondLargest = largest;
            largest = arr[i];
        }
        else if (arr[i] > secondLargest && arr[i] != largest)
        {
            secondLargest = arr[i];
        }
    }

    printf("(ii) First largest = %d\n", largest);

    if (secondLargest == -2147483648)
        printf("     Second largest does not exist.\n");
    else
        printf("     Second largest = %d\n", secondLargest);

    /* (iii) Mean */
    double sum = 0;

    for (int i = 0; i < n; i++)
        sum += arr[i];

    double mean = sum / n;

    printf("(iii) Mean = %.2lf\n", mean);

    /* (iv) Median */
    int temp[n];

    for (int i = 0; i < n; i++)
        temp[i] = arr[i];

    sortArray(temp, n);

    double median;

    if (n % 2 == 0)
        median = (temp[n / 2 - 1] + temp[n / 2]) / 2.0;
    else
        median = temp[n / 2];

    printf("(iv) Median = %.2lf\n", median);

    /* (v) Standard deviation */
    double variance = 0;

    for (int i = 0; i < n; i++)
    {
        variance += (arr[i] - mean) * (arr[i] - mean);
    }

    variance /= n;

    double standardDeviation = sqrt(variance);

    printf("(v) Standard deviation = %.2lf\n", standardDeviation);

    /* (vi) Mode */
    int mode = arr[0];
    int maxFrequency = 1;

    for (int i = 0; i < n; i++)
    {
        int frequency = 1;

        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] == arr[j])
                frequency++;
        }

        if (frequency > maxFrequency)
        {
            maxFrequency = frequency;
            mode = arr[i];
        }
    }

    if (maxFrequency == 1)
        printf("(vi) Mode = No mode\n");
    else
        printf("(vi) Mode = %d\n", mode);

    /* (vii) Remove duplicates */
    int unique[n];
    int uniqueCount = 0;

    for (int i = 0; i < n; i++)
    {
        int found = 0;

        for (int j = 0; j < uniqueCount; j++)
        {
            if (arr[i] == unique[j])
            {
                found = 1;
                break;
            }
        }

        if (!found)
        {
            unique[uniqueCount] = arr[i];
            uniqueCount++;
        }
    }

    printf("(vii) Array after removing duplicates:\n");

    for (int i = 0; i < uniqueCount; i++)
        printf("%d ", unique[i]);

    printf("\n");

    /* (viii) Reverse */
    printf("(viii) Reversed array:\n");

    for (int i = n - 1; i >= 0; i--)
        printf("%d ", arr[i]);

    printf("\n");

    /* (ix) Partition with respect to pivot */
    int pivot;

    printf("(ix) Enter pivot element: ");
    scanf("%d", &pivot);

    int partitioned[n];
    int index = 0;

    /*
       Elements less than pivot first,
       followed by elements >= pivot.
    */

    for (int i = 0; i < n; i++)
    {
        if (arr[i] < pivot)
            partitioned[index++] = arr[i];
    }

    for (int i = 0; i < n; i++)
    {
        if (arr[i] >= pivot)
            partitioned[index++] = arr[i];
    }

    printf("Partitioned array:\n");

    for (int i = 0; i < n; i++)
        printf("%d ", partitioned[i]);

    printf("\n");

    return 0;
}