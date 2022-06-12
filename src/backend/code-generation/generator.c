#include "../support/logger.h"
#include "generator.h"

/**
 * Implementación de "generator.h".
 */

void Generator(MainProgram* program) {
	write("int main { \n");
	GeneratorBlock(program->block);
	write(" }");
	//LogInfo("El resultado de la expresion computada es: '%d'.", result);
}

void GeneratorBlock(Block* block){
	switch (block->type)
	{
		case INSTRUCTION_BLOCK:
			GeneratorInstruction(block->instruction);
			write(" ");
			Generator(block->block);
			break;
		case INSTRUCTION:
			GeneratorInstruction(block->instruction);
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
			GeneratorStatement(instruction->statement);
			write(" ;");
			break; 
		case IF_INSTRUCTION:
			GeneratorIf(instruction->if_instruction);
			break;
		case FOR_INSTRUCTION:
			GeneratorFor(instruction->for_instruction);
			break;
		case WHILE_INSTRUCTION:
			GeneratorWhile(instruction->while_instruction);
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
			GeneratorDeclareAndAssign(statement->declareAndAssign);
			break;
		case ASSIGNATION:
			GeneratorAssignation(statement->assignation);
			break;
		case FUNCTION:
			GeneratorFunction(statement->function);
			break;

		default:
			LogInfo("Statement Type not found");
			break;
	}
}

void GeneratorDeclareAndAssign(DeclareAndAssign* declareAndAssign){
	GeneratorDeclare(declareAndAssign->declare);
	switch (declareAndAssign->type)
	{
		case DECLARE_ASSIGN_EXPRESSION:
			
			write(" = ");
			GeneratorExpression(declareAndAssign->expression);
			break;
		case DECLARE_ASSIGN_PARAM_LIST:
			write(" = ( ");
			GeneratorParameterList(declareAndAssign->parameterList);
			write(" ) ");
			break;
		case DECLARE:
			write(" ");
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
			write(declare->type_token);
			write(" "); 
			GeneratorVariable(declare->variable);
			break;
		case TREE_TYPE_SYMBOL:
			//aca hay q hacer cosas raras
			break;
		case TYPE_VECTOR:
			//me mataste con este
			break;
		default:
			LogInfo("Declare Type not found");
			break;
	}
	
}

void GeneratorAssignation(Assignation* assignation){
	write(" ");
	GeneratorVariable(assignation->variable);
	write(" = ");
	GeneratorExpression(assignation->Expression);
	write(" ; ");
}

void GeneratorFunction(Function* function){
	//aca hay que hacer otro switch para diferenciar a las funciones por token
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
	//no entiendo que hace esta

}

void GeneratorWrite(Write* write){
	//no entiendo que hace esta
}

void GeneratorIfClose(IfClose* ifClose){
	switch (ifClose->type)
	{
		case IF_CLOSE_NORMAL:
			write(" } ");
			break;
		case IF_ELSE:
			write("} else{ ");
			GeneratorBlock(ifClose->block);
			write(" }");
			break;
		default:
			LogInfo("IfClose Type not found");
			break;
	}
}

void GeneratorIf(If* ifInstruction){
	write(" if( ");
	GeneratorExpression(ifInstruction->expression);
	write(" ){ ");
	GeneratorBlock(ifInstruction->block);
	GeneratorIfClose(ifInstruction->ifClose);
	
}

void GeneratorWhile(While* whileInstruction){
	write(" while(");
	GeneratorExpression(whileInstruction->expression);
	write(" ){ ");
	GeneratorBlock(whileInstruction->block);
	write(" } ");
}

