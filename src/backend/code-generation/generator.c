#include "../support/logger.h"
#include "generator.h"
#include "../semantic-analysis/symbol-table.h"

/**
 * Implementación de "generator.h".
 */


int scanner = 0;

void GeneratorProgram(MainProgram* program, FILE * out) {
	GeneratorBlock(program->block, out);
	fprintf(out,"	}\n");
	fprintf(out,"}");
}

void GeneratorBlock(Block* block, FILE * output){
	LogDebug("Generating block..");
	switch (block->type)
	{
		case INSTRUCTION_BLOCK:
			GeneratorInstruction(block->instruction, output);
			GeneratorBlock(block->block, output);
			break;
		case INSTRUCTION:
			GeneratorInstruction(block->instruction, output);
			break;

		default:
			LogInfo("Block Type not found");
			break;
	}
	
}

void GeneratorInstruction(Instruction* instruction, FILE * output){
	LogDebug("Generating instruction...");
	switch (instruction->type)
	{
		case STATEMENT_INSTRUCTION:
			fprintf(output,"		");
			GeneratorStatement(instruction->statement, output);
			fprintf(output,";\n");
			break; 
		case IF_INSTRUCTION:
			GeneratorIf(instruction->if_instruction, output);
			break;
		case FOR_INSTRUCTION:
			GeneratorFor(instruction->for_instruction, output);
			break;
		case WHILE_INSTRUCTION:
			GeneratorWhile(instruction->while_instruction, output);
			break;
		default:
			LogInfo("Instruction Type not found");
			break;
	}
}

void GeneratorStatement(Statement* statement, FILE * output){
	LogDebug("Generating statement...");
	switch (statement->type)
	{
		case DECLARE_AND_ASSIGN:
			GeneratorDeclareAndAssign(statement->declareAndAssign, output);
			break;
		case ASSIGNATION:
			GeneratorAssignation(statement->assignation, output);
			break;
		case FUNCTION:
			GeneratorFunction(statement->function, output);
			break;
		default:
			LogInfo("Statement Type not found");
			break;
	}
}

void GeneratorDeclareAndAssign(DeclareAndAssign* declareAndAssign, FILE * output){
	GeneratorDeclare(declareAndAssign->declare, output);
	LogDebug("Generating DeclareAndAssign...");
	switch (declareAndAssign->type)
	{
		case DECLARE_ASSIGN_EXPRESSION:
			LogDebug("DeclareAndAssign -> expression");
			fprintf(output," = ");
			GeneratorExpression(declareAndAssign->expression, output);
			break;
		case DECLARE_ASSIGN_PARAM_LIST:
			LogDebug("DeclareAndAssign -> paramList");
			fprintf(output," = {");
			GeneratorParameterList(declareAndAssign->parameterList, output);
			fprintf(output," }");
			break;
		case ONLY_DECLARE:
			if(declareAndAssign->declare->type == TREE_TYPE_SYMBOL) {
				fprintf(output," = new ");
				switch (declareAndAssign->declare->treeType_token->value)
				{
					case AVL_TREE_TYPE:
						fprintf(output,"%s", "AVLTree<>()");
						break;
					case RED_BLACK_TREE_TYPE:
						fprintf(output,"%s", "RedBlackTree<>()");
						break;
					case BST_TREE_TYPE:
						fprintf(output,"%s", "BSTree<>()");
						break;
				}
				break;
			}
		default:
			LogInfo("DeclareAndASsign Type not found");
			break;
	}
}


void GeneratorDeclare(Declare* declare, FILE * output){
	LogDebug("Generating declare...");
	switch (declare->type)
	{
		case TYPE_SYMBOL:
			LogDebug("Declare type symbol");
			if(declare->type_token->value == INT_TYPE) {
				LogDebug("Declare type symbol -> int");
				fprintf(output,"%s", "Integer");
			}
			else if(declare->type_token->value == STRING_TYPE) {
				LogDebug("Declare type symbol -> String");
				fprintf(output,"%s", "String");
			}
			fprintf(output," %s",declare->variable);
			break;
		case TREE_TYPE_SYMBOL:
			LogDebug("Declare tree type symbol");
			switch (declare->treeType_token->value)
			{
				case AVL_TREE_TYPE:
					fprintf(output,"%s", "AVLTree<");
					break;
				case RED_BLACK_TREE_TYPE:
					fprintf(output,"%s", "RedBlackTree<");
					break;
				case BST_TREE_TYPE:
					fprintf(output,"%s", "BSTree<");
					break;
			}

			if(declare->type_token->value == INT_TYPE) {
				LogDebug("Declare tree type symbol -> int");
				fprintf(output,"Integer>");
			}
			else if(declare->type_token->value == STRING_TYPE) {
				LogDebug("Declare tree type symbol -> string");
				fprintf(output,"String>");
			}
			fprintf(output," %s",declare->variable);
			break;
		case TYPE_VECTOR:
			LogDebug("Declare type vector");
			if(declare->type_token->value == INT_TYPE) {
				LogDebug("Declare type vector -> int");
				fprintf(output,"%s", "Integer");
			}
			else if(declare->type_token->value == STRING_TYPE) {
				LogDebug("Declare type vector -> string");
				fprintf(output,"%s", "String");
			}	
			fprintf(output," %s[]",declare->variable);
			break;
		default:
			LogInfo("Declare Type not found");
			break;
	}
	
}

