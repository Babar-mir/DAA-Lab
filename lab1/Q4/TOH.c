#include <stdio.h>

long long moveCount = 0;

void solveHanoi(int n, char from, char aux, char to, int printMoves)
{
    if (n == 0) return;

    solveHanoi(n - 1, from, to, aux, printMoves);

    moveCount++;
    if (printMoves)
        printf("Move %-4lld: disc %d  %c -> %c\n", moveCount, n, from, to);

    solveHanoi(n - 1, aux, from, to, printMoves);
}

int main(void)
{
    int discs;


    printf(" Q4: Tower of Hanoi\n");

    printf("Enter number of discs to simulate step-by-step (try 3 or 4): ");
    if (scanf("%d", &discs) != 1 || discs < 0) {
        printf("Invalid input.\n");
        return 1;
    }

    moveCount = 0;
    solveHanoi(discs, 'A', 'B', 'C', 1);
    printf("-----------------------------------------------------\n");
    printf("Total moves for %d discs = %lld\n", discs, moveCount);

    /* Growth table: moves vs n, without printing every move */
    printf("\nGrowth of move-count with number of discs:\n");
    printf("%-8s %-15s\n", "Discs", "TotalMoves");
    printf("---------------------------\n");

    FILE *fp = fopen("tower_of_hanoi.csv", "w");
    if (!fp) { printf("Could not open CSV file for writing.\n"); return 1; }
    fprintf(fp, "Discs,TotalMoves\n");

    for (int n = 1; n <= 25; n++) {
        long long moves = (1LL << n) - 1;   /* closed form: 2^n - 1 */
        printf("%-8d %-15lld\n", n, moves);
        fprintf(fp, "%d,%lld\n", n, moves);
    }
    fclose(fp);
    return 0;
}