#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_RULE_LENGTH 20

// Function to check if the grammar is operator precedent
bool is_operator_precedent(char *rule) {
    bool has_non_terminal = false;

    // Iterate over each character in the production rule
    for (int j = 0; j < strlen(rule); j++) {
        if (rule[j] >= 'A' && rule[j] <= 'Z') { // Check for non-terminals
            if (has_non_terminal) {
                // Found two consecutive non-terminals
                return false;
            }
            has_non_terminal = true; // Set flag for non-terminal found
        } else if (rule[j] >= 'a' && rule[j] <= 'z') { // Check for terminals
            has_non_terminal = false; // Reset the flag for the next character
        } else if (rule[j] == 'e') { // Epsilon check
            return false; // Epsilon is not allowed
        }
    }
    return true; // The grammar is operator precedent
}

int main() {
    char production[MAX_RULE_LENGTH];

    // Input for the production rule
    printf("Enter a single production rule (e.g., S-->AB|a): ");
    fgets(production, sizeof(production), stdin);
    production[strcspn(production, "\n")] = '\0'; // Remove newline character

    // Check if the grammar is operator precedent
    if (is_operator_precedent(production)) {
        printf("Operator precedent grammar\n");
    } else {
        printf("Not operator precedent grammar\n");
    }

    return 0;
}
