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

node_t *add_generic_node(node_type node_type, char * open, node_t * next_1, node_t * next_2, node_t * next_3)
{
    node_t * node = malloc(sizeof(node_t));
    if (node == NULL)
    {
        printf("Malloc error");
        return NULL;
    }
    if (open != NULL)
    {
        node->open = malloc(strlen(open) + 1);
        if (node->open == NULL)
        {
            free(node);
            printf("Malloc error");
            return NULL;
        }
        strcpy(node->open, open);
    }
    else
    {
        node->open = NULL;
    }
    node->type = node_type;
    node->next_1 = next_1;
    node->next_2 = next_2;
    node->next_3 = next_3;
    return node;
}

node_t *add_string_node(char * string_text)
{
    return add_generic_node(STRING_NODE, string_text, NULL, NULL, NULL);
}

node_t *add_integer_node(char * integer)
{
    return add_generic_node(INTEGER_NODE, integer, NULL, NULL, NULL);
}

node_t *add_if_node(node_t * condition, node_t * block, node_t * else_condition)
{
    return add_generic_node(IF_NODE, NULL, condition, block, else_condition);
}

node_t *add_while_node(node_t * condition, node_t * block)
{
    return add_generic_node(WHILE_NODE, NULL, condition, block, NULL);
}

node_t *add_block_node(node_t * list)
{
    return add_generic_node(BLOCK_NODE, NULL, list, NULL, NULL);
}

node_t *add_instruction_node(node_t * node)
{
    return add_generic_node(INSTRUCTION_NODE, NULL, node, NULL, NULL);
}

node_t *add_write_node(node_t * content)
{
    return add_generic_node(WRITE_NODE, NULL, content, NULL, NULL);
}

node_t *add_read_node(node_t * content)
{
    return add_generic_node(READ_NODE, NULL, content, NULL, NULL);
}

node_t *add_expression_node(node_t * node_1, node_t * node_2, node_t * node_3)
{
    return add_generic_node(EXPRESSION_NODE, NULL, first, second, third);
}

node_t *add_instruction_list_node(node_t * node)
{
    return add_generic_node(INSTRUCTION_NODE, NULL, node, NULL, NULL);
}

node_t *add_operation_node(char * operation)
{
    return add_generic_node(OPERATION_NODE, operation, NULL, NULL, NULL);
}

node_t *new_declare_constant_variable_node(char * name, int var_type)
{
    node_t * to_return = new_variable_node(name, var_type);
    ((variable_node *)to_return)->is_constant = TRUE;
    return to_return;
}

node_t *new_declare_variable_node(char * name, int var_type)
{
    variable_node * node = calloc(1, sizeof(variable_node));
    if (node == NULL)
    {
        printf("Calloc error");
        return NULL;
    }
    node->type = VARIABLE_NODE;
    node->name = malloc(strlen(name) + 1);
    if (node->name == NULL)
    {
        free(node);
        printf("Malloc error");
        return NULL;
    }
    node->var_type = var_type;
    node->is_declared = TRUE;
    node->is_constant = FALSE;
    strcpy(node->name, name);

    return (node_t *)node;
}

node_t *assign_value_variable_node(char * name, node_t * expression)
{
    variable_node *node = calloc(1, sizeof(variable_node));
    if (node == NULL)
    {
        printf("Calloc error");
        return NULL;
    }
    node->type = VARIABLE_NODE;
    node->name = malloc(strlen(name) + 1);
    if (node->name == NULL)
    {
        free(node);
        printf("Malloc error");
        return NULL;
    }
    node->declared = FALSE;
    node->value = expression;
    strcpy(node->name, name);

    return (node_t *)node;
}

node_t *add_value_variable_node(node_t *past_node, node_t *expression)
{
    variable_node * var_node = (variable_node *)past_node;
    variable_node * node = malloc(sizeof(variable_node));
    if (node == NULL)
    {
        printf("Malloc error");
        return NULL;
    }
    node->name = malloc(strlen(var_node->name) + 1);
    if (node->name == NULL)
    {
        free(node);
        printf("Malloc error");
        return NULL;
    }
    strcpy(node->name, var_node->name);
    node->value = expression;
    node->declared = TRUE;
    node->type = VARIABLE_NODE;
    node->var_type = var_node->var_type;
    node->is_constant = var_node->is_constant;

    free(var_node->name);
    free(var_node);
    return (node_t *)node;
}

node_t *add_variable_reference(char *name)
{
    variable_node *node = calloc(1, sizeof(variable_node));
    if (node == NULL)
    {
        printf("Malloc error");
        return NULL;
    }
    node->name = malloc(strlen(name) + 1);
    if (node->name == NULL)
    {
        free(node);
        printf("Malloc error");
        return NULL;
    }
    strcpy(node->name, name);
    node->declared = FALSE;
    node->type = VARIABLE_NODE;

    return (node_t *)node;
}

node_t *add_element_to_list(node_t *list, node_t *element)
{
    if (element == NULL)
    {
        return (node_t *)list;
    }

    node_t *current_node = list;

    if (current_node->next_1 == NULL)
    {
        free(list);
        return (node_t *)element;
    }
    else if (element != NULL)
    {
        element->next_2 = current_node;
    }

    return (node_t *)element;
}




