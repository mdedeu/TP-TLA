#include "binary-treeCDT.h"

/* Retorna un nuevo multiSet de elementos genéricos. Al inicio está vacío */
binaryTreeADT newMultiSet()
{
    return calloc(1,sizeof(struct binaryTreeCDT));
}
static int compare (elemType e1, elemType e2) {
    return e1-e2;
}
t_node addRec(t_node node, elemType elem, size_t *size, size_t *count)
{
    int c;
    //if it is a greater element it is a greater element, it is a right child
    if(node==NULL||(c=compare(node->elem,elem))<0)
    {
        //t_node aux=malloc(sizeof(struct node));
        //(*size)++;
        //aux->elem=elem;
        //aux->tail=node;
        //aux->count=1;
        //*count=1;
        //return aux;
    }
    if(c==0)
    {
        //node->count++;
        //*count=node->count;
        return node;
    }
    //node->tail=addRec(node->tail,elem,size,count);
    return node;
}