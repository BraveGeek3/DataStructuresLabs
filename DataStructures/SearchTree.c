#include <stdlib.h>
#include "string.h"

typedef struct SearchTree {
    int departmentId;
    struct SearchTree* left;
    struct SearchTree* right;
    struct SearchTree* parent;
    char departmentName[31];
    char chiefName[26];
} SearchTree;

SearchTree* createNode(int key, const char* departmentName, const char* chiefName) {
    SearchTree* newNode = (SearchTree*)malloc(sizeof(SearchTree));
    if (!newNode) return NULL; // Проверка выделения памяти

    newNode->departmentId = key;
    newNode->left = newNode->right = newNode->parent = NULL;
    strncpy(newNode->departmentName, departmentName, 30);
    newNode->departmentName[30] = '\0';
    strncpy(newNode->chiefName, chiefName, 25);
    newNode->chiefName[25] = '\0';

    return newNode;
}

SearchTree* insertNode(SearchTree* root, int key, const char* departmentName, const char* chiefName) {
    if (root == NULL) {
        return createNode(key, departmentName, chiefName);
    }

    if (key < root->departmentId) {
        SearchTree* leftChild = insertNode(root->left, key, departmentName, chiefName);
        root->left = leftChild;
        leftChild->parent = root;
    } else if (key > root->departmentId) {
        SearchTree* rightChild = insertNode(root->right, key, departmentName, chiefName);
        root->right = rightChild;
        rightChild->parent = root;
    }

    return root;
}

SearchTree* findMin(SearchTree* node) {
    while (node && node->left != NULL) node = node->left;
    return node;
}

SearchTree* deleteNode(SearchTree* root, int key, int *isDeleted) {
    if (isDeleted == NULL) {
        isDeleted = (int *) malloc(sizeof(int));
        *isDeleted = 0;
    }
    if (root == NULL) {
        if (*isDeleted == 1) {
            return root;
        }

        printf("Не удалось удалить элемент\n");
        return NULL;
    }

    if (key < root->departmentId) {
        root->left = deleteNode(root->left, key, isDeleted);
    } else if (key > root->departmentId) {
        root->right = deleteNode(root->right, key, isDeleted);
    } else {
        if (root->left == NULL) {
            SearchTree* temp = root->right;
            free(root);

            *isDeleted = 1;
            return temp;
        } else if (root->right == NULL) {
            SearchTree* temp = root->left;
            free(root);

            *isDeleted = 1;
            return temp;
        }

        *isDeleted = 1;
        SearchTree* temp = findMin(root->right);
        root->departmentId = temp->departmentId;
        strcpy(root->departmentName, temp->departmentName);
        strcpy(root->chiefName, temp->chiefName);
        root->right = deleteNode(root->right, temp->departmentId, isDeleted);
    }

    return root;
}

// Освобождение памяти дерева
void freeSearchTree(SearchTree* root) {
    if (root != NULL) {
        freeSearchTree(root->left); // Рекурсивное освобождение левого поддерева
        freeSearchTree(root->right); // Рекурсивное освобождение правого поддерева
        free(root); // Освобождение текущего узла
    }
}
