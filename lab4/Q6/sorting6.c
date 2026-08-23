#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int position;
    int type;       // +1 = left endpoint, -1 = right endpoint
} Event;

/* Sort events according to position */
int compare(const void *a, const void *b) {

    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;

    return e1->position - e2->position;
}

int main() {

    int n;

    printf("Enter number of intervals: ");
    scanf("%d", &n);

    Event events[2 * n];

    printf("Enter the intervals:\n");

    for (int i = 0; i < n; i++) {

        int left, right;

        scanf("%d %d", &left, &right);

        events[2 * i].position = left;
        events[2 * i].type = 1;

        events[2 * i + 1].position = right;
        events[2 * i + 1].type = -1;
    }

    /* Sort all endpoints */
    qsort(events, 2 * n, sizeof(Event), compare);

    int current = 0;
    int maximum = 0;
    int bestPoint = 0;

    for (int i = 0; i < 2 * n; i++) {

        if (events[i].type == 1) {

            /* Interval starts */
            current++;

            if (current > maximum) {
                maximum = current;
                bestPoint = events[i].position;
            }
        }
        else {

            /*
             * Since the endpoint itself belongs to the interval,
             * check the current count before removing the interval.
             */
            if (current > maximum) {
                maximum = current;
                bestPoint = events[i].position;
            }

            /* Interval ends */
            current--;
        }
    }

    printf("\nPoint with maximum overlap: %d\n", bestPoint);
    printf("Maximum number of intervals containing the point: %d\n",
           maximum);

    return 0;
}