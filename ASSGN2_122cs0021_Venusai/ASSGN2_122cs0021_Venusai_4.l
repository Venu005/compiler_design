%{
#include <stdio.h>
#include <string.h>

int keywords = 0, identifiers = 0, constants = 0, operators = 0, punctuations = 0, totalTokens = 0;

int isKeyword(char *word) {
    const char *keywordList[] = {"int", "float", "if", "else", "for", "while", "return", "void", "char", NULL};
    for (int i = 0; keywordList[i] != NULL; i++) {
        if (strcmp(word, keywordList[i]) == 0)
            return 1;
    }
    return 0;
}
%}

%%

[ \t\n]                     { /* Ignore whitespace */ }
[a-zA-Z_][a-zA-Z0-9_]*      { 
                            if (isKeyword(yytext)) {
                                keywords++;
                            } else {
                                identifiers++;
                            }
                            totalTokens++;
                          }
[0-9]+                      { constants++; totalTokens++; }
"+"|"-"|"*"|"/"|"%"         { operators++; totalTokens++; }
"(" | ")" | "{" | "}" | ";" | "," { punctuations++; totalTokens++; }
.                           { /* Catch all for unrecognized characters */ }

%%

int main() {
    printf("Enter a statement: ");
    yylex();
    printf("Number of Keywords: %d\n", keywords);
    printf("Number of Constants: %d\n", constants);
    printf("Number of Identifiers: %d\n", identifiers);
    printf("Number of Operators: %d\n", operators);
    printf("Number of Punctuations: %d\n", punctuations);
    printf("Total Number of Tokens are: %d\n", totalTokens);
    return 0;
}

int yywrap() {
    return 1;
}
