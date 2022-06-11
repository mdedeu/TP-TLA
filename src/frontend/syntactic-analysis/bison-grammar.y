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
%token <token> OPEN_PARENTHESIS CLOSE_PARENTHESIS OPEN_CURL_BRACKETS CLOSE_CURL_BRACKETS OPEN_SQUARE_BRACKETS CLOSE_SQUARE_BRACKETS QUOTE SEMI_COLON
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

mainProgram: MAIN OPEN_CURL_BRACKETS block CLOSE_CURL_BRACKETS 										{ $$ = MainProgramGrammarAction($3); }
	;

block: instruction block 																			{ $$ = InstructionBlockGrammarAction($1, $2); }
    | instruction		 																			{ $$ = BlockGrammarAction($1); }									
	;

instruction: statement semiColons 																	{ $$ = StatementInstructionGrammarAction($1); }
    | if 																							{ $$ = IfInstructionGrammarAction($1); }
	| for		  																					{ $$ = ForInstructionGrammarAction($1); }
	| while		  																					{ $$ = WhileInstructionGrammarAction($1); }
	;
	
statement: declareAndAssign 																		{ $$ = DeclareAndAssignStatementGrammarAction($1); }
	| assignation																					{ $$ = AssignationStatementGrammarAction($1); }
	| function																					    { $$ = FunctionStatementGrammarAction($1); }

declareAndAssign:	declare ASSIGN expression  														{ $$ = DeclareAndAssignGrammarAction($1,$3); }
	|   declare ASSIGN OPEN_CURL_BRACKETS parameterList CLOSE_CURL_BRACKETS	    					{ $$ = DeclareParameterListGrammarAction($1,$4); }
	| 	declare																						{ $$ = OnlyDeclareGrammarAction($1); }
	;

declare: type SYMBOL  																				{ $$ = TypeSymbolDeclareGrammarAction($1,$2); }
	| treeType type SYMBOL  																		{ $$ = TreetypeTpyeSymbolDeclareGrammarAction($1,$2,$3); }
	| type vector  																					{ $$ = TypeVectorDeclareGrammarAction($1,$2); }
	;

assignation: SYMBOL ASSIGN expression  																{ $$ = AssignationGrammarAction($1, $3); }
	;

function:	SYMBOL POINT noParamFunctions OPEN_PARENTHESIS CLOSE_PARENTHESIS  						{ $$ = NoParamFunctionGrammarAction($1,$3); }
	| SYMBOL POINT oneParamFunctions OPEN_PARENTHESIS expression CLOSE_PARENTHESIS  				{ $$ = OneParamFunctionGrammarAction($1,$3,$5); }
	| SYMBOL POINT multiParamFunctions OPEN_PARENTHESIS parameterList CLOSE_PARENTHESIS 			{ $$ = MultiParamFunctionGrammarAction($1,$3,$5); }
	| SYMBOL POINT FILTER OPEN_PARENTHESIS expression CLOSE_PARENTHESIS								{ $$ = FilterFunctionGrammarAction($5); }
	| read																							{ $$ = ReadFunctionGrammarAction($1); }
	| write																							{ $$ = WriteFunctionGrammarAction($2); }
	;
	
read: READ OPEN_PARENTHESIS SYMBOL CLOSE_PARENTHESIS		 										{ $$ = ReadGrammarAction($3); }
	;

write: WRITE OPEN_PARENTHESIS expression CLOSE_PARENTHESIS   										{ $$ = WriteGrammarAction($3); }
	;

noParamFunctions: PRINT										 										{ $$ = NoParamGrammarAction($1); }
	| LENGTH												 										{ $$ = NoParamGrammarAction($1); }
	| BALANCED											   	 										{ $$ = NoParamGrammarAction($1); }
	| SIZE													 										{ $$ = NoParamGrammarAction($1); }
	;
	
oneParamFunctions: DELETE_NODE																		{ $$ = OneParamGrammarAction($1); }
	| MODIFY_NODE																					{ $$ = OneParamGrammarAction($1); }
	| SEARCH																						{ $$ = OneParamGrammarAction($1); }
	;
	
multiParamFunctions: NEW_NODE																		{ $$ = MultiParamGrammarAction($1); }
	;	
	
if: IF OPEN_PARENTHESIS expression CLOSE_PARENTHESIS OPEN_CURL_BRACKETS block if_close 				{$$ = IfGrammarAction($3, $6, $7);};
	;

if_close: CLOSE_CURL_BRACKETS 																		{ $$ = IfCloseNormalGrammarAction(); }
    | CLOSE_CURL_BRACKETS ELSE OPEN_CURL_BRACKETS block CLOSE_CURL_BRACKETS 						{ $$ = IfCloseElseGrammarAction($4); };
	;

