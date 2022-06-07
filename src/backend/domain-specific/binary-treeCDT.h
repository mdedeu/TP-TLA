#include <stdio.h>
#include <stdlib.h>
typedef struct binaryTreeCDT * binaryTreeADT;
typedef struct node *t_node;
typedef int elemType; // Tipo de elemento a insertar
struct node
{
    elemType elem;
    size_t currentHeight;
    struct node *rightSon;
    struct node *leftSon;

};

struct binaryTreeCDT{
    t_node first;
    size_t size;
    size_t maxHeight;
};

binaryTreeADT newMultiSet();
