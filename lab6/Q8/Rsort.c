#include <stdio.h>

void reverse(int p[], int l, int r)
{
    while (l < r)
    {
        int temp = p[l];
        p[l] = p[r];
        p[r] = temp;

        l++;
        r--;
    }
}

/* Rotate two adjacent blocks:
   [first ... middle] [middle+1 ... last]
   into
   [middle+1 ... last] [first ... middle]
*/
void rotate(int p[], int first, int middle, int last)
{
    if (first > middle || middle >= last)
        return;

    reverse(p, first, middle);
    reverse(p, middle + 1, last);
    reverse(p, first, last);
}

int lowerBound(int p[], int left, int right, int value)
{
    int low = left;
    int high = right + 1;

    while (low < high)
    {
        int mid = low + (high - low) / 2;

        if (p[mid] < value)
            low = mid + 1;
        else
            high = mid;
    }

    return low;
}

int upperBound(int p[], int left, int right, int value)
{
    int low = left;
    int high = right + 1;

    while (low < high)
    {
        int mid = low + (high - low) / 2;

        if (p[mid] <= value)
            low = mid + 1;
        else
            high = mid;
    }

    return low;
}

/*
   Merge two sorted adjacent ranges:

   [left ... middle] [middle+1 ... right]
*/
void mergeReversal(int p[], int left, int middle, int right)
{
    if (left >= middle || middle >= right)
        return;

    if (p[middle] <= p[middle + 1])
        return;

    int len1 = middle - left + 1;
    int len2 = right - middle;

    int firstCut;
    int secondCut;

    /*
       Divide the larger half.
    */
    if (len1 >= len2)
    {
        firstCut = left + len1 / 2;

        secondCut =
            lowerBound(p,
                       middle + 1,
                       right,
                       p[firstCut]);

        secondCut--;
    }
    else
    {
        secondCut =
            middle + 1 + len2 / 2;

        firstCut =
            upperBound(p,
                       left,
                       middle,
                       p[secondCut]);

        firstCut--;
    }

    /*
       Blocks:

       A1 = [left ... firstCut]
       A2 = [firstCut+1 ... middle]

       B1 = [middle+1 ... secondCut]
       B2 = [secondCut+1 ... right]
    */

    int a2Start = firstCut + 1;
    int b1End = secondCut;

    if (a2Start <= middle && middle + 1 <= b1End)
    {
        rotate(p, a2Start, middle, b1End);
    }

    int newMiddle =
        firstCut + (secondCut - middle);

    mergeReversal(p,
                  left,
                  firstCut,
                  newMiddle);

    mergeReversal(p,
                  newMiddle + 1,
                  secondCut,
                  right);
}

void reversalMergeSort(int p[], int left, int right)
{
    if (left >= right)
        return;

    int middle = left + (right - left) / 2;

    reversalMergeSort(p, left, middle);

    reversalMergeSort(p, middle + 1, right);

    mergeReversal(p, left, middle, right);
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

    int p[n];

    printf("Enter permutation of 1 to %d:\n", n);

    for (int i = 0; i < n; i++)
        scanf("%d", &p[i]);

    printf("\nOriginal permutation:\n");

    for (int i = 0; i < n; i++)
        printf("%d ", p[i]);

    reversalMergeSort(p, 0, n - 1);

    printf("\n\nSorted permutation:\n");

    for (int i = 0; i < n; i++)
        printf("%d ", p[i]);

    printf("\n");

    return 0;
}