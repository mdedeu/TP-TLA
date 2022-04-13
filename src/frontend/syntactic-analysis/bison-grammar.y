%{

#include "bison-actions.h"

%}

// IDs de los tokens generados desde Flex:
%token ADD
%token SUB
%token MUL
%token DIV

%token EQ
%token LE
%token GE
%token NE
%token LT
%token GT

%token OR
%token AND
%token NOT

%token ASSIGN

%token INT_TYPE
%token STRING_TYPE

%token NON_BINARY_TREE_TYPE
%token BINARY_TREE_TYPE
%token AVL_TREE_TYPE
%token RED_BLACK_TREE_TYPE
%token B_TREE_TYPE
%token BST_TREE_TYPE
%token NODE_TYPE

%token MAIN
%token PRINT

%token FOR
%token WHILE
%token IF
%token ELSE


%token OPEN_PARENTHESIS
%token CLOSE_PARENTHESIS
%token  OPEN_BRACKETS
%token  CLOSE_BRACKETS
%token  OPEN_SQUARE_BRACKETS
%token  CLOSE_SQUARE_BRACKETS
%token  QUOTE
%token  END_LINE

%token INTEGER
%token STRING
%token CHAR

// Reglas de asociatividad y precedencia (de menor a mayor):
%left ADD SUB
%left MUL DIV

%%

program: MAIN { expression }												{ $$ = ProgramGrammarAction($1); }
	;

expression: expression ADD expression							{ $$ = AdditionExpressionGrammarAction($1, $3); }
	| expression SUB expression									{ $$ = SubtractionExpressionGrammarAction($1, $3); }
	| expression MUL expression									{ $$ = MultiplicationExpressionGrammarAction($1, $3); }
	| expression DIV expression									{ $$ = DivisionExpressionGrammarAction($1, $3); }
	| factor													{ $$ = FactorExpressionGrammarAction($1); }
	;

factor: OPEN_PARENTHESIS expression CLOSE_PARENTHESIS			{ $$ = ExpressionFactorGrammarAction($2); }
	| constant													{ $$ = ConstantFactorGrammarAction($1); }
	;

constant: INTEGER												{ $$ = IntegerConstantGrammarAction($1); }
	;

Type
	: INT_TYPE
	| STRING_TYPE
	| NON_BINARY_TREE_TYPE
	| BINARY_TREE_TYPE
	| AVL_TREE_TYPE
	| RED_BLACK_TREE_TYPE
	| B_TREE_TYPE
	| BST_TREE_TYPE
	| NODE_TYPE
	;

SemiColons
	: ';'
        | SemiColons ';'
        ;

%%