void GeneratorAssignation(Assignation* assignation, FILE * output){
	LogDebug("Generating assignation...");
	fprintf(output, "%s", assignation->variable);
	fprintf(output, " = ");
	GeneratorExpression(assignation->Expression, output);
}

void GeneratorFunction(Function* function, FILE * output){
	switch (function->type)
	{
		case NO_PARAM_FUNCTIONS:
			switch(function->noParamFunctionToken->value) {
					case PRINT:
						fprintf(output,"%s.print()",function->variable);
						break;
					case LENGTH:
						fprintf(output,"%s.size()",function->variable);
						break;
					case BALANCED:
						fprintf(output,"%s.balanced()",function->variable);
						break;
			}
			break;
		case ONE_PARAM_FUNCTIONS:
			switch(function->oneParamFunctionToken->value) {
				case NEW_NODE:
					fprintf(output,"%s.addNode(",function->variable);
					GeneratorExpression(function->expression, output);
					fprintf(output,")");
					break;
				case DELETE_NODE:
					fprintf(output,"%s.deleteNode(",function->variable);
					GeneratorExpression(function->expression, output);
					fprintf(output,")");
					break;
				case TREE_MULT:
					fprintf(output,"%s.mul(",function->variable);
					GeneratorExpression(function->expression, output);
					fprintf(output,")");
					break;
				case FILTER:
					fprintf(output,"%s.filter(",function->variable);
					GeneratorExpression(function->expression, output);
					fprintf(output,")");
					break;
			}
			break;
		case READ_FUNCTION:
			GeneratorRead(function->read, output);
			break;
		case WRITE_FUNCTION:
			GeneratorWrite(function->write, output);
			break;
		default:
			LogInfo("Function Type not found");
			break;
	}
}

void GeneratorRead(Read* read, FILE * output){
	if(!scanner) {
		scanner = 1;
		fprintf(output,"Scanner sc= new Scanner(System.in)");
	}
	Variable * var = symbol_table_get(read->variable);
	if(var->type->value == STRING_TYPE)
		fprintf(output, "%s = sc.nextLine()", read->variable);
	else {
		fprintf(output, "%s = sc.nextInt()", read->variable);
	}
}

void GeneratorWrite(Write* write, FILE * output){
	fprintf(output,"System.out.println(");
	GeneratorExpression(write->expression, output);
	fprintf(output,")");
}

void GeneratorIfClose(IfClose* ifClose, FILE * output){
	LogDebug("Generating if close...");
	switch (ifClose->type)
	{
		case IF_CLOSE_NORMAL:
			fprintf(output," } ");
			break;
		case IF_ELSE:
			fprintf(output,"} else { ");
			GeneratorBlock(ifClose->block, output);
			fprintf(output," }");
			break;
		default:
			LogInfo("IfClose Type not found");
			break;
	}
}

void GeneratorIf(If* ifInstruction, FILE * output){
	LogDebug("Generating if...");
	fprintf(output," if( ");
	GeneratorExpression(ifInstruction->expression, output);
	fprintf(output," ){ ");
	GeneratorBlock(ifInstruction->block, output);
	GeneratorIfClose(ifInstruction->ifClose, output);
}

void GeneratorWhile(While* whileInstruction, FILE * output){
	LogDebug("Generating while...");
	fprintf(output," while(");
	GeneratorExpression(whileInstruction->expression, output);
	fprintf(output," ){ ");
	GeneratorBlock(whileInstruction->block, output);
	fprintf(output," } ");
}

void GeneratorFor(For* forInstruction, FILE * output){
	LogDebug("Generating for...");
	fprintf(output,"for(");
	switch (forInstruction->type)
	{
		case DECLARE_ASSIGN_FOR:
			GeneratorDeclareAndAssign(forInstruction->declareAndAssign, output);
			break;
		case ASSIGNATION_FOR:
			GeneratorAssignation(forInstruction->assignation, output);
			break;
		case INCOMPLETE_FOR:
			break;
		default:
			LogInfo("For Type not found");
			break;
	}
	fprintf(output," ; ");
	GeneratorExpression(forInstruction->expression, output);
	fprintf(output," ; ");
	GeneratorStatement(forInstruction->statement, output);
	fprintf(output," ){ ");
	GeneratorBlock(forInstruction->block, output);
	fprintf(output," }");
}

