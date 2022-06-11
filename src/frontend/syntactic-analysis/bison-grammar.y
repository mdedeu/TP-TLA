%{

#include "bison-actions.h"

%}

%union {
    char * string;
    int integer;
	int token;
	Variable* variable;
    ParameterList * parameterList;
	Vector* vector;
	Constant* constant;
	Factor* factor;
	Expression* expression;
	For* for;
	While* while;
	IfClose * ifClose;
	If * if;
	Write * write;
	Read * read;
	Function * function;
	Assignation * assignation;
	Declare * declare;
	DeclareAndAssign * declareAndAssign;
	Statement * statement;
	Instruction * instruction;
	Block * block;
	MainProgram * mainProgram;
}

// Terminales
%token <token> ADD SUB MUL DIV 
%token <token> EQ LE GE NE LT GT
%token <token> OR AND NOT
%token <token> ASSIGN
%token <token> POINT COMMA
%token <token> INT_TYPE STRING_TYPE
%token <token> NON_BINARY_TREE_TYPE BINARY_TREE_TYPE AVL_TREE_TYPE RED_BLACK_TREE_TYPE B_TREE_TYPE BST_TREE_TYPE NODE_TYPE
%token <token> MAIN PRINT READ WRITE NEW_NODE DELETE_NODE BALANCED LENGTH SIZE MODIFY_NODE SEARCH FILTER
%token <token> FOR WHILE IF ELSE
%token <token> OPEN_PARENTHESIS CLOSE_PARENTHESIS OPEN_CURL_BRACKETS CLOSE_CURL_BRACKETS OPEN_SQUARE_BRACKETS CLOSE_SQUARE_BRACKETS QUOTE END_LINE
%token <token> INTEGER STRING SYMBOL

// No terminales
%type <token> type treeType semiColons
%type <parameterList> parameterList;
%type <vector> vector;
%type <constant> constant;
%type <factor> factor;
%type <expression> expression;
%type <for> for;
%type <while> while;
%type <ifClose> if_close;
%type <if> if;
%type <token> multiParamFunctions oneParamFunctions noParamFunctions
%type <write> write;
%type <read> read;
%type <function> function;
%type <assignation assignation;
%type <declare> declare;
%type <declareAndAssign> declareAndAssign;
%type <statement> statement;
%type <instruction> instruction;
%type <block> block;
%type <mainProgram> mainProgram;

// Reglas de asociatividad y precedencia (de menor a mayor):
%left ADD SUB
%left MUL DIV
%left EQ NE LT LE GT GE AND OR NOT

%%

mainProgram: MAIN OPEN_CURL_BRACKETS block CLOSE_CURL_BRACKETS { $$ = ProgramGrammarAction(); }
	;

block: instruction block { $$ = add_element_to_list($2, $1); }
    | instruction		 { $$ = $1; }									
	;

instruction: statement semiColons 	{ $$ = InstructionsGrammarAction(); }
    | if 							{ $$ = IfGrammarAction(); }
	| for		  					{ $$ = ForGrammarAction(); }
	| while		  					{ $$ = WhileGrammarAction(); }
	;
	
statement: declareAndAssign 	{ $$ = StatementsGrammarAction(); }
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

assignation: SYMBOL ASSIGN expression  { $$ = assign_value_variable_node($1, $3); }
	;

function:	SYMBOL POINT noParamFunctions OPEN_PARENTHESIS CLOSE_PARENTHESIS  { $$ = NoParamFunctionGrammarAction(); }
	| SYMBOL POINT oneParamFunctions OPEN_PARENTHESIS expression CLOSE_PARENTHESIS  { $$ = OneParamFunctionGrammarAction(); }
	| SYMBOL POINT multiParamFunctions OPEN_PARENTHESIS parameterList CLOSE_PARENTHESIS { $$ = MultiParamFunctionGrammarAction(); }
	| SYMBOL POINT FILTER OPEN_PARENTHESIS expression CLOSE_PARENTHESIS { $$ = ExpressionFunctionGrammarAction(); }
	| read	{ $$ = ReadFunctionGrammarAction(); }
	| write	{ $$ = WriteFunctionGrammarAction(); }
	;
	
read: READ OPEN_PARENTHESIS SYMBOL CLOSE_PARENTHESIS { $$ = add_read_node(add_variable_reference($3)); }
	;

write: WRITE OPEN_PARENTHESIS expression CLOSE_PARENTHESIS { $$ = add_write_node($3); }
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
	
if: IF OPEN_PARENTHESIS expression CLOSE_PARENTHESIS OPEN_CURL_BRACKETS block if_close {$$ = add_if_node($3, add_block_node($6), $7); };
	;

if_close: CLOSE_CURL_BRACKETS { $$ = NULL; }
    | CLOSE_CURL_BRACKETS ELSE OPEN_CURL_BRACKETS block CLOSE_CURL_BRACKETS { $$ = add_block_node($4); };
	;

while: WHILE OPEN_PARENTHESIS expression CLOSE_PARENTHESIS OPEN_CURL_BRACKETS block CLOSE_CURL_BRACKETS { $$ = add_while_node($3, add_block_node($6)); };
	;

for: FOR OPEN_PARENTHESIS declareAndAssign semiColons expression semiColons statement CLOSE_PARENTHESIS OPEN_CURL_BRACKETS block CLOSE_CURL_BRACKETS
	| FOR OPEN_PARENTHESIS assignation semiColons expression semiColons statement CLOSE_PARENTHESIS OPEN_CURL_BRACKETS block CLOSE_CURL_BRACKETS
	| FOR OPEN_PARENTHESIS semiColons expression semiColons statement CLOSE_PARENTHESIS OPEN_CURL_BRACKETS block CLOSE_CURL_BRACKETS
	;

expression: expression ADD expression							{ $$ = add_expression_node($1, add_operation_node($2), $3); }
	| expression SUB expression									{ $$ = add_expression_node($1, add_operation_node($2), $3); }
	| expression MUL expression									{ $$ = add_expression_node($1, add_operation_node($2), $3); }
	| expression DIV expression									{ $$ = add_expression_node($1, add_operation_node($2), $3); }
	| expression GT expression 									{ $$ = add_expression_node($1, add_operation_node($2), $3); }
	| expression GE expression									{ $$ = add_expression_node($1, add_operation_node($2), $3); }
	| expression LE expression									{ $$ = add_expression_node($1, add_operation_node($2), $3); }
	| expression LT expression									{ $$ = add_expression_node($1, add_operation_node($2), $3); }
	| expression NE expression									{ $$ = add_expression_node($1, add_operation_node($2), $3); }
	| expression EQ expression									{ $$ = add_expression_node($1, add_operation_node($2), $3); }
	| NOT expression											{ $$ = add_expression_node(add_operation_node($1), $2, NULL); }
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

type: INT_TYPE
	| STRING_TYPE 
	;

treeType: NON_BINARY_TREE_TYPE 
	| BINARY_TREE_TYPE 
	| AVL_TREE_TYPE
	| RED_BLACK_TREE_TYPE 
	| B_TREE_TYPE 
	| BST_TREE_TYPE
	| NODE_TYPE
	;

semiColons: END_LINE
    | semiColons END_LINE
    ;


%%