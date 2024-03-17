#include <stdio.h>
#include <stdlib.h>

// Структура узла бинарного дерева
typedef struct BinaryTree {
    int data;
    struct BinaryTree* left;
    struct BinaryTree* right;
} BinaryTree;

// добавление левого потомка
BinaryTree* addLeftChild(BinaryTree* node, int data) {
    if (data == 0) {
        return NULL;
    }

    BinaryTree* childNode = (BinaryTree*)malloc(sizeof(BinaryTree));
    childNode->data = data;
    childNode->left = NULL;
    childNode->right = NULL;

    node->left = childNode;

    return childNode;
}

// добавление правого потомка
BinaryTree* addRightChild(BinaryTree* node, int data) {
    if (data == 0) {
        return NULL;
    }

    BinaryTree* childNode = (BinaryTree*)malloc(sizeof(BinaryTree));
    childNode->data = data;
    childNode->left = NULL;
    childNode->right = NULL;

    node->right = childNode;

    return childNode;
}

void freeTree(BinaryTree* root) {
    if (root != NULL) {
        freeTree(root->left); // Рекурсивное освобождение левого поддерева
        freeTree(root->right); // Рекурсивное освобождение правого поддерева
        free(root); // Освобождение текущего узла
    }
}