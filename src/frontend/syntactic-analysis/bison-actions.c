
#include "../../backend/support/logger.h"
#include "bison-actions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Implementación de "bison-grammar.h".
 */

// TODO: error handler

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
	LogDebug("MainProgramGrammarAction ");
	MainProgram * toReturn = malloc(sizeof(MainProgram));
	toReturn->block = block;
	
	state.succeed = TRUE;
	state.mainProgram = toReturn;
	return toReturn;
}

Block * InstructionBlockGrammarAction(Instruction * instruction, Block * block) {
	LogDebug("InstructionBlockGrammarAction ");
	Block * toReturn = malloc(sizeof(Block));
	toReturn->type = INSTRUCTION_BLOCK;
	toReturn->block = block;
	toReturn->instruction = instruction;
	return toReturn;
}

Block * BlockGrammarAction(Instruction * instruction) {
	LogDebug("BlockGrammarAction ");
	Block * toReturn = malloc(sizeof(Block));
	toReturn->type = INSTRUCTION;
	toReturn->block = NULL;
	toReturn->instruction = instruction;
	return toReturn;
}

Instruction * StatementInstructionGrammarAction(Statement * statement) {
	LogDebug("StatementInstructionGrammarAction ");
	Instruction * toReturn = malloc(sizeof(Instruction));
	toReturn->type = STATEMENT_INSTRUCTION;
	toReturn->statement = statement;
	toReturn->for_instruction = NULL;
	toReturn->if_instruction = NULL;
	toReturn->while_instruction = NULL;
	return toReturn;
}

Instruction * IfInstructionGrammarAction(If * _if) {
	LogDebug("IfInstructionGrammarAction ");
	Instruction * toReturn = malloc(sizeof(Instruction));
	toReturn->type = IF_INSTRUCTION;
	toReturn->statement = NULL;
	toReturn->for_instruction = NULL;
	toReturn->if_instruction = _if;
	toReturn->while_instruction = NULL;
	return toReturn;
}

Instruction * ForInstructionGrammarAction(For * _for) {
	LogDebug("ForInstructionGrammarAction ");
	Instruction * toReturn = malloc(sizeof(Instruction));
	toReturn->type = FOR_INSTRUCTION;
	toReturn->statement = NULL;
	toReturn->for_instruction = _for;
	toReturn->if_instruction = NULL;
	toReturn->while_instruction = NULL;
	return toReturn;
}

Instruction * WhileInstructionGrammarAction(While * _while) {
	LogDebug("WhileInstructionGrammarAction ");
	Instruction * toReturn = malloc(sizeof(Instruction));
	toReturn->type = WHILE_INSTRUCTION;
	toReturn->statement = NULL;
	toReturn->for_instruction = NULL;
	toReturn->if_instruction = NULL;
	toReturn->while_instruction = _while;
	return toReturn;
}

Statement * DeclareAndAssignStatementGrammarAction(DeclareAndAssign * declareAndAssign) {
	LogDebug("DeclareAndAssignStatementGrammarAction ");
	Statement * toReturn = malloc(sizeof(Statement));
	toReturn->type = DECLARE_AND_ASSIGN;
	toReturn->declareAndAssign = declareAndAssign;
	toReturn->assignation = NULL;
	toReturn->function = NULL;
	return toReturn;
}

Statement * AssignationStatementGrammarAction(Assignation * assignation) {
	LogDebug("AssignationStatementGrammarAction ");
	Statement * toReturn = malloc(sizeof(Statement));
	toReturn->type = ASSIGNATION;
	toReturn->declareAndAssign = NULL;
	toReturn->assignation = assignation;
	toReturn->function = NULL;
	return toReturn;
}

Statement * FunctionStatementGrammarAction(Function * function) {
	LogDebug("FunctionStatementGrammarAction ");
	Statement * toReturn = malloc(sizeof(Statement));
	toReturn->type = FUNCTION;
	toReturn->declareAndAssign = NULL;
	toReturn->assignation = NULL;
	toReturn->function = function;
	return toReturn;
}

DeclareAndAssign * DeclareAndAssignGrammarAction(Declare * declare, Expression * expression) {
	LogDebug("DeclareAndAssignGrammarAction ");
	Variable * var = symbol_table_get(declare->variable);
	if(var == NULL) {
		printf("la variable no existe");
		exit(1);
	}
	DeclareAndAssign * toReturn = malloc(sizeof(DeclareAndAssign));
	toReturn->type = DECLARE_ASSIGN_EXPRESSION;
	toReturn->expression = expression;
	toReturn->declare = declare;
	toReturn->parameterList = NULL;
	return toReturn;
}