while: WHILE OPEN_PARENTHESIS expression CLOSE_PARENTHESIS OPEN_CURL_BRACKETS block CLOSE_CURL_BRACKETS 	{ $$ = WhileGrammarAction($3, $6); };
	;

for: FOR OPEN_PARENTHESIS declareAndAssign semiColons expression semiColons statement CLOSE_PARENTHESIS OPEN_CURL_BRACKETS block CLOSE_CURL_BRACKETS{ $$ = DeclareAndAssignForGrammarAction($3, $5, $7, $10); }
	| FOR OPEN_PARENTHESIS assignation semiColons expression semiColons statement CLOSE_PARENTHESIS OPEN_CURL_BRACKETS block CLOSE_CURL_BRACKETS    { $$ = AssignationForGrammarAction($3, $5, $7, $10); }
	| FOR OPEN_PARENTHESIS semiColons expression semiColons statement CLOSE_PARENTHESIS OPEN_CURL_BRACKETS block CLOSE_CURL_BRACKETS	            { $$ = IncompleteForGrammarAction($4, $6, $9); }
	;

expression: expression ADD expression							{ $$ = AdditionExpressionGrammarAction($1, $3); }
	| expression SUB expression									{ $$ = SubstractionExpressionGrammarAction($1, $3); }
	| expression MUL expression									{ $$ = MultiplicationExpressionGrammarAction($1, $3); }
	| expression DIV expression									{ $$ = DivisionExpressionGrammarAction($1, $3); }
	| expression GT expression 									{ $$ = GreaterExpressionGrammarAction($1, $3); }
	| expression GE expression									{ $$ = GreaterOrEqualExpressionGrammarAction($1, $3); }
	| expression LE expression									{ $$ = LesserOrEqualExpressionGrammarAction($1,$3); }
	| expression LT expression									{ $$ = LesserExpressionGrammarAction($1, $3); }
	| expression NE expression									{ $$ = NotEqualExpressionGrammarAction($1, $3); }
	| expression EQ expression									{ $$ = EqualExpressionGrammarAction($1, $3); }
	| NOT expression											{ $$ = NotExpressionGrammarAction($2); }
	| factor													{ $$ = FactorExpressionGrammarAction($1); }
	| function													{ $$ = FunctionExpressionGrammarAction($1); }
	| vector													{ $$ = VectorExpressionGrammarAction($1); }
	;

factor: OPEN_PARENTHESIS expression CLOSE_PARENTHESIS			{ $$ = ExpressionFactorGrammarAction($2); }
	| constant													{ $$ = ConstantFactorGrammarAction($1); }
	| STRING													{ $$ = StringFactorGrammarAction($1); }
	| SYMBOL													{ $$ = SymbolFactorGrammarAction($1); }
	
	;

constant: INTEGER												{ $$ = IntegerConstantGrammarAction($1); }
	;

vector: 
	SYMBOL OPEN_SQUARE_BRACKETS constant CLOSE_SQUARE_BRACKETS	 { $$ = VectorConstantGrammarAction($1, $2); }
	| SYMBOL OPEN_SQUARE_BRACKETS SYMBOL CLOSE_SQUARE_BRACKETS	 { $$ = VectorSymbolGrammarAction($1, $2); }
	;

parameterList: expression 										{ $$ = ParameterListGrammarAction($1); }
	| parameterList COMMA expression							{ $$ = ParameterListCommaExpressionGrammarAction($1,$3); }
	;

type: INT_TYPE													{  $$ = TypeGrammarAction($1);  }
	| STRING_TYPE 												{  $$ = TypeGrammarAction($2);  }
	;

treeType: NON_BINARY_TREE_TYPE 									{  $$ = TreeTypeGrammarAction($1);  }
	| BINARY_TREE_TYPE 											{  $$ = TreeTypeGrammarAction($1);  }
	| AVL_TREE_TYPE												{  $$ = TreeTypeGrammarAction($1);  }
	| RED_BLACK_TREE_TYPE 										{  $$ = TreeTypeGrammarAction($1);  }
	| B_TREE_TYPE 												{  $$ = TreeTypeGrammarAction($1);  }
	| BST_TREE_TYPE												{  $$ = TreeTypeGrammarAction($1);  }
	| NODE_TYPE													{  $$ = TreeTypeGrammarAction($1);  }
	;

semiColons: SEMI_COLON											{  $$ = SemiColonsGrammarAction($1);  }
    | semiColons SEMI_COLON										{  $$ = SemiColonsGrammarAction($2);  }
    ;


%%