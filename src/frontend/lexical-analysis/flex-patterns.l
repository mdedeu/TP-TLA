%{

#include "flex-actions.h"

%}

/* Obliga a crear una regla explícita para manejar lexemas desconocidos. */
%option nodefault

/* Escanea un único archivo y se detiene. */
%option noyywrap

/* Dispone una variable global "yylineno" con el número de línea actual. */
%option yylineno

/* Patrones reutilizables. */
crlf			\r\n
digit			[0-9]
endline			\n
whitespace		[ \f\n\r\t\v]

%%

main      {return MAIN;}
int       { return INT_TYPE; }
string    { return STRING_TYPE; }
print     { return PRINT; }
intTree   { return INT_TREE_TYPE; } 
stringTree { return STRING_TREE_TYPE; } 
intNode { return INT_NODE_TYPE; } 
stringNode { return STRING_NODE_TYPE; }

"+"											{ return ADD; }
"-"											{ return SUB; }
"*"											{ return MUL; }
"/"											{ return DIV; }

"("											{ return OPEN_PARENTHESIS; }
")"											{ return CLOSE_PARENTHESIS; }

{digit}+									{ return IntegerPatternAction(yytext); }
{whitespace}								{ IgnoredPatternAction(yytext); }

.											{ return UnknownPatternAction(yytext); }

%%
