#ifndef BISON_ACTIONS_HEADER
#define BISON_ACTIONS_HEADER

#include "../../backend/support/shared.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef enum node_type 
{
  	STRING_NODE,
    INTEGER_NODE,
    OPERATION_NODE,
    TREE_NODE,
    VARIABLE_NODE,
    IF_NODE,
    WHILE_NODE,
    FOR_NODE,
    WRITE_NODE,
    READ_NODE,
    BLOCK_NODE,
    INSTRUCTION_NODE,
    EXPRESSION_NODE,
    RETURN_NODE
} node_type;

typedef struct node_t
{
    node_type type;
    void * open;
    struct node_t *next_1;
    struct node_t *next_2;
    struct node_t *next_3;
} node_t;

typedef struct variable_node_t
{
    node_type type;
    int is_declared;
    int is_constant;
    int var_type;
    char *name;
    node_t *value;
} variable_node_t;

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


node_t *add_generic_node(node_type node_type, char * open, node_t * next_1, node_t * next_2, node_t * next_3);
node_t *add_string_node(char * string_text);
node_t *add_integer_node(char * integer);
node_t *add_if_node(node_t * condition, node_t * block, node_t * else_condition);
node_t *add_while_node(node_t * condition, node_t * block);
node_t *add_return_node(node_t * expression);
node_t *add_block_node(node_t * list);
node_t *add_instruction_node(node_t * node);
node_t *add_write_node(node_t * content);
node_t *add_read_node(node_t * content);
node_t *add_expression_node(node_t * node_1, node_t * node_2, node_t * node_3);
node_t *add_instruction_list_node(node_t * node);
node_t *add_operation_node(char * operation);
node_t *new_declare_constant_variable_node(char * name, int var_type);
node_t *new_declare_variable_node(char * name, int var_type);
node_t *assign_value_variable_node(char * name, node_t * expression);
node_t *add_value_variable_node(node_t *past_node, node_t *expression);
node_t *add_variable_reference(char *name);
node_t *add_element_to_list(node_t *list, node_t *element);

#endif
