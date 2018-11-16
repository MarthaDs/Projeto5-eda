#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct tree {
    int value;
    struct tree *left;
    struct tree *right;
} Tree;

tree *inicialize();
void insert(Tree *, int);
tree *loadTreeFromFile(Tree *, char);

int main() {
    return 0;
}

tree *inicialize() {
    Tree *tree = (Tree*) malloc(sizeof(Tree));
    return tree = NULL;
}

tree *loadTreeFromFile(Tree *tree, char fileName[MAX]) {
    Tree *node = (Tree*) malloc(sizeof(Tree));
    FILE *file = fopen(fileName,"r");

    if(file == NULL) {
        printf("\nCan't find file");
    }
    else {
        node = tree;
        int value;
        while (fscanf(file,"%d ",&value) != EOF) {
            insert(node,value);
        }
    }
}

void insert(Tree *node, int value) {
    if(node == NULL) {
        node->value = value;
        node->left = NULL;
        node->right = NULL;
    }
    else if (node->value > value) {
        insert(node->left,value);
    }
    else if(node->value < value) {
        insert(node->right, value);
    }
}

void showTree(Tree *node) {
    if(node != NULL) {
        printf("%d\n", node->value);
    }
 // incompleta
}