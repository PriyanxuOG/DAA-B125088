#include <stdio.h>
#include <string.h>

struct Item {
    int number;
    char colour[10];
};

int main() {
    int n;
    
    printf("Enter number of items: ");
    scanf("%d", &n);

    struct Item items[n];

    printf("Enter number and colour (red/blue/yellow) for each item:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %9s", &items[i].number, items[i].colour);
    }

    printf("\nSorted items:\n");

    for (int i = 0; i < n; i++) {
        if (strcmp(items[i].colour, "red") == 0) {
            printf("%d red\n", items[i].number);
        }
    }
    for (int i = 0; i < n; i++) {
        if (strcmp(items[i].colour, "blue") == 0) {
            printf("%d blue\n", items[i].number);
        }
    }

    for (int i = 0; i < n; i++) {
        if (strcmp(items[i].colour, "yellow") == 0) {
            printf("%d yellow\n", items[i].number);
        }
    }

    return 0;
}
