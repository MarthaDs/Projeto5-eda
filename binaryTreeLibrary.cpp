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

int showMenu();
Tree *createEmptyTree();
int treeIsEmpty(Tree* t);
void insert(Tree **, int);
Tree *loadTreeFromFile(Tree *tree, char fileName[MAX]);
void showTree(Tree *root);

int main() {
    int opcao = 0;
    char fileName[MAX];
    char path[] = "BSTs/";
    Tree *root = createEmptyTree(); 

    while(opcao != 11) {
        opcao = showMenu();

        switch(opcao){
            case 1: 
                getchar();
                gets(fileName);
                strcpy(path,"BSTs/");
                strcat(path, fileName);
                printf("%s\n", path);
                root = loadTreeFromFile(root, path);
                break;
            
             case 2:
                showTree(root);
                break;
            default:
                if(opcao != 11) printf("Opção inválida\n");
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
    if(!treeIsEmpty(root)) {
        printf("%d\n", root->value);
        showTree(root->left);
        showTree(root->right);
    }
}

/* void isFull(Tree *root) {

} */

