#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 50
#define true 1
#define false 0


typedef struct tree {
    int value;
    struct tree *left;
    struct tree *right;
    struct tree *parent;
} Tree;

int showMenu();
Tree *createEmptyTree();
int treeIsEmpty(Tree *tree);
void insert(Tree **root, int value);
Tree *loadTreeFromFile(Tree *tree, char fileName[MAX]);
Tree *searchValue(Tree *node, int value, int nodeLevel);
void showTree(Tree *, int height);
void siblings(tree *node, int value);
void printInOrder(Tree *root);
void printPreOrder(Tree *root);
void printPosOrder(Tree *root);
void removeValue(Tree *node, int value);
Tree *FindMin(Tree *node);
int getHeight(Tree *node);
int isFull(Tree *root);
Tree *parent(Tree *node, int value);
Tree *rightRotation(Tree *grandParent, Tree *parent, Tree *leftChild);
void leftRotation(Tree *grandParent, Tree *parent, Tree *leftChild);
Tree *createBackbone(Tree *node);
unsigned int binarytree_count_recursive;
unsigned int binarytree_count(Tree *tree);
void makeRotation(unsigned int count, Tree *nodeBackbone);
int greatestPowerOf2LessThanN(int n);
void balanceTree(Tree *node);

char path[] = "BSTs/";

int main() {
    int value, value2, opcao = 0, height = 0;
    int fullTree;
    char fileName[MAX];
    int nodeLevel = 1;
    Tree *root = createEmptyTree();

    while (opcao != 11) {
        opcao = showMenu();

        switch (opcao) {
        case 1:
            printf("Enter the name of the file to be loaded: \n");
            getchar();
            scanf(" %[^\n]",fileName);
            //gets(fileName);
            strcpy(path,"BSTs/");
            strcat(path, fileName);
            printf("%s\n", path);
            root = loadTreeFromFile(root, path);
            break;

        case 2:
            showTree(root, getHeight(root));
            break;

        case 3:
            fullTree = isFull(root);
            if(fullTree == 1) {
                printf("Tree is full\n");
            }
            else if(fullTree == 0) {
                printf("Tree isn't full\n");
            }
            break;

        case 4:
            printf("Enter the value: ");
            scanf("%d", &value);
            searchValue(root, value, nodeLevel);
            break;

        case 5:
            height = getHeight(root);
            printf("Height of the tree : %d\n", height);
            break;

        case 6:
            printf("Enter the value: ");
            scanf("%d", &value2);
            printf("%d\n",value2);
            removeValue(root, value2);

            break;

        case 7:
            printInOrder(root);
            break;

        case 8:
            printPreOrder(root);
            break;

        case 9:
            printPosOrder(root);
            break;
        
        case 10:
            //isBalance(root);
            break;

        default:
            if (opcao != 11)
                printf("Opção inválida\n");
            break;
        
        }
    }
    return 0;
}

int showMenu() {
    int opcao = 0;

    printf("---------------------------------- \n");
    printf("          Menu de Opções \n");
    printf("----------------------------------\n");
    printf("1 - Load tree from file\n");
    printf("2 - Show tree\n");
    printf("3 - Is Full\n");
    printf("4 - Search value\n");
    printf("5 - Get height\n");
    printf("6 - Remove value\n");
    printf("7 - Print InOrder\n");
    printf("8 - Print PreOrder\n");
    printf("9 - Print PosOrder\n");
    printf("10 - Balance tree\n");
    printf("11 - Sair\n");
    printf("\nEscolha uma das opções: \n");
    scanf("%d", &opcao);

    return opcao;
}

Tree *createEmptyTree() {
    return NULL;
}

int treeIsEmpty(Tree *t) {
    return t == NULL;
}

