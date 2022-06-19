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

int                                         { yylval.token = INT_TYPE; return INT_TYPE; }
string                                      { yylval.token = STRING_TYPE; return STRING_TYPE; }

avlTree                                     { yylval.token = AVL_TREE_TYPE; return AVL_TREE_TYPE; }
rbtree                                      { yylval.token = RED_BLACK_TREE_TYPE; return RED_BLACK_TREE_TYPE; }
bstTree                                     { yylval.token = BST_TREE_TYPE; return BST_TREE_TYPE; }

main                                        { return MAIN;}
print                                       { yylval.token = PRINT; return PRINT; }
read                                        { yylval.token = READ; return READ; }
write                                       { yylval.token = WRITE; return WRITE; }
createNode                                  { yylval.token = NEW_NODE; return NEW_NODE; }
balanced                                    { yylval.token = BALANCED; return BALANCED; }
size                                        { yylval.token = SIZE; return SIZE; }
length                                      { yylval.token = LENGTH; return LENGTH; }
deleteNode                                  { yylval.token = DELETE_NODE; return DELETE_NODE; }
filter                                      { yylval.token = FILTER; return FILTER; }
mul                                         { yylval.token = TREE_MULT; return TREE_MULT; }



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
"'"                                         { return QUOTE; }
";"											{ return SEMI_COLON; }


{digit}+									{ return IntegerPatternAction(yytext); }
{whitespace}								{ IgnoredPatternAction(yytext); }
\/\/.*                                      { IgnoredPatternAction(yytext); }
\"[^\"]+\"                                  { return StringPatternAction(yytext); }
{letter}+                                   { return SymbolPatternAction(yytext); } //solo se pueden declarar vars con letras

.											{ return UnknownPatternAction(yytext); }

%%