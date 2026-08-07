#include <stdio.h>
#include <string.h>
#include <math.h>

#define NUM_FUNCS 12

typedef struct {
    char  name[24];
    double log10val;   /* log10 of the function's value at a given n */
} FuncEntry;

/* log10 of each function, evaluated at a given n (n given as double) */
void evaluateAll(FuncEntry list[], double n)
{
    double log10n  = log10(n);
    double log2n   = log2(n);
    double log10_2 = log10(2.0);
    double log10_3 = log10(3.0);

    strcpy(list[0].name, "1/n");
    list[0].log10val = -log10n;

    strcpy(list[1].name, "log2(n)");
    list[1].log10val = log10(log2n);

    strcpy(list[2].name, "12*sqrt(n)");
    list[2].log10val = log10(12.0) + 0.5 * log10n;

    strcpy(list[3].name, "50*n^0.5");
    list[3].log10val = log10(50.0) + 0.5 * log10n;

    strcpy(list[4].name, "n^0.51");
    list[4].log10val = 0.51 * log10n;

    strcpy(list[5].name, "n*log2(n)");
    list[5].log10val = log10n + log10(log2n);

    strcpy(list[6].name, "n^log2(n)");
    list[6].log10val = log2n * log10n;

    strcpy(list[7].name, "2^32 * n");
    list[7].log10val = 32.0 * log10_2 + log10n;

    strcpy(list[8].name, "100n^2+6n");
    list[8].log10val = log10(100.0 * n * n + 6.0 * n);

    strcpy(list[9].name, "n^2-324");
    /* n^2-324 is negative for n < 18ish; log10 is undefined there.
     * Clamp to a very small placeholder so it still sorts correctly
     * (it genuinely is tiny/negative for small n). */
    double n2minus = n * n - 324.0;
    list[9].log10val = (n2minus > 0) ? log10(n2minus) : -100.0;

    strcpy(list[10].name, "2n^3");
    list[10].log10val = log10(2.0) + 3.0 * log10n;

    strcpy(list[11].name, "3^n");
    list[11].log10val = n * log10_3;
}

/* simple insertion sort - fine for 12 elements */
void sortByGrowth(FuncEntry list[])
{
    for (int i = 1; i < NUM_FUNCS; i++) {
        FuncEntry key = list[i];
        int j = i - 1;
        while (j >= 0 && list[j].log10val > key.log10val) {
            list[j + 1] = list[j];
            j--;
        }
        list[j + 1] = key;
    }
}

void printRanking(double n)
{
    FuncEntry list[NUM_FUNCS];
    evaluateAll(list, n);
    sortByGrowth(list);

    printf("\n----- Ranking at n = %.0f -----\n", n);
    for (int i = 0; i < NUM_FUNCS; i++)
        printf("%2d. %-14s (log10 value = %.3f)\n",
               i + 1, list[i].name, list[i].log10val);
}

int main(void)
{
    double testValues[] = { 10, 100, 1000, 1e4, 1e5, 1e6, 1e7, 1e8 };
    int numTests = sizeof(testValues) / sizeof(testValues[0]);


    printf(" Q1: Increasing order of growth (log10-scale ranking)\n");
    printf("======================================================\n");

    for (int i = 0; i < numTests; i++)
        printRanking(testValues[i]);

    printf("\n------------------------------------------------------\n");
    printf("Theoretical order (n -> infinity), ignoring constants:\n");
    printf("------------------------------------------------------\n");
    printf(" 1/n  <  log2(n)  <  12*sqrt(n) ~ 50*n^0.5  <  n^0.51\n");
    printf(" <  2^32*n  <  n*log2(n)  <  n^2-324 ~ 100n^2+6n\n");
    printf(" <  2n^3  <  n^log2(n)  <  3^n\n");

    return 0;
}