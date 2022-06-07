#IFNDEF _NODES_H
#DEFINE _NODES_H

typedef enum{
  	STRING_NODE,
    INTEGER_NODE,
    OPERATION_NODE, //Acá deberíamos hacer Un node por cada op?
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
} nodeType;

typedef struct node_t
{
    node_type type;
    void *meta;
    void *meta2;
    struct node_t *next_1;
    struct node_t *next_2;
    struct node_t *next_3;

} node_t;

typedef struct variable_node
{
    node_type type;
    int declared;
    int is_constant;
    int var_type;
    char *name;
    node_t *value;
} variable_node;



#ENDIF