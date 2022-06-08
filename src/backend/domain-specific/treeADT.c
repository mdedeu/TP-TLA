#include "treeCDT.h"

/* Retorna un nuevo multiSet de elementos genéricos. Al inicio está vacío */
treeADT newTree()
{
    return calloc(1,sizeof(struct treeCDT));
}
static int compare (elemType e1, elemType e2) {
    return e1-e2;
}
//-----------------------NORMAL TREE------------------------//
unsigned int addRoot(treeADT tree, elemType elem,char *node_name){
    t_node aux=malloc(sizeof(struct node));
    aux->elem=elem;
    aux->currentHeight=0;
    aux->node_name=node_name;
    aux->leftSon=aux->rightSon=NULL;
    tree->first=aux;
    tree->size=1;
    return 1;
}
// unsigned int add(treeADT tree, elemType elem,char *node_name,char *parent_name){
//     size_t count;
//     //if(tree->)
//     tree->first=addRec(tree->first,elem,&tree->size,&count,*node_name);
//     return count;
// }

//--------------------------------------------------------//
//-------------------BINARY-------------------------------//
//function that finds the node and print its values

t_node binarySearchRec(t_node node,char *node_name,elemType elem){
    if(node==NULL){
        return NULL;
    }
    if(compare(node->elem,elem)<0){
        return binarySearchRec(node->rightSon,node_name, elem);    
    }
    if(compare(node->elem,elem)>0){
        return binarySearchRec(node->leftSon,node_name, elem);    
    }
        printf("node name:%s\nnode value:%d\n",node->node_name,node->elem);

    return node;
}
t_node binarySearch(t_node root,char *node_name, elemType elem){
    t_node aux=NULL;
    int c=compare(root->elem,elem);
    if(c==0){
        aux=root;
        printf("---------\n");
        printf("%s:    %d\n",node_name,root->elem);
        printf("---------\n");

    }else{
        if(c<0){            
            aux=binarySearchRec(root->rightSon,node_name, elem);        
        }else{
            aux=binarySearchRec(root->leftSon,node_name, elem);        
        }
    }
    return aux;
}


t_node addRecBinary(t_node node, elemType elem, size_t *size, size_t *count,char *node_name)
{
    int c;
    //if node is null it means we have to add our leaf
    if(node==NULL){
        t_node aux=malloc(sizeof(struct node));
        (*size)++;
        aux->node_name=node_name;
        aux->elem=elem;
        aux->rightSon=NULL;
        aux->leftSon=NULL;
        //aux->count=1;
        //*count=1;
        return aux;
    }
    //if it is a greater element it is a greater element, it is a right child
    if((c=compare(node->elem,elem))<0)
    {
        node->rightSon=addRecBinary(node->rightSon,elem,size,count, node_name);
    }else if((c=compare(node->elem,elem))>0){
        node->leftSon=addRecBinary(node->leftSon,elem,size,count, node_name);   
    }
    return node;
}
unsigned int addBinary(treeADT tree, elemType elem,char *node_name){
    size_t count;
    tree->first=addRecBinary(tree->first,elem,&tree->size,&count,node_name);
    return count;
}

//--------------------------------------------------------//


void printRightChild(t_node list) {
	if(list == NULL) {
		printf("NULL\n");
		return ;
	}
	printf("%d -> ", list->elem);
	printRightChild(list->rightSon);
}
void printLeftChild(t_node list) {
	if(list == NULL) {
		printf("NULL\n");
		return ;
	}
	printf("%d -> ", list->elem);
	printLeftChild(list->leftSon);
}
void printRec(t_node list){
    if(list == NULL) {
		printf("NULL\n");
		return ;
	}
    printf("--------\n");
    printf("   %s   \n",list->node_name);
    printf("--------\n");
    printf("right:");
    printRightChild(list->rightSon);
    printf("left:");
    printLeftChild(list->leftSon);
    printRec(list->rightSon);
    printRec(list->leftSon);   
}
void multiplyTreeRec(t_node node,int value){
    if(node==NULL){
        return;
    }
    multiplyTreeRec(node->rightSon,value);
    multiplyTreeRec(node->leftSon,value);
    
    node->elem*=value;
    
}
void multiplyTree(treeADT tree, int value){
    if(tree==NULL){
        return;
    }
    multiplyTreeRec(tree->first,value);
        
}

