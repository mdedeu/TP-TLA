#include "../../backend/domain-specific/calculator.h"
#include "../../backend/support/logger.h"
#include "bison-actions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Implementación de "bison-grammar.h".
 */

void yyerror(const char * string) {
	LogError("Mensaje: '%s' debido a '%s' (linea %d).", string, yytext, yylineno);
	LogError("En ASCII es:");
	LogErrorRaw("\t");
	const int length = strlen(yytext);
	for (int i = 0; i < length; ++i) {
		LogErrorRaw("[%d]", yytext[i]);
	}
	LogErrorRaw("\n\n");
}


MainProgram * MainProgramGrammarAction(Block * block) {
	MainProgram * toReturn = malloc(sizeof(MainProgram));
	toReturn->block = block;
	
	state.succeed = TRUE;
	state.mainProgram = toReturn;
	return toReturn;
}

Block * InstructionBlockGrammarAction(Instruction * instruction, Block * block) {
	Block * toReturn = malloc(sizeof(Block));
	toReturn->BlockType = INSTRUCTION_BLOCK;
	toReturn->block = block;
	toReturn->instruction = instruction;
	return toReturn;
}

Block * BlockGrammarAction(Instruction * instruction) {
	Block * toReturn = malloc(sizeof(Block));
	toReturn->BlockType = INSTRUCTION;
	toReturn->block = NULL;
	toReturn->instruction = instruction;
	return toReturn;
}

Instruction * StatementInstructionGrammarAction(Statement * statement) {
	Instruction * toReturn = malloc(sizeof(Instruction));
	toReturn->type = STATEMENT_INSTRUCTION;
	toReturn->statement = statement;
	toReturn->for_instruction = NULL;
	toReturn->if_instruction = NULL;
	toReturn->while_instruction = NULL;
	return toReturn;
}

Instruction * IfInstructionGrammarAction(If * _if) {
	Instruction * toReturn = malloc(sizeof(Instruction));
	toReturn->type = IF_INSTRUCTION;
	toReturn->statement = NULL;
	toReturn->for_instruction = NULL;
	toReturn->if_instruction = _if;
	toReturn->while_instruction = NULL;
	return toReturn;
}

Instruction * ForInstructionGrammarAction(For * _for) {
	Instruction * toReturn = malloc(sizeof(Instruction));
	toReturn->type = FOR_INSTRUCTION;
	toReturn->statement = NULL;
	toReturn->for_instruction = _for;
	toReturn->if_instruction = NULL;
	toReturn->while_instruction = NULL;
	return toReturn;
}

Instruction * WhileInstructionGrammarAction(While * _while) {
	Instruction * toReturn = malloc(sizeof(Instruction));
	toReturn->type = WHILE_INSTRUCTION;
	toReturn->statement = NULL;
	toReturn->for_instruction = NULL;
	toReturn->if_instruction = NULL;
	toReturn->while_instruction = _while;
	return toReturn;
}

Statement * DeclareAndAssignStatementGrammarAction(DeclareAndAssign * declareAndAssign) {
	Statement * toReturn = malloc(sizeof(Statement));
	toReturn->type = DECLARE_AND_ASSIGN;
	toReturn->declareAndAssign = declareAndAssign;
	toReturn->assignation = NULL;
	toReturn->function = NULL;
	return toReturn;
}

Statement * AssignationStatementGrammarAction(Assignation * assignation) {
	Statement * toReturn = malloc(sizeof(Statement));
	toReturn->type = ASSIGNATION;
	toReturn->declareAndAssign = NULL;
	toReturn->assignation = assignation;
	toReturn->function = NULL;
	return toReturn;
}

Statement * FunctionStatementGrammarAction(Function * function) {
	Statement * toReturn = malloc(sizeof(Statement));
	toReturn->type = FUNCTION;
	toReturn->declareAndAssign = NULL;
	toReturn->assignation = NULL;
	toReturn->function = function;
	return toReturn;
}

DeclareAndAssign * DeclareAndAssignGrammarAction(Declare * declare, Expression * expression) {
	DeclareAndAssign * toReturn = malloc(sizeof(DeclareAndAssign));
	toReturn->type = DECLARE_ASSIGN_EXPRESSION;
	toReturn->expression = expression;
	toReturn->declare = NULL;
	toReturn->parameterList = NULL;
	return toReturn;
}

