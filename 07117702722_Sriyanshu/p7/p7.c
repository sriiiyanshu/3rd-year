#include <stdio.h>
#include <string.h>

struct ProductionRule {
    char left;                // Single character for the non-terminal
    char right[10];           // Right side of the production rule
};

int main() {
    char input[20], stack[50] = "", temp[50], ch[2], *substring;
    int i = 0, j, rule_count = 0, reduced;
    struct ProductionRule rules[10];

    // Input for the number of production rules
    printf("\nEnter the number of production rules: ");
    scanf("%d", &rule_count);
    getchar();  // Consume the newline

    // Input for each production rule in the specified form 'S-->AB|a'
    printf("\nEnter the production rules (in the form 'S-->AB|a'):\n");
    for (i = 0; i < rule_count; i++) {
        fgets(temp, sizeof(temp), stdin);
        temp[strcspn(temp, "\n")] = '\0'; // Remove newline at end of input

        // Parse the left and right parts of the production
        char *token1 = strtok(temp, "-->");
        char *token2 = strtok(NULL, "-->");
        rules[i].left = token1[0];  // Store left side as a single non-terminal character

        // Right side of the rule (e.g., "AB" or "a")
        if (token2 != NULL) {
            strcpy(rules[i].right, token2);
        }
    }

    // Input for the string to parse
    printf("\nEnter the input string: ");
    scanf("%s", input);

    printf("%-14s %-14s %-14s\n", "Stack", "Input", "Action");
    printf("-------------- -------------- --------------\n");

    i = 0;
    while (1) {
        // Shift: If there are more characters in the input, shift the next character to the stack
        if (i < strlen(input)) {
            ch[0] = input[i++];
            ch[1] = '\0';
            strcat(stack, ch);  // Shift operation
            printf("%-15s%-15sShift %s\n", stack, &input[i], ch);
        }

        // Attempt to apply reductions
        reduced = 0;
        for (j = 0; j < rule_count; j++) {
            int right_len = strlen(rules[j].right);
            // Check if the stack ends with the right side of the production
            if (strlen(stack) >= right_len &&
                strcmp(stack + strlen(stack) - right_len, rules[j].right) == 0) {
                // Replace the right side of the rule in the stack with the left side
                stack[strlen(stack) - right_len] = '\0';  // Remove the matched substring
                strncat(stack, &rules[j].left, 1);  // Add the left side of the rule
                printf("%-15s%-15sReduce %c-->%s\n", stack, &input[i], rules[j].left, rules[j].right);
                reduced = 1;
                break;  // After a reduction, restart the loop
            }
        }

        // Final acceptance condition
        char start_symbol[2] = { rules[0].left, '\0' };  // Convert start symbol to a string
        if (!reduced && i == strlen(input) && strcmp(stack, start_symbol) == 0) {
            printf("\nAccepted\n");
            return 0;
        }

        // If no reduction was possible and input is fully consumed, reject
        if (!reduced && i == strlen(input)) {
            printf("\nNot Accepted\n");
            return 0;
        }
    }
}
