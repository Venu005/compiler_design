#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINES 100
#define MAX_TOKEN_LENGTH 100
#define MAX_KEYWORDS 5
#define MAX_OPERATORS 5
#define MAX_PUNCTUATIONS 6
#define MAX_IDENTIFIERS 100
#define MAX_CONSTANTS 100
#define MAX_TOKENS 200

// Define sets of keywords, operators, and punctuations
const char *keywords[MAX_KEYWORDS] = {"int", "float", "return", "if", "else"};
const char operators[MAX_OPERATORS] = {'+', '-', '*', '/', '%'};
const char punctuations[MAX_PUNCTUATIONS] = {';', ',', '{', '}', '(', ')'};
  
// Function to check if a string is a number
int isNumber(const char *str) {
    int decimalPoint = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (isdigit(str[i])) continue;
        if (str[i] == '.' && !decimalPoint) {
            decimalPoint = 1;
        } else {
            return 0;  // Not a number
        }
    }
    return 1;  // It's a number
}

// Function to check if a string is an identifier
int isIdentifier(const char *str) {
    if (str[0] == '\0' || isdigit(str[0])) return 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalnum(str[i]) && str[i] != '_') return 0;
    }
    return 1;
}

// Function to check if a string is a keyword
int isKeyword(const char *str) {
    for (int i = 0; i < MAX_KEYWORDS; i++) {
        if (strcmp(str, keywords[i]) == 0) return 1;
    }
    return 0;
}

// Function to check if a character is an operator
int isOperator(char ch) {
    for (int i = 0; i < MAX_OPERATORS; i++) {
        if (ch == operators[i]) return 1;
    }
    return 0;
}

// Function to check if a character is punctuation
int isPunctuation(char ch) {
    for (int i = 0; i < MAX_PUNCTUATIONS; i++) {
        if (ch == punctuations[i]) return 1;
    }
    return 0;
}

// Function to analyze code
void analyzeCode(char lines[MAX_LINES][MAX_TOKEN_LENGTH], int numLines) {
    int keywordCount = 0, operatorCount = 0, constantCount = 0, punctuationCount = 0, identifierCount = 0, tokenCount = 0;
    char keywordTokens[MAX_TOKENS][MAX_TOKEN_LENGTH];
    char constantTokens[MAX_TOKENS][MAX_TOKEN_LENGTH];
    char identifierTokens[MAX_TOKENS][MAX_TOKEN_LENGTH];
    char punctuationTokens[MAX_TOKENS][MAX_TOKEN_LENGTH];
    
    for (int i = 0; i < numLines; i++) {
        int j = 0;
        while (lines[i][j] != '\0') {
            // Skip whitespace
            if (isspace(lines[i][j])) {
                j++;
                continue;
            }

            // Extract token
            char token[MAX_TOKEN_LENGTH] = {0};
            int k = 0;
            while (lines[i][j] != '\0' && !isspace(lines[i][j]) && !isOperator(lines[i][j]) && !isPunctuation(lines[i][j])) {
                token[k++] = lines[i][j++];
            }
            
            // Check for keywords
            if (strlen(token) > 0 && isKeyword(token)) {
                keywordCount++;
                strcpy(keywordTokens[keywordCount - 1], token);
            } 
            // Check for numbers (constants)
            else if (strlen(token) > 0 && isNumber(token)) {
                constantCount++;
                strcpy(constantTokens[constantCount - 1], token);
            } 
            // Check for identifiers
            else if (strlen(token) > 0 && isIdentifier(token)) {
                identifierCount++;
                strcpy(identifierTokens[identifierCount - 1], token);
            }

            // Handle operators and punctuations
            if (lines[i][j] != '\0' && isOperator(lines[i][j])) {
                operatorCount++;
                j++;
            } 
            else if (lines[i][j] != '\0' && isPunctuation(lines[i][j])) {
                punctuationCount++;
                punctuationTokens[punctuationCount - 1][0] = lines[i][j];
                j++;
            }
            
            if (strlen(token) > 0) {
                tokenCount++;
            }
        }
    }

    // Output the results
    printf("Keywords: %d (", keywordCount);
    for (int i = 0; i < keywordCount; i++) {
        printf("%s%s", keywordTokens[i], (i < keywordCount - 1) ? " " : "");
    }
    printf(")\n");

    printf("Operators: %d\n", operatorCount);

    printf("Constants: %d (", constantCount);
    for (int i = 0; i < constantCount; i++) {
        printf("%s%s", constantTokens[i], (i < constantCount - 1) ? " " : "");
    }
    printf(")\n");

    printf("Punctuations: %d (", punctuationCount);
    for (int i = 0; i < punctuationCount; i++) {
        printf("%c%s", punctuationTokens[i][0], (i < punctuationCount - 1) ? " " : "");
    }
    printf(")\n");

    printf("Identifiers: %d (", identifierCount);
    for (int i = 0; i < identifierCount; i++) {
        printf("%s%s", identifierTokens[i], (i < identifierCount - 1) ? " " : "");
    }
    printf(")\n");

    printf("Tokens: %d\n", tokenCount + operatorCount + punctuationCount);
}

int main() {
    int numLines;
    printf("Enter number of lines: ");
    scanf("%d", &numLines);
    getchar();  // Clear the newline character from the input buffer

    char lines[MAX_LINES][MAX_TOKEN_LENGTH];
    printf("Enter the code:\n");
    for (int i = 0; i < numLines; i++) {
        fgets(lines[i], MAX_TOKEN_LENGTH, stdin);
        lines[i][strcspn(lines[i], "\n")] = '\0';  // Remove newline character if present
    }

    printf("\nLexical Analysis Output:\n");
    analyzeCode(lines, numLines);

    return 0;
}
