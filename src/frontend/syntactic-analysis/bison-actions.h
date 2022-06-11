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
int ProgramGrammarAction();

// Expresión.
int AdditionExpressionGrammarAction(const int leftValue, const int rightValue);
int SubtractionExpressionGrammarAction(const int leftValue, const int rightValue);
int MultiplicationExpressionGrammarAction(const int leftValue, const int rightValue);
int DivisionExpressionGrammarAction(const int leftValue, const int rightValue);
int FactorExpressionGrammarAction(const int value);

// Factores.
int ExpressionFactorGrammarAction(const int value);
int ConstantFactorGrammarAction(const int value);

// Constantes.
int IntegerConstantGrammarAction(const int value);

//Comparaciones expresión
int GreaterExpressionGrammarAction();
int GreaterOrEqualExpressionGrammarAction();
int LesserOrEqualExpressionGrammarAction();
int LesserExpressionGrammarAction();
int NotEqualExpressionGrammarAction();
int EqualExpressionGrammarAction();

//Bloque
int BlockGrammarAction();

//Instrucción
int InstructionsGrammarAction();

//Declaración (statement)
int StatementsGrammarAction();

//Declararción
int DeclareAndAssignGrammarAction();
int DeclareGrammarAction();

//Asignación
int AssignationGrammarAction();

//Función
int NoParamFunctionGrammarAction();
int OneParamFunctionGrammarAction();
int MultiParamFunctionGrammarAction();
int ExpressionFunctionGrammarAction();
int ReadFunctionGrammarAction();
int WriteFunctionGrammarAction();

//Bloques de control
int IfGrammarAction();
int ForGrammarAction();
int WhileGrammarAction();

//Vector
int VectorGrammarAction();

#endif
