#include <stdio.h>
#include <stdlib.h>

int mutex = 1;
int full = 0;
int empty, x = 0;

void producer() {
    --mutex;
    ++full;
    --empty;
    x++;
    printf("Producer produces item %d\n", x);
    ++mutex;
}

void consumer() {
    --mutex;
    --full;
    ++empty;
    printf("Consumer consumes item %d\n", x);
    x--;
    ++mutex;
}

void showBuffer() {
    printf("\nBuffer Status:");
    printf("\nFull slots: %d", full);
    printf("\nEmpty slots: %d", empty);
    printf("\nTotal items in buffer: %d\n", x);
}

int main() {
    int n, bufferSize;
    
    printf("Enter buffer size: ");
    scanf("%d", &bufferSize);
    
    empty = bufferSize;

    printf("\n1. Press 1 for Producer"
           "\n2. Press 2 for Consumer"
           "\n3. Press 3 for Exit"
           "\n4. Press 4 to Show Buffer Status");

    while (1) {
        printf("\nEnter your choice: ");
        scanf("%d", &n);

        switch (n) {
        case 1:
            if (mutex == 1 && empty != 0) {
                producer();
            } else {
                printf("Buffer is full!\n");
            }
            break;

        case 2:
            if (mutex == 1 && full != 0) {
                consumer();
            } else {
                printf("Buffer is empty!\n");
            }
            break;

        case 3:
            exit(0);
            break;

        case 4:
            showBuffer();
            break;

        default:
            printf("Invalid choice! Please try again.");
        }
    }
}