void GeneratorExpression(Expression* expression, FILE * output){
	LogDebug("Generating expression...");
	switch (expression->type)
	{
		case ADD_EXPRESSION:
			LogDebug("Expression -> ADD");
			GeneratorExpression(expression->left, output);
			fprintf(output," + ");
			GeneratorExpression(expression->right, output);
			break;
		case SUB_EXPRESSION:
			LogDebug("Expression -> ADD");
			GeneratorExpression(expression->left, output);
			fprintf(output," - ");
			GeneratorExpression(expression->right, output);
			break;
		case MUL_EXPRESSION:
			LogDebug("Expression -> MUL");
			GeneratorExpression(expression->left, output);
			fprintf(output," * ");
			GeneratorExpression(expression->right, output);
			break;
		case DIV_EXPRESSION:
			LogDebug("Expression -> DIV");
			GeneratorExpression(expression->left, output);
			fprintf(output," / ");
			GeneratorExpression(expression->right, output);
			break;
		case FACTOR_EXPRESSION:
			LogDebug("Expression -> FACTOR");
			GeneratorFactor(expression->factor, output);
			break;
		case GT_EXPRESSION:
			LogDebug("Expression -> GT");
			GeneratorExpression(expression->left, output);
			fprintf(output," > ");
			GeneratorExpression(expression->right, output);
			break;
		case GE_EXPRESSION:
			LogDebug("Expression -> GE");
			GeneratorExpression(expression->left, output);
			fprintf(output," >= ");
			GeneratorExpression(expression->right, output);
			break;
		case LE_EXPRESSION:
			LogDebug("Expression -> LE");
			GeneratorExpression(expression->left, output);
			fprintf(output," <= ");
			GeneratorExpression(expression->right, output);
			break;
		case LT_EXPRESSION:
			LogDebug("Expression -> LT");
			GeneratorExpression(expression->left, output);
			fprintf(output," < ");
			GeneratorExpression(expression->right, output);
			break;
		case NE_EXPRESSION:
			LogDebug("Expression -> NE");
			GeneratorExpression(expression->left, output);
			fprintf(output," != ");
			GeneratorExpression(expression->right, output);
			break;
		case EQ_EXPRESSION:
			LogDebug("Expression -> EQ");
			GeneratorExpression(expression->left, output);
			fprintf(output," == ");
			GeneratorExpression(expression->right, output);
			break;
		case NOT_EXPRESSION:
			LogDebug("Expression -> NOT");
			fprintf(output," ! ");
			GeneratorExpression(expression->right, output);
			break;
			break;	
		case FUNCTION_EXPRESSION:
			LogDebug("Expression -> FUNCTION");
			GeneratorFunction(expression->function, output);
			break;	
		case VECTOR_EXPRESSION:
			LogDebug("Expression -> VECTOR");
			GeneratorVector(expression->vector, output);
			break;
		default:
			LogInfo("Expression Type not found");
			break;
	}

}


void GeneratorFactor(Factor* factor, FILE * output){
	LogDebug("Generating factor...");
	switch (factor->type)
	{
		case CONSTANT_FACTOR:
			LogDebug("Factor -> CONSTANT");
			GeneratorConstant(factor->constant, output);
			break;
		case STRING_FACTOR:
			LogDebug("Factor -> STRING");
			fprintf(output,"%s",factor->string);
			break;
		case SYMBOL_FACTOR:
			LogDebug("Factor -> SYMBOL");
			fprintf(output,"%s",factor->variable);
			break;
		case EXPRESSION_FACTOR:
			LogDebug("Factor -> EXPRESSION");
			GeneratorExpression(factor->expression, output);
			break;
		default:
			LogInfo("Factor Type not found");
			break;
	}
}

void GeneratorConstant(Constant* constant, FILE * output){
	LogDebug("Generating constant...");
	fprintf(output,"%d",constant->value);
}

void GeneratorVector(Vector* vector, FILE * output){
	LogDebug("Generating vector...");
	fprintf(output,"[");
	GeneratorFactor(vector->factor, output);
	fprintf(output,"]");
}

void GeneratorParameterList(ParameterList* parameterList, FILE * output){
	LogDebug("Generating parameterList...");
	switch (parameterList->type)
	{
		case EXPRESSION:
			GeneratorExpression(parameterList->expression, output);
			break;
		case PARAM_COMMA_EXPRESSION:
			GeneratorParameterList(parameterList->parameterList, output);
			fprintf(output," , ");
			GeneratorExpression(parameterList->expression, output);
			break;
		default:
			LogInfo("ParameterList Type not found");
			break;
	}
}

