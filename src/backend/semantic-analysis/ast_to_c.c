#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "y.tab.h"
#include "ast_to_c.h"
$include "../../frontend/syntactic-analysis/bison-actions.h"


FILE * output;

//check functions, free memory etc

#define PRINT(...) fprintf(output, ##__VA_ARGS__);

void ast_to_c(node_t * program, FILE * file)
{
    output = file;
    instructions_to_c(program);
    //free tree
}

void switch_expresion_to_c(node_t * node)
{
    switch (node->type)
    {
    case EXPRESSION_NODE:
        expresion_to_c(node);
        break;
    case VARIABLE_NODE:
        variable_node *var = (variable_node *)node;
        PRINT(" %s ", var->name);
        free(var->name);
        break;
    case STRING_NODE:
    case INTEGER_NODE:
    case OPERATION_NODE:
        PRINT(" %s ", (char *)node->open);
        free(node->open);
        break;
    default:
        break;
    }
}

void expression_to_c(node_t * expression)
{
    if (expression->type == VARIABLE_NODE)
    {
        switch_expresion_to_c(expression);
        return ;
    }
    int integer = 0;
    if (expression && expression->next_2 && expression->next_2->open)
    {
        char * open_str = (char *)expression->next_2->open;
        integer = strcmp(open_str, "%") == 0;
    }
    if (expression->next_1 != NULL)
    {
        if (integer)
            PRINT("(int)");
        switch_expresion_to_c(expression->next_1);
        free(expression->next_1);
    }

    if (expression->next_2 != NULL)
    {
        switch_expresion_to_c(expression->next_2);
        free(expression->next_2);
    }

    if (expression->next_3 != NULL)
    {
        if (integer)
            PRINT("(int)");
        switch_expresion_to_c(expression->next_3);
        free(expression->next_3);
    }
}

void instructions_to_c(node_t * instructions)
{
    node_t * aux = instructions;
    while (aux != NULL)
    {
        node_t * current = aux->next_1;
        switch (current->type)
        {
        case VARIABLE_NODE:
            variable_to_c(current);
            break;
        case WRITE_NODE:
            write_to_c(current);
            break;
        case READ_NODE:
            read_to_c(current);
            break;
        case IF_NODE:
            if_to_c(current);
            break;
        case WHILE_NODE:
            while_to_c(current);
            break;
        default:
            break;
        }
        free(current);
        node_t * next = aux->next_2;
        free(aux);
        aux = next;
    }
}


void if_to_c(node_t * node)
{
    //check free
    PRINT("if (");
    expression_to_c(node->next_1);
    free(node->next_1);
    PRINT(") {\n");
    node_t * block = node->next_2;
    instruction_list_to_c(block->next_1);
    free(block);
    if (node->next_3 != NULL)
    {
        PRINT("\n} else {\n");
        block = node->next_3;
        instruction_list_to_c(block->next_1);
        free(block);
    }
    PRINT("}\n");
}

void while_to_c(node_t *node)
{
    //check free
    PRINT("while (");
    expression_to_c(node->next_1);
    free(node->next_1);
    PRINT(") {\n");
    instruction_list_to_c(node->next_2->next_1);
    free(node->next_2);
    PRINT("}\n");
}

void for_to_c(node_t * node)
{
    //check free
    //hacerlo
}

void variable_to_c(node_t * node)
{
    variable_node * var = (variable_node *)node;

    if (var->declared == TRUE)
    {
        switch (var->var_type)
        {
        case INTEGER_TYPE:
            PRINT("int %s", var->name);
            break;
        case STRING_TYPE:
            PRINT("char * %s", var->name);
            break;
        default:
            break;
        }
    }
    else
    {
        PRINT("%s", (var->name));
    }
    free(var->name);

    if (var->value != NULL)
    {
        PRINT(" = ");
        if (var->var_type == INTEGER_TYPE)
            PRINT("(int)");

        if (var->value->type == EXPRESSION_NODE)
        {
            expresion_to_c(var->value);
        }
        else if (var->value->type == STRING_NODE || var->value->type == INTEGER_NODE)
        {
            PRINT("%s", (char *)var->value->open);
            free(var->value->open);
        }
        else if (var->value->type == VARIABLE_NODE)
        {
            variable_node *var_node = (variable_node *)var->value;
            PRINT("%s", var_node->name);
            free(var_node->name);
        }
        free(var->value);
    }
    PRINT(";\n");
}