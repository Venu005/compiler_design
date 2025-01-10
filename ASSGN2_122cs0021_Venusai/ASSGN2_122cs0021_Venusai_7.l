%{
#include <stdio.h>
#include <ctype.h>
%}

%%

^[aeiouAEIOU][a-zA-Z]*         { printf("%say ", yytext); }

^[^aeiouAEIOU][a-zA-Z]*        { printf("%s%cay ", yytext+1, yytext[0]); }

[^a-zA-Z]+                     { printf("%s", yytext); }

[ \t\n]*                       { printf("%s", yytext); }

%%

int main() {
    printf("Enter text (press Ctrl+D to end):\n");
    yylex();  
    return 0;
}

int yywrap() {
    return 1;
}