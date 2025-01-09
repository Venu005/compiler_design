%{
#include <stdio.h>
%}

%%
[0-9]+\.[0-9]+  { printf("Floating Point Number: %s\n", yytext); }
.|\n            { /* ignore other characters */ }
%%

int main(int argc, char **argv) {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}