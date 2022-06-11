#ifndef BISON_ACTIONS_HEADER
#define BISON_ACTIONS_HEADER

#include "../../backend/support/shared.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

/**
 * Se definen las acciones a ejecutar sobre cada regla de producción de la
 * gramática. El objetivo de cada acción debe ser el de construir el nodo
 * adecuado que almacene la información requerida en el árbol de sintaxis
 * abstracta (i.e., el AST).
 */

// Programa.
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
#endif