DeclareAndAssign * DeclareParameterListGrammarAction(Declare * declare, ParameterList * parameterList) {
	LogDebug("DeclareParameterListGrammarAction ");
	DeclareAndAssign * toReturn = malloc(sizeof(DeclareAndAssign));
	toReturn->type = DECLARE_ASSIGN_PARAM_LIST;
	toReturn->expression = NULL;
	toReturn->declare = declare;
	toReturn->parameterList = parameterList;
	return toReturn;
}

DeclareAndAssign * OnlyDeclareGrammarAction(Declare * declare) {
	LogDebug("OnlyDeclareGrammarAction ");
	DeclareAndAssign * toReturn = malloc(sizeof(DeclareAndAssign));
	toReturn->type = ONLY_DECLARE;
	toReturn->expression = NULL;
	toReturn->declare = declare;
	toReturn->parameterList = NULL;
	return toReturn;
}

Declare * TypeSymbolDeclareGrammarAction(Token * t_type, char * variable) {
	LogDebug("TypeSymbolDeclareGrammarAction %s ", variable);
	if(symbol_table_put(variable,t_type) == NULL) {
		printf("variable redeclarada");
		exit(1);
	}
	Declare * toReturn = malloc(sizeof(Declare));
	toReturn->type = TYPE_SYMBOL;
	toReturn->type_token = t_type;
	toReturn->variable = variable;
	toReturn->treeType_token = NULL;
	toReturn->vector = NULL;
	return toReturn;
}

Declare * TreetypeTpyeSymbolDeclareGrammarAction(Token * t_tree_type, Token * t_type, char * variable) {
	LogDebug("TreetypeTpyeSymbolDeclareGrammarAction %s" , variable);
	Variable * var = symbol_table_put(variable,t_type);
	if( var == NULL) {
		printf("variable redeclarada");
		exit(1);
	}
	var->value.nodes = 0;
	Declare * toReturn = malloc(sizeof(Declare));
	toReturn->type = TREE_TYPE_SYMBOL;
	toReturn->type_token = t_type;
	toReturn->variable = variable;
	toReturn->treeType_token = t_tree_type;
	toReturn->vector = NULL;
	return toReturn;
}

Declare * TypeVectorDeclareGrammarAction(Token * t_type, Vector * vector) {
	LogDebug("TypeVectorDeclareGrammarAction ");
	if(symbol_table_put(vector->variable,t_type) == NULL) {
		printf("variable redeclarada");
		exit(1);
	}
	Declare * toReturn = malloc(sizeof(Declare));
	toReturn->type = TREE_TYPE_SYMBOL;
	toReturn->type_token = t_type;
	toReturn->variable = NULL;
	toReturn->treeType_token = NULL;
	toReturn->vector = vector;
	return toReturn;
}

// TODO: chequear tipos?
Assignation * AssignationGrammarAction(char * variable, Expression * expression) {
	LogDebug("AssignationGrammarAction ");
	Variable * var = symbol_table_get(variable);
	if(var == NULL) {
		printf("la variable no existe");
		exit(1);
	}
	Assignation * toReturn = malloc(sizeof(Assignation));
	toReturn->Expression = expression;
	toReturn->variable = variable;
	return toReturn;
}

Function * NoParamFunctionGrammarAction(char * variable, Token * t_noparamfunction) {
	LogDebug("NoParamFunctionGrammarAction %s ", variable);
	Function * toReturn = malloc(sizeof(Function));
	toReturn->type = NO_PARAM_FUNCTIONS;
	toReturn->variable = variable;
	toReturn->noParamFunctionToken = t_noparamfunction;
	toReturn->oneParamFunctionToken = NULL;
	toReturn->expression = NULL;
	toReturn->parameterList = NULL;
	toReturn->read = NULL;
	toReturn->write = NULL;
	return toReturn;
}

Function * OneParamFunctionGrammarAction(char * variable, Token * t_oneparamfunction, Expression * expression) {
	LogDebug("OneParamFunctionGrammarAction ");
	Variable * var = symbol_table_get(variable);
	if(var == NULL) {
		printf("la variable no existe");
		exit(1);
	}
	Function * toReturn = malloc(sizeof(Function));
	toReturn->type = ONE_PARAM_FUNCTIONS;
	toReturn->variable = variable;
	toReturn->noParamFunctionToken = NULL;
	toReturn->oneParamFunctionToken = t_oneparamfunction;
	toReturn->expression = expression;
	toReturn->parameterList = NULL;
	toReturn->read = NULL;
	toReturn->write = NULL;
	return toReturn;
}