Tree *loadTreeFromFile(Tree *tree, char fileName[MAX]) {
    FILE *file = fopen(fileName, "r");

    if (file == NULL) {
        printf("\nCan't find file\n");
    }
    else {
        int value;
        while (fscanf(file, "%d ", &value) != EOF) {
            insert(&tree, value);
        }
    }
    if (file != NULL) {
        fclose(file);
    }
    return tree;
}

void insert(Tree **node, int value) {

    if (*node == NULL) {
        *node = (Tree *)malloc(sizeof(Tree));
        (*node)->left = NULL;
        (*node)->right = NULL;
        (*node)->parent = NULL;
        (*node)->value = value;
    }
    if ((*node)->value > value) {
        insert(&(*node)->left, value);
        ((*node)->left)->parent = *node;
    }
    if ((*node)->value < value) {
        insert(&(*node)->right, value);
        ((*node)->right)->parent = *node;
    }
}

void showTree(Tree *root,int height) {
    tree *aux = root;
    int elems = (pow(2,height));
    elems--;
    int order[elems],i = 0,current = 0, numLevel, count, j,
    spaceLevel = 0, espaceBetween = 3, countAux, space;

    if (aux == NULL) {
      return;
    }
    
    order[i] = aux->value;
    i++;

    while(i < elems) {
        if(order[current] == 0) {
          order[i] = 0;
          i++;
          order[i] = 0;
          i++;
        }
        else {
          aux = parent(root, order[current]);
          
          if(aux->left != NULL) {
            if(aux->left->value == order[current])
              aux = aux->left;
          }
          if(aux->right != NULL) {
            if(aux->right->value == order[current])
              aux = aux->right;
          }
          if (aux->left != NULL)
            order[i]= aux->left->value;
          else
            order[i] = 0;
          
          i++;
          
          if (aux->right != NULL)
            order[i]= aux->right->value;
          else
            order[i] = 0;

          i++;
        }
        current++;
    }
    current = 1;
    i = 1;
    j = 1;
    numLevel = 2;
    space = ((espaceBetween- 1) / 2) + 1;

    for(count = 0; count < (height-1) ;count++){
      spaceLevel += space;
      space = 2*space;
    }

    for(count = 0; count < (height-1) ;count++){
      espaceBetween = (2*espaceBetween) + 1;
    }

    for(count = 0; count < spaceLevel; count++){
      printf(" ");
    }
    printf("%d\n",order[0]);

    space = space / 2;
    spaceLevel +=  - space;
    space = space / 2;
    espaceBetween += - 1;
    espaceBetween = espaceBetween / 2;

    while(i < elems){
      for(count = 0;count < spaceLevel; count++) {
        printf(" ");
      }
      for(count = 0; count < numLevel; count++) {
        if(j % 2 == 1) {
          if(order[j] != 0)
            printf("/");
          else
            printf(" ");
        }
        if(j % 2 == 0) {
          if(order[j] != 0)
            printf("\\");
          else
            printf(" ");
        }
        if(count < numLevel-1) {
          for(countAux = 0; countAux < espaceBetween; countAux++) {
            printf(" ");
          }
        }
        j++;
      }
      printf("\n");

      for(count = 0; count < spaceLevel;count++) {
        printf(" ");
      }

      for(count = 0; count < numLevel; count++) {
        if(i % 2 == 1) {
          if(order[i] != 0)
            printf("%d",order[i]);
          else
            printf(" ");
        }
        if(i % 2 == 0) {
          if(order[i] != 0)
            printf("%d",order[i]);
          else
            printf(" ");
        }
        if(count < numLevel-1) {
          if(order[i] >= 10){
            for(countAux = 0; countAux < espaceBetween - 1; countAux++) {
              printf(" ");
            }
          }
          else {
            for(countAux = 0; countAux < espaceBetween; countAux++) {
              printf(" ");
            }
          }
        }
        i++;
      }
      printf("\n");

      numLevel = 2*numLevel;
      spaceLevel +=  - space;
      space = space / 2;
      espaceBetween += - 1;
      espaceBetween = espaceBetween / 2;

    }
}

