#include "free_lib.h"
#include "logger.h"

void free_ast(MainProgram * mainProgram) {
    if(mainProgram == NULL)
        return;
    LogDebug("free of ast");
    freeBlock(mainProgram->block);
    free(mainProgram);
}

void freeBlock(Block * block) {
    if(block == NULL)
        return;
    LogDebug("freeBlock");
    freeInstruction(block->instruction);
    freeBlock(block->block);
    free(block);
}

void freeInstruction(Instruction * instruction) {
    if(instruction == NULL)
        return;
    LogDebug("freeInstruction");
    freeStatement(instruction->statement);
	freeIf(instruction->if_instruction);
	freeFor(instruction->for_instruction);
    freeWhile(instruction->while_instruction);
    free(instruction);
}

void freeStatement(Statement * statement) {
    if(statement == NULL)
        return;
    LogDebug("freeStatement");
    freeDeclareAndAssign(statement->declareAndAssign);
    freeAssignation(statement->assignation);
    freeFunction(statement->function);
    free(statement);
}

void freeIf(If * _if) {
    if(_if == NULL)
        return;
    LogDebug("freeIf");
    freeExpression(_if->expression);
    freeBlock(_if->block);
    freeIfClose(_if->ifClose);
    free(_if);
}

void freeFor(For * _for) {
    if(_for == NULL)
        return;
    LogDebug("freeFor");
    freeDeclareAndAssign(_for->declareAndAssign);
    freeAssignation(_for->assignation);
    freeExpression(_for->expression);
    freeStatement(_for->statement);
    freeBlock(_for->block);
    free(_for);
}

void freeWhile(While * _while) {
    if(_while == NULL)
        return;
    LogDebug("freeWhile");
    freeExpression(_while->expression);
    freeBlock(_while->block);
    free(_while);
}

void freeDeclareAndAssign(DeclareAndAssign * declareAndAssign) {
    if(declareAndAssign == NULL)
        return;
    LogDebug("freeDeclareAndAssign");
    freeDeclare(declareAndAssign->declare);
    freeExpression(declareAndAssign->expression);
    freeParameterList(declareAndAssign->parameterList);
	free(declareAndAssign);
}

void freeAssignation(Assignation * assignation) {
    if(assignation == NULL)
        return;
    LogDebug("freeAssignation");
    freeVariable(assignation->variable);
    freeExpression(assignation->Expression);
    free(assignation);
}

void freeFunction(Function * function) {
    if(function == NULL)
        return;
    LogDebug("freeFunction");
    freeVariable(function->variable);
    freeToken(function->noParamFunctionToken);
    freeToken(function->oneParamFunctionToken);
    freeExpression(function->expression);
    freeParameterList(function->parameterList);
    freeRead(function->read);
    freeWrite(function->write);
    free(function);
}

void freeExpression(Expression * expression) {
    if(expression == NULL)
        return;
    LogDebug("freeExpression");
    freeExpression(expression->left);
    freeExpression(expression->right);
    freeFactor(expression->factor);
    freeFunction(expression->function);
    freeVector(expression->vector);
    free(expression);
}

void freeIfClose(IfClose * ifClose) {
    if(ifClose == NULL)
        return;
    LogDebug("freeIfClose");
    freeBlock(ifClose->block);
    free(ifClose);
}

void freeFactor(Factor * factor) {
    if(factor == NULL)
        return;
    LogDebug("freeFactor");
    freeConstant(factor->constant);
    freeString(factor->string);
    freeVariable(factor->variable);
    freeExpression(factor->expression);
    free(factor);
}

void freeVector(Vector * vector) {
    if(vector == NULL) 
        return;
    LogDebug("freeVector");
    freeFactor(vector->factor);
    freeVariable(vector->variable);
    free(vector);
}

void freeDeclare(Declare * declare) {
    if(declare == NULL)
        return;
    LogDebug("freeDeclare");
    freeToken(declare->treeType_token);
    freeToken(declare->type_token);
    freeVariable(declare->variable);
    free(declare);
}

void freeParameterList(ParameterList * parameterList) {
    if(parameterList == NULL)
        return;
    LogDebug("freeParameterList");
    freeExpression(parameterList->expression);
    freeParameterList(parameterList->parameterList);
    free(parameterList);
}

void freeToken(Token * token) {
    if(token == NULL)
        return;
    LogDebug("freeToken");
    free(token);
}

void freeRead(Read * read) {
    if(read == NULL)
        return;
    LogDebug("freeRead");
    freeVariable(read->variable);
    free(read);
}

void freeWrite(Write * write) {
    if(write == NULL)
        return;
    LogDebug("freeWrite");
    freeExpression(write->expression);
    free(write);
}

void freeConstant(Constant * constant) {
    if(constant == NULL)
        return;
    LogDebug("freeConstant");
    free(constant);
}

void freeString(char * string) {
    if(string == NULL)
        return;
    LogDebug("freeString");
    free(string);
}

void freeVariable(char * variable) {
    if(variable == NULL)
        return;
    LogDebug("freeVariable");
    free(variable);
}