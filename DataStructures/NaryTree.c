//
// Created by bravegeek on 09.03.2024.
//

#include "NaryTree.h"
#include "stdlib.h"

// Структура узла сильно ветвящегося дерева
typedef struct NaryTree {
    int data;
    struct NaryTree** children; // Динамический массив детей
    int children_count;
} NaryTree;

// Функция для добавления узла в сильно ветвящееся дерево
void addNaryTreeNode(NaryTree* parent, NaryTree* child) {
    parent->children_count++;
    parent->children = realloc(parent->children, parent->children_count * sizeof(NaryTree*));
    parent->children[parent->children_count - 1] = child;
}

// Функция для создания нового узла сильно ветвящегося дерева
NaryTree* newNaryTreeNode(int data) {
    NaryTree* node = (NaryTree*)malloc(sizeof(NaryTree));
    node->data = data;
    node->children = NULL;
    node->children_count = 0;
    return node;
}