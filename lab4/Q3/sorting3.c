#include <stdio.h>
#include <stdlib.h>

int n, k, T;
int arr[100];
int selected[100];

/* Compare function for qsort */
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

/* Binary search in the given range */
int binarySearch(int arr[], int left, int right, int key) {

    while (left <= right) {

        int mid = left + (right - left) / 2;

        if (arr[mid] == key) {
            return mid;
        }
        else if (arr[mid] < key) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return -1;
}

/*
   Select k-1 elements.
   At the last level, binary search for the required kth element.
*/
int findKSum(int start, int count, int sum) {

    /* If k-1 elements have been selected */
    if (count == k - 1) {

        int required = T - sum;

        /*
           Search only after start.
           This ensures that the same element is not used twice.
        */
        int index = binarySearch(arr, start, n - 1, required);

        if (index != -1) {

            selected[count] = arr[index];

            printf("\nCombination found:\n");

            for (int i = 0; i < k; i++) {
                printf("%d ", selected[i]);
            }

            printf("\n");

            return 1;
        }

        return 0;
    }

    /*
       Select the next element.
       We move forward so that no element is selected twice.
    */
    for (int i = start; i < n; i++) {

        selected[count] = arr[i];

        if (findKSum(i + 1, count + 1, sum + arr[i])) {
            return 1;
        }
    }

    return 0;
}

int main() {

    printf("Enter the size of set: ");
    scanf("%d", &n);

    printf("Enter the elements of set:\n");

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter the value of k: ");
    scanf("%d", &k);

    printf("Enter the target T: ");
    scanf("%d", &T);

    if (k <= 0 || k > n) {
        printf("Invalid value of k.\n");
        return 0;
    }

    /* Sort the input array */
    qsort(arr, n, sizeof(int), compare);

    if (!findKSum(0, 0, 0)) {
        printf("\nNo combination of %d elements adds up to %d.\n", k, T);
    }

    return 0;
}