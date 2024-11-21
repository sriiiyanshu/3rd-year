#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

void checkLeftRecursion(char nonTerminal, char *productions) {
    char alpha[MAX], beta[MAX]; 
    int isLeftRecursive = 0;
    
    char *token = strtok(productions, "|");
    int alphaIndex = 0, betaIndex = 0;
    
    while (token != NULL) {
        if (token[0] == nonTerminal) {
            isLeftRecursive = 1;
            strcpy(&alpha[alphaIndex], token + 1);
            alphaIndex += strlen(token + 1);
            alpha[alphaIndex++] = '|';
        } else {
            strcpy(&beta[betaIndex], token);
            betaIndex += strlen(token);
            beta[betaIndex++] = '|';
        }
        token = strtok(NULL, "|");
    }
    
    if (alphaIndex > 0) alpha[alphaIndex - 1] = '\0';
    if (betaIndex > 0) beta[betaIndex - 1] = '\0';

    if (isLeftRecursive) {
        printf("Left Recursive Grammar Detected.\n");
        printf("%c -> %s%c'\n", nonTerminal, beta, nonTerminal);
        printf("%c' -> %s%c'|e\n", nonTerminal, alpha, nonTerminal);
    } else {
        printf("No Left Recursion detected.\n");
    }
}

int validateProductionRule(char *input) {
    if (strstr(input, "-->") != NULL) {
        printf("Error: '->' should not be greater than 3 characters long.\n");
        return 0;
    }

    if (!isupper(input[0]) || strncmp(input + 1, "->", 2) != 0) {
        printf("Error: Invalid production rule format.\n");
        return 0;
    }

    return 1;
}

int main() {
    char input[MAX], nonTerminal, productions[MAX];

    printf("Enter the production rule (e.g., A->Aa|b): ");
    fgets(input, MAX, stdin);
    input[strcspn(input, "\n")] = '\0'; 

    if (!validateProductionRule(input)) {
        return 0; 
    }

    nonTerminal = input[0];
    strcpy(productions, input + 3);

    checkLeftRecursion(nonTerminal, productions);

    return 0;
}
