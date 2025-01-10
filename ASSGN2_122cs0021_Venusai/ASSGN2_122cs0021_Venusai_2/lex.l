%{
#include "y.tab.h"
%}

%%

[0-9]+      { yylval = atoi(yytext); return NUMBER; }
[ \t]       { /* ignore whitespace */ }
"("         { return LPAREN; }
")"         { return RPAREN; }
"+"         { return PLUS; }
"-"         { return MINUS; }
"*"         { return MULTIPLY; }
"/"         { return DIVIDE; }

%%

int yywrap() {
    return 1;
}