#ifndef GARBAGE_HEADER
#define GARBAGE_HEADER
#include "shared.h"
#include <string.h>
#include <stdlib.h>

void free_ast(MainProgram * mainProgram);

void freeBlock(Block * block);

void freeInstruction(Instruction * instruction);

void freeStatement(Statement * statement);

void freeIf(If * _if);

void freeFor(For * _for);

void freeWhile(While * _while);

void freeDeclareAndAssign(DeclareAndAssign * declareAndAssign);

void freeAssignation(Assignation * assignation);

void freeFunction(Function * function);

void freeExpression(Expression * expression);

void freeIfClose(IfClose * ifClose);

void freeFactor(Factor * factor);

void freeVector(Vector * vector);

void freeDeclare(Declare * declare);

void freeParameterList(ParameterList * parameterList);

void freeToken(Token * token);

void freeRead(Read * read);

void freeWrite(Write * write);

void freeConstant(Constant * constant);

void freeString(char * string);

void freeVariable(char * variable);
#endif