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


MainProgram * MainProgramGrammarAction(Block * block);
Block * InstructionBlockGrammarAction(Instruction * instruction, Block * block);
Block * BlockGrammarAction(Instruction * instruction);
Instruction * StatementInstructionGrammarAction(Statement * statement);
Instruction * IfInstructionGrammarAction(If * _if);
Instruction * ForInstructionGrammarAction(For * _for);
Instruction * WhileInstructionGrammarAction(While * _while);
Statement * DeclareAndAssignStatementGrammarAction(DeclareAndAssign * declareAndAssign);
Statement * AssignationStatementGrammarAction(Assignation * assignation);
Statement * FunctionStatementGrammarAction(Function * function);
DeclareAndAssign * DeclareAndAssignGrammarAction(Declare * declare, Expression * expression);
DeclareAndAssign * DeclareParameterListGrammarAction(Declare * declare, ParameterList * parameterList);
DeclareAndAssign * OnlyDeclareGrammarAction(Declare * declare);
Declare * TypeSymbolDeclareGrammarAction(int t_type, char * variable);
Declare * TreetypeTpyeSymbolDeclareGrammarAction(int t_tree_type, int t_type, char * variable);
Declare * TypeVectorDeclareGrammarAction(int t_type, Vector * vector);
Assignation * AssignationGrammarAction(char * variable, Expression * expression);
Function * NoParamFunctionGrammarAction(char * variable, int t_noparamfunction);
Function * OneParamFunctionGrammarAction(char * variable, int t_oneparamfunction, Expression * expression);
Function * MultiParamFunctionGrammarAction(char * variable, int t_multiparamfunction, ParameterList * parameterList);
Function * FilterFunctionGrammarAction(Expression * expression);
Function * ReadFunctionGrammarAction(Read * read);
Function * WriteFunctionGrammarAction(Write * write);
Read * ReadGrammarAction(char * variable);
Write * WriteGrammarAction(Expression * expression);
int NoParamGrammarAction(int token);
int OneParamGrammarAction(int token);
int MultiParamGrammarAction(int token);

//
If * IfGrammarAction(Expression * expression, Block * block);
IfClose* IfCloseNormalGrammarAction();
IfClose* IfCloseElseGrammarAction(Block* block);


While* WhileGrammarAction(Expression* expression, Block* block);


For* DeclareAndAssignForGrammarAction(DeclareAndAssign* declareAndAssign, Expression* expression, Statement* statement, Block* block);
For* AssignationForGrammarAction(Assignation* assignation,  Expression* expression, Statement* statement, Block* block);
For* IncompleteForGrammarAction( Expression* expression, Statement* statement, Block* block);




//Expresiones
Expression* AdditionExpressionGrammarAction(Expression* leftValue, Expression* rightValue);
Expression* SubtractionExpressionGrammarAction(Expression* leftValue, Expression* rightValue);
Expression* MultiplicationExpressionGrammarAction(Expression* leftValue, Expression* rightValue);
Expression* DivisionExpressionGrammarAction(Expression* leftValue, Expression* rightValue);

Expression* GreaterExpressionGrammarAction(Expression* leftValue, Expression* rightValue);
Expression* GreaterOrEqualExpressionGrammarAction(Expression* leftValue, Expression* rightValue);
Expression* LesserOrEqualExpressionGrammarAction(Expression* leftValue, Expression* rightValue);
Expression* LesserExpressionGrammarAction(Expression* leftValue, Expression* rightValue);
Expression* NotEqualExpressionGrammarAction(Expression* leftValue, Expression* rightValue);
Expression* EqualExpressionGrammarAction(Expression* leftValue, Expression* rightValue);
Expression* NotExpressionGrammarAction(Expression* expression);
Expression* FactorExpressionGrammarAction(Factor* factor);
Expression* FunctionExpressionGrammarAction(Function* function);
Expression* VectorExpressionGrammarAction(Vector* vector);



//Factor 
Factor* ExpressionFactorGrammarAction(const int value);
Factor* ConstantFactorGrammarAction(const int value);
Factor* SymbolFactorGrammarAction(const int value);
Factor* StringFactorGrammarAction(const int value);


//Constant
Constant* IntegerConstantGrammarAction(const int value);


//Vector
Vector* VectorConstantGrammarAction(char * symbol, Constant* constant);
Vector* VectorSymbolGrammarAction(char * symbol, char* symbol2);


ParameterList * ParameterListCommaExpressionGrammarAction(ParameterList * parameterList, Expression * expression);
ParameterList * ParameterListGrammarAction(Expression * expression);
//Types
int TypeGrammarAction(int token);
int TreeTypeGrammarAction(int token);

int SemiColonsGrammarAction(int token);