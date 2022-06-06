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

%token MAIN PRINT READ WRITE NEW_NODE DELETE_NODE BALANCED LENGTH SIZE MODIFY_NODE SEARCH FILTER


%token FOR WHILE IF ELSE


%token OPEN_PARENTHESIS CLOSE_PARENTHESIS OPEN_CURL_BRACKETS CLOSE_CURL_BRACKETS OPEN_SQUARE_BRACKETS CLOSE_SQUARE_BRACKETS QUOTE END_LINE

%token INTEGER STRING SYMBOL

// Reglas de asociatividad y precedencia (de menor a mayor):
%left ADD SUB
%left MUL DIV
%left EQ NE LT LE GT GE AND OR NOT


%%

mainProgram: MAIN OPEN_CURL_BRACKETS block CLOSE_CURL_BRACKETS { $$ = ProgramGrammarAction(); }
	;

block: instruction block { $$ = BlockGrammarAction(); }
    | instruction		 { $$ = BlockGrammarAction(); }									
	;

instruction: statements semiColons 	{ $$ = InstructionsGrammarAction(); }
	| 	control_block				{ $$ = InstructionsGrammarAction(); }
	;
	
statements: declareAndAssign 	{ $$ = StatementsGrammarAction(); }
	| assignation				{ $$ = StatementsGrammarAction(); }
	| function					{ $$ = StatementsGrammarAction(); }
	;

declareAndAssign:	declare ASSIGN expression  { $$ = DeclareAndAssignGrammarAction(); }
	|   declare ASSIGN OPEN_CURL_BRACKETS parameterList CLOSE_CURL_BRACKETS	   { $$ = DeclareAndAssignGrammarAction(); }
	| 	declare	{ $$ = DeclareAndAssignGrammarAction(); }
	;

declare: type SYMBOL  { $$ = DeclareGrammarAction(); }
	| treeType type SYMBOL  { $$ = DeclareGrammarAction(); }
	| type vector  { $$ = DeclareGrammarAction(); }
	;

assignation: SYMBOL ASSIGN expression  { $$ = AssignationGrammarAction(); }
	;

function:	SYMBOL POINT noParamFunctions OPEN_PARENTHESIS CLOSE_PARENTHESIS  { $$ = NoParamFunctionGrammarAction(); }
	| SYMBOL POINT oneParamFunctions OPEN_PARENTHESIS expression CLOSE_PARENTHESIS  { $$ = OneParamFunctionGrammarAction(); }
	| SYMBOL POINT multiParamFunctions OPEN_PARENTHESIS parameterList CLOSE_PARENTHESIS { $$ = MultiParamFunctionGrammarAction(); }
	| SYMBOL POINT FILTER OPEN_PARENTHESIS expression CLOSE_PARENTHESIS { $$ = ExpressionFunctionGrammarAction(); }
	| read	{ $$ = ReadFunctionGrammarAction(); }
	| write	{ $$ = WriteFunctionGrammarAction(); }
	;
	
read: READ OPEN_PARENTHESIS SYMBOL CLOSE_PARENTHESIS
	;

write: WRITE OPEN_PARENTHESIS expression CLOSE_PARENTHESIS 
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
	
control_block: if { $$ = IfGrammarAction(); }
	| for		  { $$ = ForGrammarAction(); }
	| while		  { $$ = WhileGrammarAction(); }
	;

if: IF OPEN_PARENTHESIS expression CLOSE_PARENTHESIS OPEN_CURL_BRACKETS block if_close 
	;

if_close: CLOSE_CURL_BRACKETS 
    | CLOSE_CURL_BRACKETS ELSE OPEN_CURL_BRACKETS block CLOSE_CURL_BRACKETS
	;

while: WHILE OPEN_PARENTHESIS expression CLOSE_PARENTHESIS OPEN_CURL_BRACKETS block CLOSE_CURL_BRACKETS
	;

for: FOR OPEN_PARENTHESIS declareAndAssign semiColons expression semiColons statements CLOSE_PARENTHESIS OPEN_CURL_BRACKETS block CLOSE_CURL_BRACKETS
	| FOR OPEN_PARENTHESIS assignation semiColons expression semiColons statements CLOSE_PARENTHESIS OPEN_CURL_BRACKETS block CLOSE_CURL_BRACKETS
	| FOR OPEN_PARENTHESIS semiColons expression semiColons statements CLOSE_PARENTHESIS OPEN_CURL_BRACKETS block CLOSE_CURL_BRACKETS
	;

expression: expression ADD expression							{ $$ = AdditionExpressionGrammarAction($1, $3); }
	| expression SUB expression									{ $$ = SubtractionExpressionGrammarAction($1, $3); }
	| expression MUL expression									{ $$ = MultiplicationExpressionGrammarAction($1, $3); }
	| expression DIV expression									{ $$ = DivisionExpressionGrammarAction($1, $3); }
	| expression GT expression 									{ $$ = GreaterExpressionGrammarAction(); }
	| expression GE expression									{ $$ = GreaterOrEqualExpressionGrammarAction(); }
	| expression LE expression									{ $$ = LesserOrEqualExpressionGrammarAction(); }
	| expression LT expression									{ $$ = LesserExpressionGrammarAction(); }
	| expression NE expression									{ $$ = NotEqualExpressionGrammarAction(); }
	| expression EQ expression									{ $$ = EqualExpressionGrammarAction(); }
	| NOT expression
	| factor													{ $$ = FactorExpressionGrammarAction($1); }
	| function
	| vector
	;

factor: OPEN_PARENTHESIS expression CLOSE_PARENTHESIS			{ $$ = ExpressionFactorGrammarAction($2); }
	| constant													{ $$ = ConstantFactorGrammarAction($1); }
	| STRING
	| SYMBOL
	;

constant: INTEGER												{ $$ = IntegerConstantGrammarAction($1); }
	;

vector: 
	SYMBOL OPEN_SQUARE_BRACKETS constant CLOSE_SQUARE_BRACKETS	 { $$ = VectorGrammarAction(); }
	| SYMBOL OPEN_SQUARE_BRACKETS SYMBOL CLOSE_SQUARE_BRACKETS	 { $$ = VectorGrammarAction(); }
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