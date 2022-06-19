#ifndef GENERATOR_HEADER
#define GENERATOR_HEADER

#include "../support/shared.h"
#include "../../frontend/syntactic-analysis/bison-parser.h"

void GeneratorProgram(MainProgram* program, FILE * out);
void GeneratorBlock(Block* block, FILE * output);
void GeneratorInstruction(Instruction* instruction, FILE * output);
void GeneratorStatement(Statement* statement, FILE * output);
void GeneratorDeclareAndAssign(DeclareAndAssign* declareAndAssign, FILE * output);
void GeneratorAssignation(Assignation* assignation, FILE * output);
void GeneratorFunction(Function* function, FILE * output);
void GeneratorDeclare(Declare* declare, FILE * output);
void GeneratorExpression(Expression* expression, FILE * output);
void GeneratorRead(Read* read, FILE * output);
void GeneratorWrite(Write* write, FILE * output);
void GeneratorIfClose(IfClose* ifClose, FILE * output);
void GeneratorIf(If* ifInstruction, FILE * output);
void GeneratorWhile(While* whileInstruction, FILE * output);
void GeneratorFor(For* forInstruction, FILE * output);
void GeneratorFactor(Factor* factor, FILE * output);
void GeneratorConstant(Constant* constant, FILE * output);
void GeneratorVector(Vector* vector, FILE * output);
void GeneratorParameterList(ParameterList* parameterList, FILE * output);



#endif
