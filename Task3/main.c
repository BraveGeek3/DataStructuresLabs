#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../DataStructures/SearchTree.c"

// Функция для вывода дерева в виде триплетов
void printTree(SearchTree * root) {
    if (root != NULL) {
        // Выводим ключ дочернего узла -1 если узла нет
        printf("Вершина: \"%d\",\n Левый узел: \"%s\",\n Ключ левого узла:\"%d\",\n Правый узел: \"%s\",\n Ключ правого узла: \"%d\"\n\n",
               root->departmentId,
               root->left ? root->left->departmentName : "нет",
               root->left ? root->left->departmentId : -1,
               root->right ? root->right->departmentName : "нет",
               root->right ? root->right->departmentId : -1
               ),
        printTree(root->left);
        printTree(root->right);
    }
}

int main() {
    // Считывание данных из файла
    FILE* file = fopen("input.txt", "r");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    // Считываем количество записей
    int n;
    fscanf(file, "%d", &n);
    printf("Считываем %d записей...\n", n);

    // Инициализируем переменные
    SearchTree* root = NULL;
    int key;
    char departmentName[31];
    char chiefName[26];

    // Считываем триплеты из файла
    for (int i = 0; i < n + 1; ++i) {
        fscanf(file, "%d,"
                     "%[^,],"  /* use "name:%s" if you want the quotes */
                     "%[^\n]\n",
                     &key, departmentName, chiefName);
        root = insertNode(root, key, departmentName, chiefName);
    }

    // Закрываем файл
    fclose(file);

    // Выводим дерево
    printTree(root);

    printf("Введите ключ записи, который нужно удалить:\n");
    scanf("%d", &key);
    printf("Удаляем запись с ключом: %d\n");

    deleteNode(root, key, 0);

    printTree(root);

    // Освобождаем память
    freeSearchTree(root);
    return 0;
}

