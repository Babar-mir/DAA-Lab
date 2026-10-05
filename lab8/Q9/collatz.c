#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef unsigned long long ull;

ull nextCollatz(ull n) {

    if (n % 2 == 0) {
        return n / 2;
    }

    // Check overflow before calculating 3n + 1
    if (n > (ULLONG_MAX - 1) / 3) {
        return 0;
    }

    return 3 * n + 1;
}


void analyzeTrajectory(ull start) {

    ull n = start;
    ull steps = 0;
    ull maxValue = start;

    printf("\nTrajectory for %llu:\n", start);

    while (n != 1) {

        printf("%llu", n);

        ull next = nextCollatz(n);

        if (next == 0) {
            printf(" -> OVERFLOW\n");
            return;
        }

        n = next;

        if (n > maxValue)
            maxValue = n;

        steps++;

        printf(" -> ");
    }

    printf("1\n");

    printf("Starting value : %llu\n", start);
    printf("Total steps    : %llu\n", steps);
    printf("Maximum value  : %llu\n", maxValue);
}


void analyzeInterval(ull a, ull b) {

    ull largestSteps = 0;
    ull stepNumber = 0;

    ull numberWithLargestSteps = a;

    ull largestValue = 0;
    ull numberWithLargestValue = a;

    printf("\n========== Interval Analysis ==========\n");

    for (ull start = a; start <= b; start++) {

        ull n = start;
        ull steps = 0;
        ull maxValue = start;

        while (n != 1) {

            ull next = nextCollatz(n);

            if (next == 0) {
                printf("Overflow encountered for %llu\n",
                       start);
                break;
            }

            n = next;
            steps++;

            if (n > maxValue)
                maxValue = n;
        }

        printf("n = %llu | steps = %llu | max = %llu\n",
               start,
               steps,
               maxValue);

        if (steps > largestSteps) {
            largestSteps = steps;
            numberWithLargestSteps = start;
        }

        if (maxValue > largestValue) {
            largestValue = maxValue;
            numberWithLargestValue = start;
        }

        /*
            Prevent unsigned integer overflow
            when start == ULLONG_MAX.
        */
        if (start == ULLONG_MAX)
            break;
    }

    printf("\n========== Summary ==========\n");

    printf("Number with largest trajectory length : %llu\n",
           numberWithLargestSteps);

    printf("Largest number of steps              : %llu\n",
           largestSteps);

    printf("Number producing largest value        : %llu\n",
           numberWithLargestValue);

    printf("Largest value reached                 : %llu\n",
           largestValue);
}

int main() {

    int choice;

    printf("========== COLLATZ ANALYSIS ==========\n");

    printf("1. Analyze a single starting value\n");
    printf("2. Analyze an interval [a, b]\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {

        ull n;

        printf("Enter starting value n (> 0): ");
        scanf("%llu", &n);

        if (n == 0) {
            printf("Starting value must be positive.\n");
            return 1;
        }

        analyzeTrajectory(n);
    }

    else if (choice == 2) {

        ull a, b;

        printf("Enter interval start a: ");
        scanf("%llu", &a);

        printf("Enter interval end b: ");
        scanf("%llu", &b);

        if (a == 0 || b == 0 || a > b) {
            printf("Invalid interval.\n");
            return 1;
        }

        analyzeInterval(a, b);
    }

    else {
        printf("Invalid choice.\n");
    }

    return 0;
}