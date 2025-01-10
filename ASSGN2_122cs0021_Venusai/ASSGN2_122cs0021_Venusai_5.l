%{
#include <stdio.h>
%}

%%
[ \t\n]+ { printf(" "); }  // Replace any sequence of whitespace characters with a single space
.       { printf("%s", yytext); }  // Copy other characters as they are
%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}