DeclareAndAssign * DeclareParameterListGrammarAction(Declare * declare, ParameterList * parameterList) {
	DeclareAndAssign * toReturn = malloc(sizeof(DeclareAndAssign));
	toReturn->type = DECLARE_ASSIGN_PARAM_LIST;
	toReturn->expression = NULL;
	toReturn->declare = NULL;
	toReturn->parameterList = parameterList;
	return toReturn;
}

DeclareAndAssign * OnlyDeclareGrammarAction(Declare * declare) {
	DeclareAndAssign * toReturn = malloc(sizeof(DeclareAndAssign));
	toReturn->type = DECLARE;
	toReturn->expression = NULL;
	toReturn->declare = declare;
	toReturn->parameterList = NULL;
	return toReturn;
}

Declare * TypeSymbolDeclareGrammarAction(int t_type, char * variable) {
	Declare * toReturn = malloc(sizeof(Declare));
	toReturn->type = TYPE_SYMBOL;
	toReturn->type_token = t_type;
	strcpy(toReturn->variable,variable);
	toReturn->treeType_token = -1;
	toReturn->vector = NULL;
	return toReturn;
}

Declare * TreetypeTpyeSymbolDeclareGrammarAction(int t_tree_type, int t_type, char * variable) {
	Declare * toReturn = malloc(sizeof(Declare));
	toReturn->type = TREE_TYPE_SYMBOL;
	toReturn->type_token = t_type;
	toReturn->variable = variable;
	toReturn->treeType_token = t_tree_type;
	toReturn->vector = NULL;
	return toReturn;
}

Declare * TypeVectorDeclareGrammarAction(int t_type, Vector * vector) {
	Declare * toReturn = malloc(sizeof(Declare));
	toReturn->type = TREE_TYPE_SYMBOL;
	toReturn->type_token = t_type;
	toReturn->variable = NULL;
	toReturn->treeType_token = -1;
	toReturn->vector = vector;
	return toReturn;
}

Assignation * AssignationGrammarAction(char * variable, Expression * expression) {
	Assignation * toReturn = malloc(sizeof(Assignation));
	toReturn->Expression = expression;
	strcpy(toReturn->variable,variable);
	return toReturn;
}

Function * NoParamFunctionGrammarAction(char * variable, int t_noparamfunction) {
	Function * toReturn = malloc(sizeof(Function));
	toReturn->type = NO_PARAM_FUNCTIONS;
	strcpy(toReturn->variable,variable);
	toReturn->noParamFunctionToken = t_noparamfunction;
	toReturn->multiParamFunctionToken = -1;
	toReturn->oneParamFunctionToken = -1;
	toReturn->expression = NULL;
	toReturn->parameterList = NULL;
	toReturn->read = NULL;
	toReturn->write = NULL;
	return toReturn;
}

Function * OneParamFunctionGrammarAction(char * variable, int t_oneparamfunction, Expression * expression) {
	Function * toReturn = malloc(sizeof(Function));
	toReturn->type = ONE_PARAM_FUNCTIONS;
	strcpy(toReturn->variable,variable);
	toReturn->noParamFunctionToken = -1;
	toReturn->multiParamFunctionToken = -1;
	toReturn->oneParamFunctionToken = t_oneparamfunction;
	toReturn->expression = expression;
	toReturn->parameterList = NULL;
	toReturn->read = NULL;
	toReturn->write = NULL;
	return toReturn;
}

Function * MultiParamFunctionGrammarAction(char * variable, int t_multiparamfunction, ParameterList * parameterList) {
	Function * toReturn = malloc(sizeof(Function));
	toReturn->type = MULTI_PARAM_FUNCTIONS;
	strcpy(toReturn->variable,variable);
	toReturn->noParamFunctionToken = -1;
	toReturn->multiParamFunctionToken = t_multiparamfunction;
	toReturn->oneParamFunctionToken = -1;
	toReturn->expression = NULL;
	toReturn->parameterList = parameterList;
	toReturn->read = NULL;
	toReturn->write = NULL;
	return toReturn;
}

Function * FilterFunctionGrammarAction(Expression * expression) {
	Function * toReturn = malloc(sizeof(Function));
	toReturn->type = FILTER_FUNCTION;
	toReturn->variable = NULL;
	toReturn->noParamFunctionToken = -1;
	toReturn->multiParamFunctionToken = -1;
	toReturn->oneParamFunctionToken = -1;
	toReturn->expression = expression;
	toReturn->parameterList = NULL;
	toReturn->read = NULL;
	toReturn->write = NULL;
	return toReturn;
}

