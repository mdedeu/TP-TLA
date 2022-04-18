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
%token DELETE_NODE
%token BALANCED
%token LENGTH
%token SIZE
%token MODIFY_NODE

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
	|										
	;

block: instruction block 
    | instruction
	| 
	;

if: IF OPEN_PARENTHESIS expression CLOSE_PARENTHESIS OPEN_CURL_BRACKETS block if_close
	;

if_close: CLOSE_CURL_BRACKETS 
    | CLOSE_CURL_BRACKETS ELSE OPEN_CURL_BRACKETS block CLOSE_CURL_BRACKETS
	;

while: WHILE OPEN_PARENTHESIS expression CLOSE_PARENTHESIS OPEN_CURL_BRACKETS block CLOSE_CURL_BRACKETS
	;

for: FOR OPEN_PARENTHESIS declareAndAssign expression semiColons expression CLOSE_PARENTHESIS OPEN_CURL_BRACKETS block CLOSE_CURL_BRACKETS
	;

expression: expression ADD expression							{ $$ = AdditionExpressionGrammarAction($1, $3); }
	| expression SUB expression									{ $$ = SubtractionExpressionGrammarAction($1, $3); }
	| expression MUL expression									{ $$ = MultiplicationExpressionGrammarAction($1, $3); }
	| expression DIV expression									{ $$ = DivisionExpressionGrammarAction($1, $3); }
	| expression GT expression
	| expression GE expression
	| expression LE expression
	| expression LT expression									
	| expression NE expression
	| expression EQ expression
	| factor													{ $$ = FactorExpressionGrammarAction($1); }
	| STRING
	| SYMBOL
	| SYMBOL POINT SIZE OPEN_PARENTHESIS CLOSE_PARENTHESIS
	;

factor: OPEN_PARENTHESIS expression CLOSE_PARENTHESIS			{ $$ = ExpressionFactorGrammarAction($2); }
	| constant													{ $$ = ConstantFactorGrammarAction($1); }
	;

constant: INTEGER												{ $$ = IntegerConstantGrammarAction($1); }
	;

instruction: declare  
	|	declareAndAssign 
	|	function
	|   expression semiColons
	| 	if
	|	while 
	|   for
	;


function:	SYMBOL POINT NEW_NODE OPEN_PARENTHESIS expression COMMA expression CLOSE_PARENTHESIS semiColons 
	| SYMBOL POINT NEW_NODE  OPEN_PARENTHESIS expression COMMA expression COMMA expression CLOSE_PARENTHESIS semiColons
	| SYMBOL POINT PRINT OPEN_PARENTHESIS CLOSE_PARENTHESIS semiColons
	| SYMBOL POINT BALANCED OPEN_PARENTHESIS CLOSE_PARENTHESIS semiColons
	| SYMBOL POINT LENGTH OPEN_PARENTHESIS CLOSE_PARENTHESIS semiColons
	| SYMBOL POINT SIZE OPEN_PARENTHESIS CLOSE_PARENTHESIS semiColons
	| SYMBOL POINT DELETE_NODE OPEN_PARENTHESIS expression CLOSE_PARENTHESIS semiColons
	| SYMBOL POINT MODIFY_NODE OPEN_PARENTHESIS expression CLOSE_PARENTHESIS semiColons
	;

declareAndAssign:	type SYMBOL ASSIGN expression semiColons 
	|	type SYMBOL ASSIGN function
	| 	treeType type SYMBOL ASSIGN expression semiColons
	|   nodeType type SYMBOL ASSIGN function	
	|   type vector ASSIGN OPEN_CURL_BRACKETS parameterList CLOSE_CURL_BRACKETS semiColons
	;

declare: type SYMBOL semiColons 
	| treeType type SYMBOL semiColons 
	| type vector semiColons
	;

parameterList: expression 
	| parameterList COMMA expression
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
	| nodeType

nodeType: NODE_TYPE 
	;

semiColons
	: END_LINE
    | semiColons END_LINE
    ;

vector:
	SYMBOL OPEN_SQUARE_BRACKETS constant CLOSE_SQUARE_BRACKETS
	
%%