Tree *parent(Tree *node, int value) {
    if (node == NULL) {
      //  printf("Not found, value doesn't exist on the tree.\n");
        return NULL;
    }
    if (node->value == value) {
        if (node->parent != NULL) {
            //printf("Parent: %d\n", (node->parent)->value);
           // siblings(node->parent, value);
        }
        else {
           // printf("Is the root, doesn't have parent.\n");
        }
        //printf("Level: %d\n", nodeLevel);
        return(node);
        //nodeLevel = 1;
    }
    if (node->value > value) {
        //nodeLevel++;
        return parent(node->left, value);
        
    }
    if (node->value < value) {
       // nodeLevel++;
        return parent(node->right, value);     
    }
}

Tree *searchValue(Tree *node, int value, int nodeLevel) {
    if (node == NULL) {
        printf("Not found, value doesn't exist on the tree.\n");
        return NULL;
    }
    if (node->value == value) {
        if (node->parent != NULL) {
            printf("Parent: %d\n", (node->parent)->value);
            siblings(node->parent, value);
        }
        else {
            printf("Is the root, doesn't have parent.\n");
        }
        printf("Level: %d\n", nodeLevel);
        return(node);
        nodeLevel = 1;
    }
    if (node->value > value) {
        nodeLevel++;
        return searchValue(node->left, value, nodeLevel);
        
    }
    if (node->value < value) {
        nodeLevel++;
        return searchValue(node->right, value, nodeLevel);     
    }
}

void siblings(tree *node, int value) {
    if (node->left != NULL && (node->left)->value != value) {
        printf("sibling: %d\n", (node->left)->value);
    }
    else if (node->right != NULL && (node->right)->value != value) {
        printf("siblings: %d\n", (node->right)->value);
    }
    else {
        printf("No siblings!\n");
    }
}

void printInOrder(Tree *root) {
    if (!treeIsEmpty(root)) {
        printInOrder(root->left);
        printf("%d\n", root->value);
        printInOrder(root->right);
    }
}

void printPreOrder(Tree *root) {
    if (!treeIsEmpty(root)) {
        printf("%d\n", root->value);
        printPreOrder(root->left);
        printPreOrder(root->right);
    }
}

void printPosOrder(Tree *root) {
    if (!treeIsEmpty(root)) {
        printPosOrder(root->left);
        printPosOrder(root->right);
        printf("%d\n", root->value);
    }
}

void removeValue(Tree *node, int value) {
    Tree *nodeRemove = parent(node,value);
    if(nodeRemove == NULL) {
        printf("Can't find this value on the tree\n");
    }

    if(!treeIsEmpty(nodeRemove)) {
        //first case, node hasn't  children
        if(nodeRemove->left == NULL && nodeRemove->right == NULL) {
            if(nodeRemove->parent->value > value) {
                nodeRemove->parent->left = NULL;
                
            }
            if(nodeRemove->parent->value <= value) {
                nodeRemove->parent->right = NULL;
            }
            free(nodeRemove);
        }
        //second case, node has 1 kid
        else if( nodeRemove->left != NULL &&  nodeRemove->right == NULL) {
            if(nodeRemove->parent->value > value) {
                nodeRemove->parent->left = nodeRemove->left;
            }
            else {
                nodeRemove->parent->right =nodeRemove->left;
            }
            free(nodeRemove);

        }
        else if( nodeRemove->left == NULL &&  nodeRemove->right != NULL ) {
            if(nodeRemove->parent->value > value) {
                nodeRemove->parent->left = nodeRemove->right;
            }
            else {
                nodeRemove->parent->right = nodeRemove->right;
            }
            free(nodeRemove);
        }
        //third case, node has 2 children
        else {
            Tree *tempNode = FindMin(nodeRemove->right);
            nodeRemove->value = tempNode->value;
            removeValue(nodeRemove->right, tempNode->value);
        }
    }
}

