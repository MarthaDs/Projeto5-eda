#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

typedef struct tree
{
    int value;
    struct tree *left;
    struct tree *right;
    struct tree *parent;
} Tree;

typedef struct queue
{
    int value;
    struct queue *prox;
} Queue;

int showMenu();
Tree *createEmptyTree();
int treeIsEmpty(Tree *tree);
void insert(Tree **root, int value);
Tree *loadTreeFromFile(Tree *tree, char fileName[MAX]);
Tree *searchValue(Tree *node, int value);
void siblings(tree *node, int value);
void printInOrder(Tree *root);
void printPreOrder(Tree *root);
void printPosOrder(Tree *root);
void removeValue(Tree *node, int value);
Tree *FindMin(Tree *node);

int nodeLevel = 1;
char path[] = "BSTs/";
int main()
{
    int value, value2, opcao = 0;
    char fileName[MAX];
    Tree *root = createEmptyTree();

    while (opcao != 11)
    {
        opcao = showMenu();

        switch (opcao)
        {
        case 1:
            getchar();
            scanf(" %[^\n]", fileName);
            //gets(fileName);
            strcpy(path, "BSTs/");
            strcat(path, fileName);
            printf("%s\n", path);
            root = loadTreeFromFile(root, path);
            break;

        case 2:
            //showTree(root);
            break;

        case 4:
            printf("Enter the value: ");
            scanf("%d", &value);
            searchValue(root, value);
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

        default:
            if (opcao != 11)
                printf("Opção inválida\n");
            break;
        }
    }
    return 0;
}

int showMenu()
{
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

Tree *createEmptyTree()
{
    return NULL;
}

int treeIsEmpty(Tree *t)
{
    return t == NULL;
}

Tree *loadTreeFromFile(Tree *tree, char fileName[MAX])
{
    FILE *file = fopen(fileName, "r");

    if (file == NULL)
    {
        printf("\nCan't find file\n");
    }
    else
    {
        int value;
        while (fscanf(file, "%d ", &value) != EOF)
        {
            insert(&tree, value);
        }
    }
    if (file != NULL)
        fclose(file);

    return tree;
}

void insert(Tree **node, int value)
{

    if (*node == NULL)
    {
        *node = (Tree *)malloc(sizeof(Tree));
        (*node)->left = NULL;
        (*node)->right = NULL;
        (*node)->parent = NULL;
        (*node)->value = value;
    }
    if ((*node)->value > value)
    {
        insert(&(*node)->left, value);
        ((*node)->left)->parent = *node;
    }
    if ((*node)->value < value)
    {
        insert(&(*node)->right, value);
        ((*node)->right)->parent = *node;
    }
}

Tree *searchValue(Tree *node, int value)
{
    if (node == NULL)
    {
        printf("Not found, value doesn't exist on the tree.\n");
    }
    if (node->value == value)
    {
        if (node->parent != NULL)
        {
            printf("Parent: %d\n", (node->parent)->value);
            siblings(node->parent, value);
        }
        else
        {
            printf("Is the root, doesn't have parent.\n");
        }
        printf("Level: %d\n", nodeLevel);
        return(node);
        nodeLevel = 1;
    }
    if (node->value > value)
    {
        nodeLevel++;
        return searchValue(node->left, value);
        
    }
    if (node->value < value)
    {
        nodeLevel++;
        return searchValue(node->right, value);
        
    }
}

void siblings(tree *node, int value)
{
    if (node->left != NULL && (node->left)->value != value)
    {
        printf("sibling: %d\n", (node->left)->value);
    }
    else if (node->right != NULL && (node->right)->value != value)
    {
        printf("siblings: %d\n", (node->right)->value);
    }
    else
    {
        printf("No siblings!\n");
    }
}

void printInOrder(Tree *root)
{
    if (!treeIsEmpty(root))
    {
        printInOrder(root->left);
        printf("%d\n", root->value);
        printInOrder(root->right);
    }
}

void printPreOrder(Tree *root)
{
    if (!treeIsEmpty(root))
    {
        printf("%d\n", root->value);
        printPreOrder(root->left);
        printPreOrder(root->right);
    }
}

void printPosOrder(Tree *root)
{
    if (!treeIsEmpty(root))
    {
        printPosOrder(root->left);
        printPosOrder(root->right);
        printf("%d\n", root->value);
    }
}

void removeValue(Tree *node, int value)
{
        Tree *nodeRemove = searchValue(node,value);
        printf("Valor do nó a ser deletado : %d\n", nodeRemove->value);
        //primeiro caso, quando o nó n tem filhos
        if(nodeRemove->left == NULL && nodeRemove->right == NULL){
            if(nodeRemove->parent->value > value){
                nodeRemove->parent->left = NULL;
                
            }
            if(nodeRemove->parent->value <= value){
                nodeRemove->parent->right = NULL;
            }
            free(nodeRemove);
        }
        //segundo caso, quando o nó tem 1 filhos
        else if( nodeRemove->left != NULL &&  nodeRemove->right == NULL){
            if(nodeRemove->parent->value > value){
                nodeRemove->parent->left = nodeRemove->left;
            }
            else{
                nodeRemove->parent->right =nodeRemove->left;
            }
            free(nodeRemove);

        }
        else if( nodeRemove->left == NULL &&  nodeRemove->right != NULL ){
            if(nodeRemove->parent->value > value){
                nodeRemove->parent->left = nodeRemove->right;
            }
            else{
                nodeRemove->parent->right = nodeRemove->right;
            }
            free(nodeRemove);
        }
        //terceiro caso, quando o no tem 2 filho
        else{
            Tree *tempNode = FindMin(nodeRemove->right);
            nodeRemove->value = tempNode->value;
            removeValue(nodeRemove->right, tempNode->value);
        }
}

Tree *FindMin(Tree *node){
    while(1){
        if(node->left != NULL){
            node = node->left;
        }
        else{
            return node;
        }
    }    
}
