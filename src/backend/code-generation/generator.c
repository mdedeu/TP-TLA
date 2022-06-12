#include "../support/logger.h"
#include "generator.h"

/**
 * Implementación de "generator.h".
 */

void Generator(MainProgram* program) {
	write("int main { \n");
	GeneratorBlock(program->block);
	write("}");
	//LogInfo("El resultado de la expresion computada es: '%d'.", result);
}

void GeneratorBlock(Block* block){
	switch (block->type)
	{
		case INSTRUCTION_BLOCK:
			break;
		case INSTRUCTION:
			break;

		default:
			LogInfo("Block Type not found");
			break;
	}

}

void GeneratorInstruction(Instruction* instruction){
	switch (instruction->type)
	{
		case STATEMENT_INSTRUCTION:
			break;
		case IF_INSTRUCTION:
			break;
		case FOR_INSTRUCTION:
			break;
		case WHILE_INSTRUCTION:
			break;
		default:
			LogInfo("Instruction Type not found");
			break;
	}
}

void GeneratorStatement(Statement* statement){
	switch (statement->type)
	{
		case DECLARE_AND_ASSIGN:
			break;
		case ASSIGNATION:
			break;
		case FUNCTION:
			break;

		default:
			LogInfo("Statement Type not found");
			break;
	}
}

void GeneratorDeclareAndAssign(DeclareAndAssign* declareAndAssign){
	switch (declareAndAssign->type)
	{
		case DECLARE_ASSIGN_EXPRESSION:
			break;
		case DECLARE_ASSIGN_PARAM_LIST:
			break;
		case DECLARE:
			break;
		default:
			LogInfo("DeclareAndASsign Type not found");
			break;
	}
}


void GeneratorDeclare(Declare* declare){
	switch (declare->type)
	{
		case TYPE_SYMBOL:
			break;
		case TREE_TYPE_SYMBOL:
			break;
		case TYPE_VECTOR:
			break;
		default:
			LogInfo("Declare Type not found");
			break;
	}
	
}

void GeneratorAssignation(Assignation* assignation){
	
}

void GeneratorFunction(Function* function){
	switch (function->type)
	{
		case NO_PARAM_FUNCTIONS:
			break;
		case ONE_PARAM_FUNCTIONS:
			break;
		case MULTI_PARAM_FUNCTIONS:
			break;
		case FILTER_FUNCTION:
			break;
		case READ_FUNCTION:
			break;
		case WRITE_FUNCTION:
			break;
		default:
			LogInfo("Function Type not found");
			break;
	}
}

void GeneratorRead(Read* read){

}

void GeneratorWrite(Write* write){

}


void GeneratorIfClose(IfClose* ifClose){
	switch (ifClose->type)
	{
		case IF_CLOSE_NORMAL:
			break;
		case IF_ELSE:
			break;
		default:
			LogInfo("IfClose Type not found");
			break;
	}
}

void GeneratorIf(If* ifInstruction){

}

void GeneratorWhile(While* whileInstruction){

}

void GeneratorFor(For* forInstruction){
	switch (forInstruction->type)
	{
		case DECLARE_ASSIGN_FOR:
			break;
		case ASSIGNATION_FOR:
			break;
		case INCOMPLETE_FOR:
			break;
		default:
			LogInfo("For Type not found");
			break;
	}
}

void GeneratorExpression(Expression* expression){
	switch (expression->type)
	{
		case ADD_EXPRESSION:
			break;
		case SUB_EXPRESSION:
			break;
		case MUL_EXPRESSION:
			break;
		case DIV_EXPRESSION:
			break;
		case FACTOR_EXPRESSION:
			break;
		case GT_EXPRESSION:
			break;
		case GE_EXPRESSION:
			break;
		case LE_EXPRESSION:
			break;
		case LT_EXPRESSION:
			break;
		case NE_EXPRESSION:
			break;
		case EQ_EXPRESSION:
			break;
		case NOT_EXPRESSION:
			break;	
		case FUNCTION_EXPRESSION:
			break;	
		case VECTOR_EXPRESSION:
			break;
		default:
			LogInfo("Expression Type not found");
			break;
	}

}


void GeneratorFactor(Factor* factor){
	switch (factor->type)
	{
		case CONSTANT_FACTOR:
			break;
		case STRING_FACTOR:
			break;
		case SYMBOL_FACTOR:
			break;
		case EXPRESSION_FACTOR:
			break;
		default:
			LogInfo("Factor Type not found");
			break;
	}
}

void GeneratorConstant(Constant* constant){

}

void GeneratorVector(Vector* vector){
	switch (vector->type)
	{
		case CONSTANT_VECTOR:
			break;
		case SYMBOL_VECTOR:
			break;
		default:
			LogInfo("Vector Type not found");
			break;
	}

}

void GeneratorParameterList(ParameterList* parameterList){
	switch (parameterList->type)
	{
		case EXPRESSION:
			break;
		case PARAM_COMMA_EXPRESSION:
			break;

		default:
			LogInfo("ParameterList Type not found");
			break;
	}
}

void GeneratorVariable(Variable* Variable){

}
