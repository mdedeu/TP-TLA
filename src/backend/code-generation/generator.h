#ifndef GENERATOR_HEADER
#define GENERATOR_HEADER

#include "../support/shared.h"

void GeneratorProgram(MainProgram* program);
void GeneratorBlock(Block* block);
void GeneratorInstruction(Instruction* instruction);
void GeneratorStatement(Statement* statement);
void GeneratorDeclareAndAssign(DeclareAndAssign* declareAndAssign);
void GeneratorAssignation(Assignation* assignation);
void GeneratorFunction(Function* function);
void GeneratorDeclare(Declare* declare);
void GeneratorExpression(Expression* expression);
void GeneratorRead(Read* read);
void GeneratorWrite(Write* write);
void GeneratorIfClose(IfClose* ifClose);
void GeneratorIf(If* ifInstruction);
void GeneratorWhile(While* whileInstruction);
void GeneratorFor(For* forInstruction);
void GeneratorFactor(Factor* factor);
void GeneratorConstant(Constant* constant);
void GeneratorVector(Vector* vector);
void GeneratorParameterList(ParameterList* parameterList);
void GeneratorVariable(char* Variable);



#endif