Function * ReadFunctionGrammarAction(Read * read) {
	LogDebug("ReadFunctionGrammarAction ");
	Function * toReturn = malloc(sizeof(Function));
	toReturn->type = READ_FUNCTION;
	toReturn->variable = NULL;
	toReturn->noParamFunctionToken = NULL;
	toReturn->oneParamFunctionToken = NULL;
	toReturn->expression = NULL;
	toReturn->parameterList = NULL;
	toReturn->read = read;
	toReturn->write = NULL;
	return toReturn;
}

Function * WriteFunctionGrammarAction(Write * write) {
	LogDebug("WriteFunctionGrammarAction ");
	Function * toReturn = malloc(sizeof(Function));
	toReturn->type = WRITE_FUNCTION;
	toReturn->variable = NULL;
	toReturn->noParamFunctionToken = NULL;
	toReturn->oneParamFunctionToken = NULL;
	toReturn->expression = NULL;
	toReturn->parameterList = NULL;
	toReturn->read = NULL;
	toReturn->write = write;
	return toReturn;
}

Read * ReadGrammarAction(char * variable) {
	LogDebug("ReadGrammarAction %s ", variable);
	Variable * var = symbol_table_get(variable);
	if(var == NULL) {
		printf("la variable no existe");
		exit(1);
	}
	Read * toReturn = malloc(sizeof(Read));
	toReturn->variable = variable;
	return toReturn;
}

Write * WriteGrammarAction(Expression * expression) {
	LogDebug("WriteGrammarAction ");
	Write * toReturn = malloc(sizeof(Write));
	toReturn->expression = expression;
	return toReturn;
}

Token * NoParamGrammarAction(int token) {
	LogDebug("NoParamGrammarAction %d",token);
	Token * toReturn = malloc(sizeof(Token));
	toReturn->value = token;
	return toReturn;
}
Token * OneParamGrammarAction(int token) {
	LogDebug("OneParamGrammarAction %d",token);
	Token * toReturn = malloc(sizeof(Token));
	toReturn->value = token;
	return toReturn;
}
Token * MultiParamGrammarAction(int token) {
	LogDebug("MultiParamGrammarAction %d",token);
	Token * toReturn = malloc(sizeof(Token));
	toReturn->value = token;
	return toReturn;
}

If * IfGrammarAction(Expression * expression, Block * block, IfClose * ifClose) {
	LogDebug("IfGrammarAction");
	If * toReturn = malloc(sizeof(If));
	toReturn->block = block;
	toReturn->expression = expression;
	toReturn->ifClose = ifClose;
	return toReturn;
}

IfClose* IfCloseNormalGrammarAction() {
	LogDebug("IfCloseNormalGrammarAction");
	IfClose * toReturn = malloc(sizeof(IfClose));
	toReturn->type = IF_CLOSE_NORMAL;
	toReturn->block = NULL;
	return toReturn;
}

IfClose* IfCloseElseGrammarAction(Block* block) {
	LogDebug("IfCloseElseGrammarAction");
	IfClose * toReturn = malloc(sizeof(IfClose));
	toReturn->type = IF_ELSE;
	toReturn->block = block;
	return toReturn;
}

While* WhileGrammarAction(Expression* expression, Block* block){
	LogDebug("WhileGrammarAction");
	While* toReturn =  malloc(sizeof(While));
	toReturn->expression =  expression;
	toReturn->block = block;
	return toReturn;
}


For* DeclareAndAssignForGrammarAction(DeclareAndAssign* declareAndAssign, Expression* expression, Statement* statement, Block* block){
	LogDebug("DeclareAndAssignForGrammarAction");
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
	LogDebug("AssignationForGrammarAction");
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
	LogDebug("IncompleteForGrammarAction");
	For* toReturn =  malloc(sizeof(For));
	toReturn->type = INCOMPLETE_FOR;
	toReturn->declareAndAssign = NULL;
	toReturn->assignation = NULL;
	toReturn->expression = expression;
	toReturn->statement = statement;
	toReturn->block = block;
	return toReturn;
}




Expression* AdditionExpressionGrammarAction(Expression* leftValue, Expression* rightValue){
	LogDebug("AdditionExpressionGrammarAction");
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
	LogDebug("SubstractionExpressionGrammarAction");
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
	LogDebug("MultiplicationExpressionGrammarAction");
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
	LogDebug("DivisionExpressionGrammarAction");
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
	LogDebug("GreaterExpressionGrammarAction");
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
	LogDebug("GreaterOrEqualExpressionGrammarAction");
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
	LogDebug("LesserOrEqualExpressionGrammarAction");
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
	LogDebug("LesserExpressionGrammarAction");
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
	LogDebug("NotEqualExpressionGrammarAction");
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
	LogDebug("EqualExpressionGrammarAction");
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
	LogDebug("NotExpressionGrammarAction");
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
	LogDebug("FactorExpressionGrammarAction");
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
	LogDebug("FunctionExpressionGrammarAction");
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
	LogDebug("VectorExpressionGrammarAction");
	Expression* toReturn =  malloc(sizeof(Expression));
	toReturn->type = ADD_EXPRESSION;
	toReturn->left = NULL;
	toReturn->right = NULL;
	toReturn->factor = NULL;
	toReturn->function = NULL;
	toReturn->vector = vector;
	return toReturn;
}

