#include <stdio.h>
#include <stdlib.h>
typedef struct treeCDT * treeADT;
typedef struct node *t_node;
typedef int elemType; // Tipo de elemento a insertar
struct node
{
    char *node_name;
    elemType elem;
    size_t currentHeight;
    struct node *rightSon;
    struct node *leftSon;

};

struct treeCDT{
    t_node first;
    size_t size;
    size_t maxHeight;
};

treeADT newTree();
unsigned int addBinary(treeADT tree, elemType elem,char *node_name);
t_node binarySearch(t_node root,char *node_name, elemType elem);
void printLeftChild(t_node list) ;
void printRightChild(t_node list) ;
void printRec(t_node list);
void multiplyTree(treeADT tree, int value);