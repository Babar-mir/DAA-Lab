#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int year;
    int type;
} Event;

/*
    type:
    -1 = death
    +1 = birth

    For the same year, death must come before birth.
*/
int compareEvents(const void *a, const void *b)
{
    Event *x = (Event *)a;
    Event *y = (Event *)b;

    if (x->year != y->year)
        return x->year - y->year;

    return x->type - y->type;
}

int main()
{
    int n;

    printf("Enter number of scientists: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid number of scientists.\n");
        return 0;
    }

    Event events[2 * n];

    printf("\nEnter birth year and death year for each scientist:\n");

    for (int i = 0; i < n; i++)
    {
        int birth, death;

        printf("Scientist %d: ", i + 1);
        scanf("%d %d", &birth, &death);

        if (death < birth)
        {
            printf("Invalid birth/death years.\n");
            return 0;
        }

        events[2 * i].year = birth;
        events[2 * i].type = 1;

        events[2 * i + 1].year = death;
        events[2 * i + 1].type = -1;
    }

    qsort(events, 2 * n, sizeof(Event), compareEvents);

    int alive = 0;
    int maximum = 0;
    int bestYear = 0;

    for (int i = 0; i < 2 * n; i++)
    {
        alive += events[i].type;

        if (alive > maximum)
        {
            maximum = alive;
            bestYear = events[i].year;
        }
    }

    printf("\nYear with maximum number of scientists alive = %d\n",
           bestYear);

    printf("Maximum number of scientists alive = %d\n",
           maximum);

    return 0;
}