Function * ReadFunctionGrammarAction(Read * read) {
	Function * toReturn = malloc(sizeof(Function));
	toReturn->type = READ_FUNCTION;
	toReturn->variable = NULL;
	toReturn->noParamFunctionToken = -1;
	toReturn->multiParamFunctionToken = -1;
	toReturn->oneParamFunctionToken = -1;
	toReturn->expression = NULL;
	toReturn->parameterList = NULL;
	toReturn->read = read;
	toReturn->write = NULL;
	return toReturn;
}

Function * WriteFunctionGrammarAction(Write * write) {
	Function * toReturn = malloc(sizeof(Function));
	toReturn->type = WRITE_FUNCTION;
	toReturn->variable = NULL;
	toReturn->noParamFunctionToken = -1;
	toReturn->multiParamFunctionToken = -1;
	toReturn->oneParamFunctionToken = -1;
	toReturn->expression = NULL;
	toReturn->parameterList = NULL;
	toReturn->read = NULL;
	toReturn->write = write;
	return toReturn;
}

Read * ReadGrammarAction(char * variable) {
	Read * toReturn = malloc(sizeof(Read));
	strcpy(toReturn->variable, variable);
	return toReturn;
}

Write * WriteGrammarAction(Expression * expression) {
	Write * toReturn = malloc(sizeof(Write));
	toReturn->expression = expression;
	return toReturn;
}

int NoParamGrammarAction(int token) {
	return token;
}
int OneParamGrammarAction(int token) {
	return token;
}
int MultiParamGrammarAction(int token) {
	return token;
}

//
If * IfGrammarAction(Expression * expression, Block * block, IfClose * ifClose) {
	If * toReturn = malloc(sizeof(If));
	toReturn->block = block;
	toReturn->expression = expression;
	toReturn->ifClose = ifClose;
	return toReturn;
}

IfClose* IfCloseNormalGrammarAction() {
	IfClose * toReturn = malloc(sizeof(IfClose));
	toReturn->ifCloseType = IF_CLOSE_NORMAL;
	toReturn->block = NULL;
	return toReturn;
}

IfClose* IfCloseElseGrammarAction(Block* block) {
	IfClose * toReturn = malloc(sizeof(IfClose));
	toReturn->ifCloseType = IF_ELSE;
	toReturn->block = block;
	return toReturn;
}

While* WhileGrammarAction(Expression* expression, Block* block){
	While* toReturn =  malloc(sizeof(While));
	toReturn->expression =  expression;
	toReturn->block = block;
	return toReturn;
}


For* DeclareAndAssignForGrammarAction(DeclareAndAssign* declareAndAssign, Expression* expression, Statement* statement, Block* block){
	For* toReturn =  malloc(sizeof(For));
	toReturn->type = DECLARE_ASSIGN_FOR;
	toReturn->declareAndAssign = declareAndAssign;
	toReturn->assignation = NULL;
	toReturn->expression = expression;
	toReturn->statement = statement;
	toReturn->block = block;
	return toReturn;
}
	
	
For* AssignationForGrammarAction(Assignation* assignation,  Expression* expression, Statement* statement, Block* block){
	For* toReturn =  malloc(sizeof(For));
	toReturn->type = ASSIGNATION_FOR;
	toReturn->declareAndAssign = NULL;
	toReturn->assignation = assignation;
	toReturn->expression = expression;
	toReturn->statement = statement;
	toReturn->block = block;
	return toReturn;
}

For* IncompleteForGrammarAction( Expression* expression, Statement* statement, Block* block){
	For* toReturn =  malloc(sizeof(For));
	toReturn->type = INCOMPLETE_FOR;
	toReturn->declareAndAssign = NULL;
	toReturn->assignation = NULL;
	toReturn->expression = expression;
	toReturn->statement = statement;
	toReturn->block = block;
	return toReturn;
}




//Expresiones
Expression* AdditionExpressionGrammarAction(Expression* leftValue, Expression* rightValue){
	Expression* toReturn =  malloc(sizeof(Expression));
	toReturn->type = ADD_EXPRESSION;
	toReturn->left = leftValue;
	toReturn->right = rightValue;
	toReturn->factor = NULL;
	toReturn->function = NULL;
	toReturn->vector = NULL;
	return toReturn;
}

