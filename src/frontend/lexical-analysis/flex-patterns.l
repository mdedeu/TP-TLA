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
char [a-zA-Z]

%%

main      {return MAIN;}
int       { return INT_TYPE; }
string    { return STRING_TYPE; }
print     { return PRINT; }
tree     { return NON_BINARY_TREE_TYPE; }
binary_tree     { return BINARY_TREE_TYPE; }
avl_tree   { return AVL_TREE_TYPE; }
rb_tree {return RED_BLACK_TREE_TYPE; }
b_tree { return B_TREE_TYPE; }
bst_tree { return BST_TREE_TYPE; }
node { return NODE_TYPE; }



"+"											{ return ADD; }
"-"											{ return SUB; }
"*"											{ return MUL; }
"/"											{ return DIV; }
"=="		{ return EQ; }
"<="		{ return LE; }
">="		{ return GE; }
"!="		{ return NE; }
"<" { return LT; }
">" { return GT; }
"||"		{return OR; }
"&&"		{return AND;}
"!" { return NOT; }

"=" { return ASSIGN; }

"for"		{return FOR;}
"while" { return WHILE;}
"if"    { return IF;}
"else" { return ELSE;}


"("											{ return OPEN_PARENTHESIS; }
")"											{ return CLOSE_PARENTHESIS; }
"{"											{ return OPEN_BRACKETS ; }
"}"											{ return CLOSE_BRACKETS ; }
"["											{ return OPEN_SQUARE_BRACKETS ; }
"]"											{ return CLOSE_SQUARE_BRACKETS ; }
"'"                                         { return  QUOTE; }
";"											{ return END_LINE; }


{digit}+									{ return IntegerPatternAction(yytext); }
{whitespace}								{ IgnoredPatternAction(yytext); }
{char}+ { return CharPatternAction(yytext); } //solo se pueden declarar vars con letras

.											{ return UnknownPatternAction(yytext); }

%%
