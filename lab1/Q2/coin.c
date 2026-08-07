#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Returns 1 for HEAD, 0 for TAIL.
 * headProbability = 0.5  -> fair coin
 * headProbability != 0.5 -> biased coin                        */
int tossCoin(double headProbability)
{
    double r = (double)rand() / (double)RAND_MAX;
    return (r < headProbability) ? 1 : 0;
}

/* Runs `tosses` simulations at the given bias and returns the
 * fraction that came up HEAD.                                  */
double estimateHeadProbability(int tosses, double headProbability)
{
    int heads = 0;
    for (int i = 0; i < tosses; i++)
        heads += tossCoin(headProbability);
    return (double)heads / tosses;
}

int main(void)
{
    srand((unsigned int)time(NULL));

    int trialSizes[] = {50, 200, 1000, 5000, 20000, 100000, 500000};
    int numTrials = sizeof(trialSizes) / sizeof(trialSizes[0]);
    double biasedProb = 0.65;   /* biased coin's true HEAD probability */

    FILE *fp = fopen("coin_simulation.csv", "w");
    if (!fp) { printf("Could not open CSV file for writing.\n"); return 1; }
    fprintf(fp, "Tosses,FairEstimate,BiasedEstimate\n");


    printf(" Q2: Fair Coin vs Biased Coin (true bias = %.2f)\n", biasedProb);

    printf("%-10s %-16s %-16s\n", "Tosses", "Fair P(HEAD)", "Biased P(HEAD)");
    printf("-----------------------------------------------------\n");

    for (int i = 0; i < numTrials; i++) {
        int n = trialSizes[i];
        double fairEst   = estimateHeadProbability(n, 0.5);
        double biasedEst = estimateHeadProbability(n, biasedProb);

        printf("%-10d %-16.5f %-16.5f\n", n, fairEst, biasedEst);
        fprintf(fp, "%d,%.5f,%.5f\n", n, fairEst, biasedEst);
    }

    fclose(fp);

    return 0;
}