Expression* SubstractionExpressionGrammarAction(Expression* leftValue, Expression* rightValue){
	Expression* toReturn =  malloc(sizeof(Expression));
	toReturn->type = SUB_EXPRESSION;
	toReturn->left = leftValue;
	toReturn->right = rightValue;
	toReturn->factor = NULL;
	toReturn->function = NULL;
	toReturn->vector = NULL;
	return toReturn;
}

Expression* MultiplicationExpressionGrammarAction(Expression* leftValue, Expression* rightValue){
	Expression* toReturn =  malloc(sizeof(Expression));
	toReturn->type = MUL_EXPRESSION;
	toReturn->left = leftValue;
	toReturn->right = rightValue;
	toReturn->factor = NULL;
	toReturn->function = NULL;
	toReturn->vector = NULL;
	return toReturn;
}
	
Expression* DivisionExpressionGrammarAction(Expression* leftValue, Expression* rightValue){
	Expression* toReturn =  malloc(sizeof(Expression));
	toReturn->type = DIV_EXPRESSION;
	toReturn->left = leftValue;
	toReturn->right = rightValue;
	toReturn->factor = NULL;
	toReturn->function = NULL;
	toReturn->vector = NULL;
	return toReturn;
}

Expression* GreaterExpressionGrammarAction(Expression* leftValue, Expression* rightValue){
	Expression* toReturn =  malloc(sizeof(Expression));
	toReturn->type = GT_EXPRESSION;
	toReturn->left = leftValue;
	toReturn->right = rightValue;
	toReturn->factor = NULL;
	toReturn->function = NULL;
	toReturn->vector = NULL;
	return toReturn;
}

Expression* GreaterOrEqualExpressionGrammarAction(Expression* leftValue, Expression* rightValue){
	Expression* toReturn =  malloc(sizeof(Expression));
	toReturn->type = GE_EXPRESSION;
	toReturn->left = leftValue;
	toReturn->right = rightValue;
	toReturn->factor = NULL;
	toReturn->function = NULL;
	toReturn->vector = NULL;
	return toReturn;
}

Expression* LesserOrEqualExpressionGrammarAction(Expression* leftValue, Expression* rightValue){
	Expression* toReturn =  malloc(sizeof(Expression));
	toReturn->type = LE_EXPRESSION;
	toReturn->left = leftValue;
	toReturn->right = rightValue;
	toReturn->factor = NULL;
	toReturn->function = NULL;
	toReturn->vector = NULL;
	return toReturn;
}

Expression* LesserExpressionGrammarAction(Expression* leftValue, Expression* rightValue){
	Expression* toReturn =  malloc(sizeof(Expression));
	toReturn->type = LT_EXPRESSION;
	toReturn->left = leftValue;
	toReturn->right = rightValue;
	toReturn->factor = NULL;
	toReturn->function = NULL;
	toReturn->vector = NULL;
	return toReturn;
}

Expression* NotEqualExpressionGrammarAction(Expression* leftValue, Expression* rightValue){
	Expression* toReturn =  malloc(sizeof(Expression));
	toReturn->type = NE_EXPRESSION;
	toReturn->left = leftValue;
	toReturn->right = rightValue;
	toReturn->factor = NULL;
	toReturn->function = NULL;
	toReturn->vector = NULL;
	return toReturn;
}

Expression* EqualExpressionGrammarAction(Expression* leftValue, Expression* rightValue){
	Expression* toReturn =  malloc(sizeof(Expression));
	toReturn->type = EQ_EXPRESSION;
	toReturn->left = leftValue;
	toReturn->right = rightValue;
	toReturn->factor = NULL;
	toReturn->function = NULL;
	toReturn->vector = NULL;
	return toReturn;
	
}

Expression* NotExpressionGrammarAction(Expression* expression){
	Expression* toReturn =  malloc(sizeof(Expression));
	toReturn->type = NOT_EXPRESSION;
	toReturn->left = NULL;
	toReturn->right = expression;
	toReturn->factor = NULL;
	toReturn->function = NULL;
	toReturn->vector = NULL;
	return toReturn;
}
Expression* FactorExpressionGrammarAction(Factor* factor){
	Expression* toReturn =  malloc(sizeof(Expression));
	toReturn->type = FACTOR_EXPRESSION;
	toReturn->left = NULL;
	toReturn->right = NULL;
	toReturn->factor = factor;
	toReturn->function = NULL;
	toReturn->vector = NULL;
	return toReturn;
	
}