Tree *FindMin(Tree *node) {
    while(1) {
        if(node->left != NULL) {
            node = node->left;
        }
        else {
            return node;
        }
    }    
}

int getHeight(Tree *node) { 
   if (node==NULL) { 
       return 0; 
   }
   else { 
       int heightLeft = getHeight(node->left); 
       int heightRight = getHeight(node->right); 

       if (heightLeft > heightRight) {
           return(heightLeft + 1); 
       }
       else { 
            return(heightRight + 1); 
        }
   } 
}  

int isFull(Tree *root) {
    if(root != NULL) {
        if(root->left == NULL && root->right == NULL) {
            return 1;
        }

        if(root->left != NULL && root->right != NULL) {
            return (isFull(root->left) && isFull(root->right));
        }
    }
    return 0;
}
int isBalance(Tree *node){
	Tree *aul = node->left;
	int l = getHeight(aul);
	Tree *aur = node->right;
	int r = getHeight(aur);
	int total = abs(l - r);
    printf("resultado: %d\n", total);
	if(total <= 1) {
		printf("The tree is balanced.\n");
		return true;
	}
    else {
		printf("The tree is not balanced.\n");
		return false;	
	}
}
Tree *rightRotation(Tree *grandParent, Tree *parent, Tree *leftChild){
    if(grandParent != NULL){
        if(grandParent->left == parent){
            grandParent->left = leftChild;
        }
        else{
            grandParent->right = leftChild;
        }
    }    
    parent->left = leftChild->right;
    leftChild->right = parent;
    return grandParent;
}

void leftRotation(Tree *grandParent, Tree *parent, Tree *leftChild){
    if(grandParent != NULL){
        if(grandParent->left == parent){
            grandParent->left = leftChild;
        }
        else{
            grandParent->right = leftChild;
        }
    }    
    parent->right = leftChild->left;
    leftChild->left = parent;
}

Tree *createBackbone(Tree *node) {
    Tree *grandParent = NULL;
    Tree *parent = node;
    Tree *leftChild;
 
    while (parent != NULL) {
        leftChild = parent->left;
        if (leftChild != NULL) {
            grandParent = rightRotation(grandParent, parent, leftChild);
            parent = leftChild;
        } 
        else {
        grandParent = parent;
        parent = parent->right;
        }
    }
    return grandParent;
}

unsigned int binarytree_count_recursive(Tree *node)
{
    unsigned int count = 1;
    if (node->left != NULL) {
       count += binarytree_count_recursive(node->left);
    }
    if (node->right != NULL) {
        count += binarytree_count_recursive(node->right);
    }
    return count;
}
 
unsigned int binarytree_count(Tree *tree)
{
    unsigned int count = 0;
    if (tree->node != NULL) {
        count = binarytree_count_recursive(tree->node);
    }
    return count;
}

void makeRotation(unsigned int count, Tree *nodeBackbone){
    Tree *grandParent = NULL;
    Tree *parent = nodeBackbone;
    Tree *child = nodeBackbone->right;
    for (; count > 0; count--) {
        if (child != NULL) {
            leftRotation(grandParent, parent, child);
            grandParent = child;
            parent = grandParent->right;
            child = parent->right;
        } 
        else {
            break;
        }
    }
} 

int greatestPowerOf2LessThanN(int n) {
  int x = binarytree_count(n);
  return (1 << x);
}
void balanceTree(Tree *node){
    if(isBalance(node) == false){    
        int n = 0;
        for (Tree *tmp = node; tmp !=NULL; tmp = tmp->right) {
            n++;
        }
  
        int m = greatestPowerOf2LessThanN(n + 1) - 1;
        unsigned int r = (n - m);
        Tree *aux = createBackbone(node);
        makeRotations(r, aux);
 
        while (m > 1) {
            makeRotations(m /= 2);
        }
    }
}

