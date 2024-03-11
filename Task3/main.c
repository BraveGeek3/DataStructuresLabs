#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Определение структуры для узла дерева
typedef struct Node {
    int departmentId;
    char departmentName[31];
    char chiefName[26];
    struct Node *left, *right;
} Node;

// Функция создания нового узла
Node* createNode(int id) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->departmentId = id;
    snprintf(newNode->departmentName, 31, "Dept %d", id); // Примерное наименование
    snprintf(newNode->chiefName, 26, "Chief %d", id); // Примерное имя начальника
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Функция вставки узла в дерево
Node* insertNode(Node* root, int id) {
    if (root == NULL) return createNode(id);

    if (id < root->departmentId)
        root->left = insertNode(root->left, id);
    else
        root->right = insertNode(root->right, id);

    return root;
}

// Функция для вывода дерева в виде триплетов
void printTree(Node* root) {
    if (root != NULL) {
        printf("Вершина: %d, Левый сын: %s, Правый сын: %s\n",
               root->departmentId,
               root->left ? root->left->departmentName : "нет",
               root->right ? root->right->departmentName : "нет");
        printTree(root->left);
        printTree(root->right);
    }
}

void freeTree(Node* root) {
    if (root != NULL) {
        freeTree(root->left); // Рекурсивное освобождение левого поддерева
        freeTree(root->right); // Рекурсивное освобождение правого поддерева
        free(root); // Освобождение текущего узла
    }
}

int main() {
    int n, i, id;
    Node* root = NULL;

    printf("Введите количество элементов: ");
    scanf("%d", &n);

    srand(time(NULL)); // Инициализация генератора случайных чисел

    for (i = 0; i < n; i++) {
        id = rand() % 100; // Генерация случайного номера подразделения
        printf("%d ", id);
        root = insertNode(root, id);
    }

    printf("\n");

    printf("Дерево поиска в виде списка триплетов:\n");
    printTree(root);

    freeTree(root); // Освобождение памяти, занятой деревом
    return 0;
}