Expression* FunctionExpressionGrammarAction(Function* function){
	Expression* toReturn =  malloc(sizeof(Expression));
	toReturn->type = FUNCTION_EXPRESSION;
	toReturn->left = NULL;
	toReturn->right = NULL;
	toReturn->factor = NULL;
	toReturn->function = function;
	toReturn->vector = NULL;
	return toReturn;
}

Expression* VectorExpressionGrammarAction(Vector* vector){
	Expression* toReturn =  malloc(sizeof(Expression));
	toReturn->type = ADD_EXPRESSION;
	toReturn->left = NULL;
	toReturn->right = NULL;
	toReturn->factor = NULL;
	toReturn->function = NULL;
	toReturn->vector = vector;
	return toReturn;
}



//Factor 
Factor* ExpressionFactorGrammarAction(Expression* expression){
	Factor* toReturn =  malloc(sizeof(Factor));
	toReturn->type = EXPRESSION_FACTOR;
	toReturn->string = NULL;
	toReturn->constant = NULL;
	toReturn->variable = NULL;
	toReturn->expression = expression;
	return toReturn;
}

Factor* ConstantFactorGrammarAction(Constant* constant){
	Factor* toReturn =  malloc(sizeof(Factor));
	toReturn->type = CONSTANT_FACTOR;
	toReturn->string = NULL;
	toReturn->constant = constant;
	toReturn->variable = NULL;
	toReturn->expression = NULL;
	return toReturn;
}

Factor* SymbolFactorGrammarAction(char* symbol) {
	Factor* toReturn =  malloc(sizeof(Factor));
	toReturn->type = SYMBOL_FACTOR;
	toReturn->string = NULL;
	toReturn->constant = NULL;
	strcpy(toReturn->variable,symbol);
	toReturn->expression = NULL;
	return toReturn;
}

Factor* StringFactorGrammarAction(char* string){
	Factor* toReturn =  malloc(sizeof(Factor));
	toReturn->type = STRING_FACTOR;
	strcpy(toReturn->string,string);
	toReturn->constant = NULL;
	toReturn->variable = NULL;
	toReturn->expression = NULL;
	return toReturn;
}


//Constant
Constant* IntegerConstantGrammarAction(const int value){
	Constant* toReturn =  malloc(sizeof(Constant));
	toReturn->value = value;
	return toReturn;
}


//Vector
Vector* VectorConstantGrammarAction(char * symbol, Constant* constant){
	Vector* toReturn =  malloc(sizeof(Vector));
	toReturn->type = CONSTANT_VECTOR;
	strcpy(toReturn->variable,symbol);
	toReturn->variable2 = NULL;
	toReturn->constant = constant;
	return toReturn;
}

Vector* VectorSymbolGrammarAction(char * symbol, char* symbol2){
	Vector* toReturn =  malloc(sizeof(Vector));
	toReturn->type = SYMBOL_VECTOR;
	strcpy(toReturn->variable,symbol);
	strcpy(toReturn->variable2,symbol2);
	toReturn->constant = NULL;
	return toReturn;
}


ParameterList * ParameterListCommaExpressionGrammarAction(ParameterList * parameterList, Expression * expression){
	ParameterList* toReturn = malloc(sizeof(ParameterList));
	toReturn->type = PARAM_COMMA_EXPRESSION;
	toReturn->expression = expression;
	toReturn->parameterList = parameterList;
	return toReturn;
}

ParameterList * ParameterListGrammarAction(Expression * expression){
	ParameterList* toReturn = malloc(sizeof(ParameterList));
	toReturn->type = EXPRESSION;
	toReturn->expression = expression;
	toReturn->parameterList = NULL;
	return toReturn;
}

//Types

int TypeGrammarAction(int token){
	LogDebug("TypeGrammarAction %d",token);
	return token;
}

int TreeTypeGrammarAction(int token){
	LogDebug("TreeTypeGrammarAction %d",token);
	return token;
}

int SemiColonsGrammarAction(int token){
	LogDebug("SemiColonsGrammarAction %d",token);
	return token;
}