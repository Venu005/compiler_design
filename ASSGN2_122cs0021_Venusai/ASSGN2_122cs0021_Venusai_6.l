%{
#include <stdio.h>
#include <string.h>
%}

%%

[0|2-9]*00                    { printf("Matched: String is ending with '00'\n"); }
.*222.*                 { printf("Matched: String is having 3 consecutive '222's\n"); }

.*[0-9]*5[0-9]*5[0-9]*[0-9]*[0-9]*[0-9]*.*  { printf("Matched: Block of 5 symbols with atleast 2 '5's\n"); }

1([01]*000|[01]*010|[01]*0*0)  { printf("Matched: Binary string which is starting with '1' and divisible by 5\n"); }

.{9}1.*                        { printf("Matched: 10th symbol from the right is '1'\n"); }

[0-9][0-9][0-9][0-9]           { 
    int sum = (yytext[0] - '0') + (yytext[1] - '0') + (yytext[2] - '0') + (yytext[3] - '0');
    if (sum == 9) {
        printf("Matched: 4-digit number whose sum is 9\n");
    }
    if (yytext[0] <= yytext[1] && yytext[1] <= yytext[2] && yytext[2] <= yytext[3]) {
        printf("Matched: 4-digit number with digits in ascending order\n");
    }
}

.|\n                           { /* Ignore other characters */ }

%%

int main() {
    printf("Enter input (press Ctrl+D to end): ");
    yylex();  // Process input until EOF
    return 0;
}

int yywrap() {
    return 1;
}