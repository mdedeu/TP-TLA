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

%token POINT
%token COMMA

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
%token NEW_NODE

%token RETURN
%token FOR
%token WHILE
%token IF
%token ELSE


%token OPEN_PARENTHESIS
%token CLOSE_PARENTHESIS
%token  OPEN_CURL_BRACKETS
%token  CLOSE_CURL_BRACKETS
%token  OPEN_SQUARE_BRACKETS
%token  CLOSE_SQUARE_BRACKETS
%token  QUOTE
%token  END_LINE

%token INTEGER
%token STRING
%token SYMBOL

// Reglas de asociatividad y precedencia (de menor a mayor):
%left ADD SUB
%left MUL DIV


%%

mainProgram: MAIN OPEN_CURL_BRACKETS program CLOSE_CURL_BRACKETS { $$ = ProgramGrammarAction(); }
	;

program: instruction program	
	| instruction											
	;

block: instruction block 
    | instruction
	;

if: IF OPEN_PARENTHESIS expression CLOSE_PARENTHESIS OPEN_CURL_BRACKETS block if_close
	;

if_close: CLOSE_CURL_BRACKETS 
    | CLOSE_CURL_BRACKETS ELSE OPEN_CURL_BRACKETS block CLOSE_CURL_BRACKETS
	;

while: WHILE OPEN_PARENTHESIS expression CLOSE_PARENTHESIS OPEN_CURL_BRACKETS block CLOSE_CURL_BRACKETS
	;

return: RETURN expression semiColons
	;

expression: expression ADD expression							{ $$ = AdditionExpressionGrammarAction($1, $3); }
	| expression SUB expression									{ $$ = SubtractionExpressionGrammarAction($1, $3); }
	| expression MUL expression									{ $$ = MultiplicationExpressionGrammarAction($1, $3); }
	| expression DIV expression									{ $$ = DivisionExpressionGrammarAction($1, $3); }
	| factor													{ $$ = FactorExpressionGrammarAction($1); }
	| STRING
	| SYMBOL
	;

factor: OPEN_PARENTHESIS expression CLOSE_PARENTHESIS			{ $$ = ExpressionFactorGrammarAction($2); }
	| constant													{ $$ = ConstantFactorGrammarAction($1); }
	;

constant: INTEGER												{ $$ = IntegerConstantGrammarAction($1); }
	;

instruction: declare  
	|	declareAndAssign 
	|	function
	|   expression 
	| 	if
	|	while 
	| 	vector
	|   return
	;


function:	SYMBOL POINT NEW_NODE OPEN_PARENTHESIS expression COMMA expression CLOSE_PARENTHESIS semiColons 
	| SYMBOL POINT NEW_NODE  OPEN_PARENTHESIS expression COMMA expression COMMA expression CLOSE_PARENTHESIS semiColons
	| SYMBOL POINT PRINT OPEN_PARENTHESIS CLOSE_PARENTHESIS semiColons
	;

declareAndAssign:	type SYMBOL ASSIGN expression semiColons 
	|	type SYMBOL ASSIGN function	/* en realidad solo la new node */ 
	;


declare: type SYMBOL semiColons 
	| treeType type SYMBOL semiColons 
	;

type
	: INT_TYPE
	| STRING_TYPE 
	;

treeType 
	: NON_BINARY_TREE_TYPE 
	| BINARY_TREE_TYPE 
	| AVL_TREE_TYPE
	| RED_BLACK_TREE_TYPE 
	| B_TREE_TYPE 
	| BST_TREE_TYPE 
	| NODE_TYPE 
	;

semiColons
	: END_LINE
    | semiColons END_LINE
    ;

vector:
	type SYMBOL OPEN_SQUARE_BRACKETS constant CLOSE_SQUARE_BRACKETS semiColons
	| type SYMBOL OPEN_SQUARE_BRACKETS CLOSE_SQUARE_BRACKETS semiColons
%%