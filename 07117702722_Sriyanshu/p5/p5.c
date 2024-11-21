#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

void longestCommonPrefix(char* result, char* str1, char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0' && str1[i] == str2[i]) {
        result[i] = str1[i];
        i++;
    }
    result[i] = '\0'; 
}

void checkLeftFactoring(char nonTerminal, char *productions) {
    char commonPrefix[MAX] = {0}, tempPrefix[MAX] = {0};
    char factoredPart[MAX] = {0};
    char remainingParts[MAX][MAX]; 
    int hasLeftFactoring = 0;
    int partCount = 0;

    char *token = strtok(productions, "|");

    strcpy(factoredPart, token);
    token = strtok(NULL, "|");

    while (token != NULL) {
        longestCommonPrefix(tempPrefix, factoredPart, token);

        if (strlen(tempPrefix) > 0) {
            hasLeftFactoring = 1;
            strcpy(commonPrefix, tempPrefix); 
            strcpy(remainingParts[partCount++], factoredPart + strlen(commonPrefix)); 
            strcpy(remainingParts[partCount++], token + strlen(commonPrefix));        
        }
        factoredPart[0] = '\0'; 
        token = strtok(NULL, "|");
    }

   
    if (hasLeftFactoring) {
        printf("Left Factoring Grammar Detected.\n");
        
        printf("%c -> %s%c'\n", nonTerminal, commonPrefix, nonTerminal);
        printf("%c' -> ", nonTerminal);
        for (int i = 0; i < partCount; i++) {
            if (strlen(remainingParts[i]) == 0) {
                printf("e");  
            } else {
                printf("%s", remainingParts[i]);
            }
            if (i < partCount - 1) {
                printf(" | ");
            }
        }
        printf("\n");
    } else {
        printf("No Left Factoring detected.\n");
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

    printf("Enter the production rule (e.g., A->ab|ac|d): ");
    fgets(input, MAX, stdin);
    input[strcspn(input, "\n")] = '\0';

    if (!validateProductionRule(input)) {
        return 0; 
    }

    nonTerminal = input[0];
    strcpy(productions, input + 3);

    checkLeftFactoring(nonTerminal, productions);

    return 0;
}
