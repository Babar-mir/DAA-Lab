#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int left;
    int right;
} Interval;

/* Compare intervals according to left endpoint */
int compare(const void *a, const void *b) {
    Interval *i1 = (Interval *)a;
    Interval *i2 = (Interval *)b;

    return i1->left - i2->left;
}

int main() {

    int n;

    printf("Enter number of intervals: ");
    scanf("%d", &n);

    Interval intervals[n];

    printf("Enter the intervals:\n");

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &intervals[i].left, &intervals[i].right);
    }

    /* Sort intervals by left endpoint */
    qsort(intervals, n, sizeof(Interval), compare);

    Interval merged[n];
    int count = 0;

    /* Start with the first interval */
    merged[count] = intervals[0];
    count++;

    for (int i = 1; i < n; i++) {

        /*
         * If current interval overlaps the last merged interval,
         * merge them.
         */
        if (intervals[i].left <= merged[count - 1].right) {

            if (intervals[i].right > merged[count - 1].right) {
                merged[count - 1].right = intervals[i].right;
            }
        }
        else {
            /* No overlap, create a new merged interval */
            merged[count] = intervals[i];
            count++;
        }
    }

    printf("\nMerged intervals:\n");

    for (int i = 0; i < count; i++) {
        printf("(%d, %d) ", merged[i].left, merged[i].right);
    }

    printf("\n");

    return 0;
}