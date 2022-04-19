#include "../../backend/domain-specific/calculator.h"
#include "../../backend/support/logger.h"
#include "bison-actions.h"
#include <stdio.h>
#include <string.h>

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

int ProgramGrammarAction() {
	LogDebug("ProgramGrammarAction(0)");
	state.succeed = true;
	return 0;
}

int AdditionExpressionGrammarAction(const int leftValue, const int rightValue) {
	LogDebug("AdditionExpressionGrammarAction(%d, %d)", leftValue, rightValue);
	return Add(leftValue, rightValue);
}

int SubtractionExpressionGrammarAction(const int leftValue, const int rightValue) {
	LogDebug("SubtractionExpressionGrammarAction(%d, %d)", leftValue, rightValue);
	return Subtract(leftValue, rightValue);
}

int MultiplicationExpressionGrammarAction(const int leftValue, const int rightValue) {
	LogDebug("MultiplicationExpressionGrammarAction(%d, %d)", leftValue, rightValue);
	return Multiply(leftValue, rightValue);
}

int DivisionExpressionGrammarAction(const int leftValue, const int rightValue) {
	LogDebug("DivisionExpressionGrammarAction(%d, %d)", leftValue, rightValue);
	return Divide(leftValue, rightValue);
}

int FactorExpressionGrammarAction(const int value) {
	LogDebug("FactorExpressionGrammarAction(%d)", value);
	return value;
}

int ExpressionFactorGrammarAction(const int value) {
	LogDebug("ExpressionFactorGrammarAction(%d)", value);
	return value;
}

int ConstantFactorGrammarAction(const int value) {
	LogDebug("ConstantFactorGrammarAction(%d)", value);
	return value;
}

int IntegerConstantGrammarAction(const int value) {
	LogDebug("IntegerConstantGrammarAction(%d)", value);
	return value;
}

int GreaterExpressionGrammarAction() {
	LogDebug("GreaterExpressionGrammarAction()");
	return 1;
}
int GreaterOrEqualExpressionGrammarAction() {
	LogDebug("GreaterOrEqualExpressionGrammarAction()");
	return 1;
}
int LesserOrEqualExpressionGrammarAction() {
	LogDebug("LesserOrEqualExpressionGrammarAction()");
	return 1;
}
int LesserExpressionGrammarAction() {
	LogDebug("LesserExpressionGrammarAction()");
	return 1;
}
int NotEqualExpressionGrammarAction() {
	LogDebug("NotEqualExpressionGrammarAction()");
	return 1;
}
int EqualExpressionGrammarAction() {
	LogDebug("EqualExpressionGrammarAction()");
	return 1;
}

int BlockGrammarAction() {
	LogDebug("BlockExpressionGrammarAction()");
	return 1;
}

int InstructionsGrammarAction() {
	LogDebug("InstructionsGrammarAction()");
	return 1;
}

int StatementsGrammarAction() {
	LogDebug("StatementsGrammarAction()");
	return 1;
}

int DeclareAndAssignGrammarAction() {
	LogDebug("DeclareAndAssignGrammarAction()");
	return 1;
}

int DeclareGrammarAction() {
	LogDebug("DeclareGrammarAction()");
	return 1;
}

int AssignationGrammarAction() {
	LogDebug("AssignationGrammarAction()");
	return 1;
}

int NoParamFunctionGrammarAction() {
	LogDebug("NoParamFunctionGrammarAction()");
	return 1;
}

int OneParamFunctionGrammarAction() {
	LogDebug("OneParamFunctionGrammarAction()");
	return 1;
}

int MultiParamFunctionGrammarAction() {
	LogDebug("MultiParamFunctionGrammarAction()");
	return 1;
}

int ExpressionFunctionGrammarAction() {
	LogDebug("ExpressionFunctionGrammarAction()");
	return 1;
}

int IfGrammarAction() {
	LogDebug("IfGrammarAction()");
	return 1;
}

int ForGrammarAction() {
	LogDebug("ForGrammarAction()");
	return 1;
}

int WhileGrammarAction() {
	LogDebug("WhileGrammarAction()");
	return 1;
}

int VectorGrammarAction() {
	LogDebug("VectorGrammarAction()");
	return 1;
}

int ReadFunctionGrammarAction() {
	LogDebug("ReadFunctionGrammarAction()");
	return 1;
}


int WriteFunctionGrammarAction() {
	LogDebug("WriteFunctionGrammarAction()");
	return 1;
}



