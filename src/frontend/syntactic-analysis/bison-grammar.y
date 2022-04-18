%{

#include "bison-actions.h"

%}

// IDs de los tokens generados desde Flex:
%token ADD SUB MUL DIV 


%token EQ LE GE NE LT GT

%token OR AND NOT

%token ASSIGN

%token POINT COMMA

%token INT_TYPE STRING_TYPE

%token NON_BINARY_TREE_TYPE BINARY_TREE_TYPE AVL_TREE_TYPE RED_BLACK_TREE_TYPE B_TREE_TYPE BST_TREE_TYPE NODE_TYPE

%token MAIN PRINT NEW_NODE DELETE_NODE BALANCED LENGTH SIZE MODIFY_NODE SEARCH FILTER


%token FOR WHILE IF ELSE


%token OPEN_PARENTHESIS CLOSE_PARENTHESIS OPEN_CURL_BRACKETS CLOSE_CURL_BRACKETS OPEN_SQUARE_BRACKETS CLOSE_SQUARE_BRACKETS QUOTE END_LINE

%token INTEGER STRING SYMBOL

// Reglas de asociatividad y precedencia (de menor a mayor):
%left ADD SUB
%left MUL DIV


%%

mainProgram: MAIN OPEN_CURL_BRACKETS block CLOSE_CURL_BRACKETS { $$ = ProgramGrammarAction(); }
	;

block: instruction block 
    | instruction
	;

instruction: declareAndAssign semiColons
	|	assignation semiColons
	|	function semiColons
	| 	control_block
	|
	;


declareAndAssign:	declare ASSIGN expression 
	|	declare ASSIGN function
	|   declare ASSIGN OPEN_CURL_BRACKETS parameterList CLOSE_CURL_BRACKETS
	| 	declare
	;

declare: type SYMBOL 
	| treeType type SYMBOL 
	| type vector 
	;

assignation: SYMBOL ASSIGN expression
	| SYMBOL ASSIGN function
	| SYMBOL ADD ASSIGN expression 
	;

function:	SYMBOL POINT noParamFunctions OPEN_PARENTHESIS CLOSE_PARENTHESIS 
	| SYMBOL POINT oneParamFunctions OPEN_PARENTHESIS expression CLOSE_PARENTHESIS  
	| SYMBOL POINT multiParamFunctions OPEN_PARENTHESIS parameterList CLOSE_PARENTHESIS 
	| SYMBOL POINT FILTER OPEN_PARENTHESIS expression CLOSE_PARENTHESIS 
	;
	
noParamFunctions: PRINT
	| LENGTH
	| BALANCED
	| SIZE
	;
	
oneParamFunctions: DELETE_NODE
	| MODIFY_NODE
	| SEARCH
	;
	
multiParamFunctions:
	NEW_NODE
	;	
	
control_block: if
	| for
	| while
	;

if: IF OPEN_PARENTHESIS expression CLOSE_PARENTHESIS OPEN_CURL_BRACKETS block if_close
	;

if_close: CLOSE_CURL_BRACKETS 
    | CLOSE_CURL_BRACKETS ELSE OPEN_CURL_BRACKETS block CLOSE_CURL_BRACKETS
	;

while: WHILE OPEN_PARENTHESIS expression CLOSE_PARENTHESIS OPEN_CURL_BRACKETS block CLOSE_CURL_BRACKETS
	;

for: FOR OPEN_PARENTHESIS declareAndAssign semiColons expression semiColons instruction CLOSE_PARENTHESIS OPEN_CURL_BRACKETS block CLOSE_CURL_BRACKETS
	| FOR OPEN_PARENTHESIS assignation semiColons expression semiColons instruction CLOSE_PARENTHESIS OPEN_CURL_BRACKETS block CLOSE_CURL_BRACKETS
	| FOR OPEN_PARENTHESIS semiColons expression semiColons instruction CLOSE_PARENTHESIS OPEN_CURL_BRACKETS block CLOSE_CURL_BRACKETS
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
	| function
	| assignation
	| vector
	;

factor: OPEN_PARENTHESIS expression CLOSE_PARENTHESIS			{ $$ = ExpressionFactorGrammarAction($2); }
	| constant													{ $$ = ConstantFactorGrammarAction($1); }
	;

constant: INTEGER												{ $$ = IntegerConstantGrammarAction($1); }
	;

vector:
	SYMBOL OPEN_SQUARE_BRACKETS constant CLOSE_SQUARE_BRACKETS
	| SYMBOL OPEN_SQUARE_BRACKETS SYMBOL CLOSE_SQUARE_BRACKETS
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
	| NODE_TYPE
	;

semiColons
	: END_LINE
    | semiColons END_LINE
    ;


%%