void GeneratorFor(For* forInstruction){
	write("for( ");
	switch (forInstruction->type)
	{
		case DECLARE_ASSIGN_FOR:
			GeneratorDeclareAndAssign(forInstruction->declareAndAssign);
			write(" ; ");
			GeneratorExpression(forInstruction->expression);
			break;
		case ASSIGNATION_FOR:
			GeneratorAssignation(forInstruction->assignation);
			write(" ; ");
			GeneratorExpression(forInstruction->expression);
	
			break;
		case INCOMPLETE_FOR:
			write(" ; ");
			GeneratorExpression(forInstruction->expression);
			break;
		default:
			LogInfo("For Type not found");
			break;
	}
	write(" ; ");
	GeneratorStatement(forInstruction->statement);
	write(" ){ ");
	GeneratorBlock(forInstruction->block);
	write(" }");
}

void GeneratorExpression(Expression* expression){
	switch (expression->type)
	{
		case ADD_EXPRESSION:
			GeneratorExpression(expression->left);
			write(" + ");
			GeneratorExpression(expression->right);
			break;
		case SUB_EXPRESSION:
			GeneratorExpression(expression->left);
			write(" - ");
			GeneratorExpression(expression->right);
			break;
		case MUL_EXPRESSION:
			GeneratorExpression(expression->left);
			write(" * ");
			GeneratorExpression(expression->right);
			break;
		case DIV_EXPRESSION:
			GeneratorExpression(expression->left);
			write(" / ");
			GeneratorExpression(expression->right);
			break;
		case FACTOR_EXPRESSION:
			GeneratorFactor(expression->factor);
		case GT_EXPRESSION:
			GeneratorExpression(expression->left);
			write(" > ");
			GeneratorExpression(expression->right);
			break;
		case GE_EXPRESSION:
			GeneratorExpression(expression->left);
			write(" >= ");
			GeneratorExpression(expression->right);
			break;
		case LE_EXPRESSION:
			GeneratorExpression(expression->left);
			write(" <= ");
			GeneratorExpression(expression->right);
			break;
		case LT_EXPRESSION:
			GeneratorExpression(expression->left);
			write(" < ");
			GeneratorExpression(expression->right);
			break;
		case NE_EXPRESSION:
			GeneratorExpression(expression->left);
			write(" != ");
			GeneratorExpression(expression->right);
			break;
		case EQ_EXPRESSION:
			GeneratorExpression(expression->left);
			write(" == ");
			GeneratorExpression(expression->right);
			break;
		case NOT_EXPRESSION:
			write(" ! ");
			GeneratorExpression(expression->right);
			break;
			break;	
		case FUNCTION_EXPRESSION:
			GeneratorFunction(expression->function);
			break;	
		case VECTOR_EXPRESSION:
			GeneratorVector(expression->vector);
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
			GeneratorConstant(factor->constant);
			break;
		case STRING_FACTOR:
			write(factor->string);
			break;
		case SYMBOL_FACTOR:
			GeneratorVariable(factor->variable);
			break;
		case EXPRESSION_FACTOR:
			GeneratorExpression(factor->expression);
			break;
		default:
			LogInfo("Factor Type not found");
			break;
	}
}

void GeneratorConstant(Constant* constant){
	//char*?
	write(constant->value);

}

void GeneratorVector(Vector* vector){
	GeneratorVariable(vector->variable);
	write("[");
	switch (vector->type)
	{
		case CONSTANT_VECTOR:

			GeneratorConstant(vector->constant);
			break;
		case SYMBOL_VECTOR:
			GeneratorVariable(vector->variable2);
			break;
		default:
			LogInfo("Vector Type not found");
			break;
	}
	write("]");
}

void GeneratorParameterList(ParameterList* parameterList){
	switch (parameterList->type)
	{
		case EXPRESSION:
			GeneratorExpression(parameterList->expression);
			break;
		case PARAM_COMMA_EXPRESSION:
			GeneratorExpression(parameterList->expression);
			write(" , ");
			GeneratorParameterList(parameterList->parameterList)
			break;

		default:
			LogInfo("ParameterList Type not found");
			break;
	}
}

void GeneratorVariable(char* variable){
	write(variable);
}
