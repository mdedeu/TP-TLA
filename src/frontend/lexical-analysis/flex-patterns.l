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
digit			[0-9]
whitespace		[ \f\n\r\t\v]
letter [a-zA-Z]

%%


"+"											{ return ADD; }
"-"											{ return SUB; }
"*"											{ return MUL; }
"/"											{ return DIV; }
"=="		                                { return EQ; }
"<="		                                { return LE; }
">="		                                { return GE; }
"!="		                                { return NE; }
"<"                                         { return LT; }
">"                                         { return GT; }
"||"		                                { return OR; }
"&&"		                                { return AND;}
"!"                                         { return NOT; }


"="                                         { return ASSIGN; }


"."                                         { return POINT; }
","                                         { return COMMA; }

int                                         { return INT_TYPE; }
string                                      { return STRING_TYPE; }

tree                                        { return NON_BINARY_TREE_TYPE; }
binaryTree                                  { return BINARY_TREE_TYPE; }
avlTree                                     { return AVL_TREE_TYPE; }
rbtree                                      { return RED_BLACK_TREE_TYPE; }
bTree                                       { return B_TREE_TYPE; }
bstTree                                     { return BST_TREE_TYPE; }
node                                        { return NODE_TYPE; }

main                                        { return MAIN;}
print                                       { return PRINT; }
read                                        { return READ; }
write                                       { return WRITE; }
createNode                                  { return NEW_NODE; }
balanced                                    { return BALANCED; }
size                                        { return SIZE; }
length                                      { return LENGTH; }
deleteNode                                  { return DELETE_NODE; }
modifyNode                                  { return MODIFY_NODE; }
search                                      { return SEARCH; }
filter                                      { return FILTER; }



"for"		                                { return FOR;}
"while"                                     { return WHILE;}
"if"                                        { return IF;}
"else"                                      { return ELSE;}


"("											{ return OPEN_PARENTHESIS; }
")"											{ return CLOSE_PARENTHESIS; }
"{"											{ return OPEN_CURL_BRACKETS ; }
"}"											{ return CLOSE_CURL_BRACKETS ; }
"["											{ return OPEN_SQUARE_BRACKETS ; }
"]"											{ return CLOSE_SQUARE_BRACKETS ; }
"'"                                         { return  QUOTE; }
";"											{ return END_LINE; }


{digit}+									{ return IntegerPatternAction(yytext); }
{whitespace}								{ IgnoredPatternAction(yytext); }
\/\/.*                                      { IgnoredPatternAction(yytext); }
{letter}+                                   { return SymbolPatternAction(yytext); } //solo se pueden declarar vars con letras
\"[^\"]+\"                                  { return StringPatternAction(yytext); }

.											{ return UnknownPatternAction(yytext); }

%%