Factor* ExpressionFactorGrammarAction(Expression* expression){
	LogDebug("ExpressionFactorGrammarAction");
	Factor* toReturn =  malloc(sizeof(Factor));
	toReturn->type = EXPRESSION_FACTOR;
	toReturn->string = NULL;
	toReturn->constant = NULL;
	toReturn->variable = NULL;
	toReturn->expression = expression;
	return toReturn;
}

Factor* ConstantFactorGrammarAction(Constant* constant){
	LogDebug("ConstantFactorGrammarAction");
	Factor* toReturn =  malloc(sizeof(Factor));
	toReturn->type = CONSTANT_FACTOR;
	toReturn->string = NULL;
	toReturn->constant = constant;
	toReturn->variable = NULL;
	toReturn->expression = NULL;
	return toReturn;
}

Factor* SymbolFactorGrammarAction(char* symbol) {
	LogDebug("SymbolFactorGrammarAction %s", symbol);
	Variable * var = symbol_table_get(symbol);
	if(var == NULL) {
		printf("la variable no existe");
		exit(1);
	}
	Factor* toReturn =  malloc(sizeof(Factor));
	toReturn->type = SYMBOL_FACTOR;
	toReturn->string = NULL;
	toReturn->constant = NULL;
	toReturn->variable = symbol;
	toReturn->expression = NULL;
	return toReturn;
}

Factor* StringFactorGrammarAction(char* string){
	LogDebug("StringFactorGrammarAction: %s .",string);
	Factor* toReturn =  malloc(sizeof(Factor));
	toReturn->type = STRING_FACTOR;
	toReturn->string = string;
	toReturn->constant = NULL;
	toReturn->variable = NULL;
	toReturn->expression = NULL;
	return toReturn;
}

Constant* IntegerConstantGrammarAction(const int value){
	LogDebug("IntegerConstantGrammarAction %d", value);
	Constant* toReturn =  malloc(sizeof(Constant));
	toReturn->value = value;
	return toReturn;
}

Vector* VectorGrammarAction(char * var, Factor* factor){
	LogDebug("VectorGrammarAction %s", var);
	Vector* toReturn =  malloc(sizeof(Vector));
	toReturn->variable = var;
	toReturn->factor = factor;
	return toReturn;
}


ParameterList * ParameterListCommaExpressionGrammarAction(ParameterList * parameterList, Expression * expression){
	LogDebug("ParameterListCommaExpressionGrammarAction");
	ParameterList* toReturn = malloc(sizeof(ParameterList));
	toReturn->type = PARAM_COMMA_EXPRESSION;
	toReturn->expression = expression;
	toReturn->parameterList = parameterList;
	return toReturn;
}

ParameterList * ParameterListGrammarAction(Expression * expression){
	LogDebug("ParameterListGrammarAction");
	ParameterList* toReturn = malloc(sizeof(ParameterList));
	toReturn->type = EXPRESSION;
	toReturn->expression = expression;
	toReturn->parameterList = NULL;
	return toReturn;
}

Token * TypeGrammarAction(int token){
	LogDebug("TypeGrammarAction %i",token);
	Token * toReturn = malloc(sizeof(Token));
	toReturn->value = token;
	return toReturn;
}

Token * TreeTypeGrammarAction(int token){
	LogDebug("TreeTypeGrammarAction %d",token);
	Token * toReturn = malloc(sizeof(Token));
	toReturn->value = token;
	return toReturn;
}

Token * SemiColonsGrammarAction(int token){
	LogDebug("SemiColonsGrammarAction %d",token);
	Token * toReturn = malloc(sizeof(Token));
	toReturn->value = token;
	return toReturn;
}

char * SymbolGrammarAction(char * varName) {
	LogDebug("SymbolGrammarAction %s", varName);
	char * toReturn = malloc(strlen(varName)+1);
	strcpy(toReturn, varName);
	return toReturn;
}

char * StringGrammarAction(char * string) {
	LogDebug("StringGrammarAction %s", string);
	char * toReturn = malloc(strlen(string)+1);
	strcpy(toReturn, string);
	return toReturn;
}