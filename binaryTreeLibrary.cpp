#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

typedef struct tree {
    int value;
    struct tree *left;
    struct tree *right;
} Tree;

int showMenu();
Tree *inicialize();
Tree *insert(Tree *, int);
Tree *loadTreeFromFile(Tree *tree, char fileName[MAX]);
void showTree(Tree *node);

int main() {
    int opcao = 0;
    char fileName[MAX];
    char path[] = "BSTs/";
    Tree *root = inicialize(); 

    while(opcao != 11) {
        opcao = showMenu();

        switch(opcao){
            case 1: 
                getchar();
                gets(fileName);
                strcpy(path,"BSTs/");
                strcat(path, fileName);
                printf("%s", path);
                loadTreeFromFile(root, path);
                break;
            
             case 2:
                getchar();
                showTree(root);
                break;
            default:
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

Tree *inicialize() {
    return NULL;
}

Tree *loadTreeFromFile(Tree *tree, char fileName[MAX]) {
    FILE *file = fopen(fileName,"r");

    if(file == NULL) {
        printf("\nCan't find file\n");
    }
    else {
        int value;
        while (fscanf(file,"%d ",&value) != EOF) {
            insert(tree,value);
            if(tree == NULL) printf("sad");
        } 
    }
}

Tree *insert(Tree *node, int value) {

    if(node == NULL) {
        Tree * newNode = (Tree*) malloc(sizeof(Tree));
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->value = value;
        node = newNode;
    }
    else if (node->value > value) {
        node->left = insert(node->left,value);
    }
    else if(node->value < value) {
        node->right = insert(node->right, value);
    }

    return node;
}

void showTree(Tree *tree) {
    if(tree != NULL) {
        printf("%d", tree->value);
        showTree(tree->left);
        showTree(tree->right);
    }
}