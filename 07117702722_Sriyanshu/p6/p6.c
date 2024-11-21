#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_NON_TERMINALS 10
#define MAX_PRODUCTIONS 10
#define MAX_SYMBOLS 10

typedef struct {
    char non_terminal;
    char production[MAX_SYMBOLS][MAX_SYMBOLS];
    int count;
} Production;

Production productions[MAX_PRODUCTIONS];
char first[MAX_NON_TERMINALS][MAX_SYMBOLS];
int production_count = 0, non_terminal_count = 0;

void addProduction(char non_terminal, char *prod) {
    int i;
    for (i = 0; i < production_count; i++) {
        if (productions[i].non_terminal == non_terminal) {
            strcpy(productions[i].production[productions[i].count++], prod);
            return;
        }
    }
    productions[production_count].non_terminal = non_terminal;
    strcpy(productions[production_count].production[productions[production_count].count++], prod);
    production_count++;
}

int findNonTerminalIndex(char non_terminal) {
    for (int i = 0; i < non_terminal_count; i++) {
        if (first[i][0] == non_terminal)
            return i;
    }
    first[non_terminal_count++][0] = non_terminal;
    return non_terminal_count - 1;
}

int addToFirst(int index, char symbol) {
    for (int i = 1; first[index][i] != '\0'; i++) {
        if (first[index][i] == symbol)
            return 0;  // Symbol already exists, no change
    }
    int i = 1;
    while (first[index][i] != '\0') i++;
    first[index][i] = symbol;
    first[index][i + 1] = '\0';
    return 1;  // New symbol added
}

int computeFirstForProduction(int index, char *prod) {
    int addedEpsilon = 0;
    for (int k = 0; prod[k] != '\0'; k++) {
        if (islower(prod[k]) || prod[k] == 'e') {
            return addToFirst(index, prod[k]);
        } else {
            int nextIndex = findNonTerminalIndex(prod[k]);
            int containsEpsilon = 0;
            for (int l = 1; first[nextIndex][l] != '\0'; l++) {
                if (first[nextIndex][l] == 'e')
                    containsEpsilon = 1;
                else
                    addedEpsilon |= addToFirst(index, first[nextIndex][l]);
            }
            if (!containsEpsilon)
                return addedEpsilon;
            addedEpsilon = 1;
        }
    }
    return addedEpsilon;
}

void computeFirst() {
    int changes;
    do {
        changes = 0;
        for (int i = 0; i < production_count; i++) {
            int index = findNonTerminalIndex(productions[i].non_terminal);
            for (int j = 0; j < productions[i].count; j++) {
                changes |= computeFirstForProduction(index, productions[i].production[j]);
            }
        }
    } while (changes);
}

void displayFirstSets() {
    printf("\nFIRST sets of non-terminals:\n");
    for (int i = 0; i < non_terminal_count; i++) {
        printf("FIRST(%c) = { ", first[i][0]);
        for (int j = 1; first[i][j] != '\0'; j++) {
            printf("%c ", first[i][j]);
        }
        printf("}\n");
    }
}

int main() {
    int n;
    printf("Enter the number of productions: ");
    scanf("%d", &n);
    getchar();

    printf("Enter productions (e.g., A-->aB|e):\n");
    for (int i = 0; i < n; i++) {
        char line[100], *token;
        fgets(line, sizeof(line), stdin);
        line[strcspn(line, "\n")] = '\0';

        token = strtok(line, "-->");
        char non_terminal = token[0];

        token = strtok(NULL, "-->");
        char *production = strtok(token, "|");

        while (production) {
            addProduction(non_terminal, production);
            production = strtok(NULL, "|");
        }
    }

    computeFirst();
    displayFirstSets();

    return 0;
}
