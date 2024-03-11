//
// Created by bravegeek on 09.03.2024.
//

#include <stdio.h>
#include <stdlib.h>

// Структура узла бинарного дерева
typedef struct BinaryTree {
    int data;
    struct BinaryTree* left;
    struct BinaryTree* right;
} BinaryTree;

// Функция для создания нового узла бинарного дерева
//BinaryTree* newBinaryTreeNode(int data) {
//    BinaryTree* node = (BinaryTree*)malloc(sizeof(BinaryTree));
//    node->data = data;
//    node->left = NULL;
//    node->right = NULL;
//    return node;
//}

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

    return node;
}

// добавление правого потомка
BinaryTree* addRightChild(BinaryTree* node, int data) {
    BinaryTree* childNode = (BinaryTree*)malloc(sizeof(BinaryTree));
    childNode->data = data;
    childNode->left = NULL;
    childNode->right = NULL;

    node->right = childNode;

    return node;
}