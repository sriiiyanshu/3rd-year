#include <stdio.h>
#include <string.h>
#include <ctype.h>

// List of 32 C keywords
const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", 
    "double", "else", "enum", "extern", "float", "for", "goto", "if", 
    "int", "long", "register", "return", "short", "signed", "sizeof", 
    "static", "struct", "switch", "typedef", "union", "unsigned", "void", 
    "volatile", "while"
};
#define NUM_KEYWORDS (sizeof(keywords) / sizeof(keywords[0]))

int is_keyword(const char *word) {
    for (int i = 0; i < NUM_KEYWORDS; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    FILE *file;
    char filename[] = "input.txt";
    char buffer[1000]; 
    int keyword_count[NUM_KEYWORDS] = {0}; 

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return 1;
    }

    printf("Content of %s:\n", filename);
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);

        // Process the current line for keywords
        char *token = strtok(buffer, " \t\n.,;(){}[]<>+-/*&|^%=!~");
        while (token != NULL) {
            // Check if the token is a keyword
            if (is_keyword(token)) {
                for (int i = 0; i < NUM_KEYWORDS; i++) {
                    if (strcmp(token, keywords[i]) == 0) {
                        keyword_count[i]++;
                        break;
                    }
                }
            }
            token = strtok(NULL, " \t\n.,;(){}[]<>+-/*&|^%=!~");
        }
    }

    fclose(file);

    printf("\n\nKeyword frequencies:\n");
    for (int i = 0; i < NUM_KEYWORDS; i++) {
        if (keyword_count[i] > 0) {
            printf("%s: %d\n", keywords[i], keyword_count[i]);
        }
    }

    return 0;
}
