#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));
    int *dp = (int *)malloc(n * sizeof(int));

    printf("Enter array elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        dp[i] = 1;
    }

    for (int i = 1; i < n; i++) {

        for (int j = 0; j < i; j++) {

            if (arr[j] < arr[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }

    int answer = 0;

    for (int i = 0; i < n; i++) {
        answer = max(answer, dp[i]);
    }

    printf("Length of Longest Increasing Subsequence = %d\n",
           answer);

    free(arr);
    free(dp);

    return 0;
}