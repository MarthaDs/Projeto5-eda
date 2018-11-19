#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

typedef struct tree {
    int value;
    struct tree *left;
    struct tree *right;
    struct tree *parent;
} Tree;

typedef struct queue {
    void *tree;
    struct queue *next;
} Queue;

typedef struct header{
	Queue *head; 
	Queue *tail; 
} Header;


Header *inicializeHeader();
int showMenu();
Tree *createEmptyTree();
int treeIsEmpty(Tree* tree);
void insert(Tree **root, int value);
Tree *loadTreeFromFile(Tree *tree, char fileName[MAX]);
void showTree(Tree *);
void insertElemQueue(Tree *node);
void removeElemQueue();
int searchValue(Tree *node, int value);
void siblings(tree *node, int value);
void printInOrder(Tree *root);
void printPreOrder(Tree *root);
void printPosOrder(Tree *root);


int nodeLevel = 1;
Header *queueHeader = inicializeHeader();

int main() {
    int value,opcao = 0;
    char fileName[MAX];
    char path[] = "BSTs/";
    Tree *root = createEmptyTree(); 

    while(opcao != 11) {
        opcao = showMenu();

        switch(opcao){
            case 1: 
                getchar();
                scanf(" %[^\n]",fileName);
                //gets(fileName);
                strcpy(path,"BSTs/");
                strcat(path, fileName);
                printf("%s\n", path);
                root = loadTreeFromFile(root, path);
                break;
            
             case 2:
                showTree(root);
                break;

             case 3:
                printf("Enter the value: ");
                scanf("%d", &value);
                searchValue(root,value);
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
                if(opcao != 11) printf("Opção inválida\n");
                break;
        }
    }
    return 0;
}

Header *inicializeHeader() {
	Header *header = (Header*) malloc(sizeof(Header));
    header->head = NULL;
    header->tail = NULL;
	return header;
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

int treeIsEmpty(Tree* t) {
  return t == NULL;
}

Tree *loadTreeFromFile(Tree *tree, char fileName[MAX]) {
    FILE *file = fopen(fileName,"r");

    if(file == NULL) {
        printf("\nCan't find file\n");
    }
    else {
        int value;
        while (fscanf(file,"%d ",&value) != EOF) {
           insert(&tree,value);
        }
    }
    if(file != NULL) fclose(file);

    return tree;
}

void insert(Tree **node, int value) {

    if(*node == NULL) {
        *node = (Tree*)malloc(sizeof(Tree));
        (*node)->left = NULL;
        (*node)->right = NULL;
        (*node)->parent = NULL;
        (*node)->value = value;
    }
    if((*node)->value > value) {
        insert(&(*node)->left ,value);
        ((*node)->left)->parent = *node;
    }
    if((*node)->value < value) {
        insert(&(*node)->right ,value);
        ((*node)->right)->parent = *node;
    }
}

void showTree(Tree *root) {
        Tree *aux = (Tree*) malloc(sizeof(Tree));

        aux = root;
        insertElemQueue(aux);

        while(queueHeader->head != NULL) {
            printf("%d\n", aux->value);
            insertElemQueue(aux->left);
            insertElemQueue(aux->right);
            removeElemQueue();

            if(queueHeader->head != NULL) {
                Tree *first = (Tree*)queueHeader->head->tree;
                aux = first;
            }
        }
}

void insertElemQueue(Tree *node) {
    
    if(node != NULL) {
        Queue *newElem = (Queue*) malloc(sizeof(Queue));
        newElem->tree = node;
        
        if(queueHeader->head == NULL) {
            queueHeader->head = newElem;
            queueHeader->tail = newElem;
            newElem->next = NULL;
        }
        else {
            newElem->next = NULL;
            queueHeader->tail->next = newElem;
            queueHeader->tail = newElem;
        }
    }
}

void removeElemQueue() {
    if(queueHeader->head != NULL) {
        Queue *aux = queueHeader->head;
        queueHeader->head = aux->next;
        free(aux);
    }
}


int searchValue(Tree *node, int value) {
    if(node == NULL) {
        printf("Not found, value doesn't exist on the tree.\n");
        return 0;
    }
    if(node->value == value) {
        if(node->parent != NULL) {
            printf("Parent: %d\n", (node->parent)->value);
            siblings(node->parent, value);
        }
        else {
            printf("Is the root, doesn't have parent.\n");
        }
        printf("Level: %d\n", nodeLevel);
        nodeLevel = 1;
    }
    if(node->value > value) {
        nodeLevel++;
        searchValue(node->left, value);
    }
    if(node->value < value) {
        nodeLevel++;
        searchValue(node->right, value);
    }    
}

void siblings(tree *node, int value) {
    if(node->left != NULL && (node->left)->value != value) {
        printf("sibling: %d\n", (node->left)->value);
    }
    else if(node->right != NULL && (node->right)->value != value) {
        printf("siblings: %d\n", (node->right)->value);   
    }
    else {
        printf("No siblings!\n");
    }
}

void printInOrder(Tree *root) {
    if(!treeIsEmpty(root)) {
        printInOrder(root->left);
        printf("%d\n", root->value);
        printInOrder(root->right);
    }
}

void printPreOrder(Tree *root) {
    if(!treeIsEmpty(root)) {
        printf("%d\n", root->value);
        printPreOrder(root->left);
        printPreOrder(root->right);
    }
}

void printPosOrder(Tree *root) {
    if(!treeIsEmpty(root)) {
        printPosOrder(root->left);
        printPosOrder(root->right);
        printf("%d\n", root->value);
 }
}