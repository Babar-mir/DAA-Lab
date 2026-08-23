#include <stdio.h>

typedef struct {
    int number;
    char colour;
} Item;

int main() {
    int n;

    printf("Enter number of items: ");
    scanf("%d", &n);

    Item red[n], blue[n], yellow[n];
    int r = 0, b = 0, y = 0;

    printf("Enter number and colour (R/B/Y):\n");

    for (int i = 0; i < n; i++) {
        Item item;
        scanf("%d  %c", &item.number, &item.colour);

        if (item.colour == 'R' || item.colour == 'r') {
            red[r++] = item;
        }
        else if (item.colour == 'B' || item.colour == 'b') {
            blue[b++] = item;
        }
        else if (item.colour == 'Y' || item.colour == 'y') {
            yellow[y++] = item;
        }
        else {
            printf("Invalid colour!\n");
            return 1;
        }
    }

    printf("\nSorted by colour:\n");

    // Print all Reds
    for (int i = 0; i < r; i++) {
        printf("(%d, %c) ", red[i].number, red[i].colour);
    }

    // Print all Blues
    for (int i = 0; i < b; i++) {
        printf("(%d, %c) ", blue[i].number, blue[i].colour);
    }

    // Print all Yellows
    for (int i = 0; i < y; i++) {
        printf("(%d, %c) ", yellow[i].number, yellow[i].colour);
    }

    printf("\n");

    return 0;
}