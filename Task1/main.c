#include "../DataStructures/BinaryTree.c"
#include "../DataStructures/NaryTree.c"

// Функция для преобразования бинарного дерева в сильно ветвящееся дерево
NaryTree *convertToNaryTree(BinaryTree *root, NaryTree *naryTreeRoot) {
    // Если у вершины нет детей, то выходим из рекурсии
    if (root == NULL) {
        return NULL;
    }

    // Если не создан корень ветвящегося дерева, создаем
    if (naryTreeRoot == NULL) {
        naryTreeRoot = newNaryTreeNode(root->data);

        convertToNaryTree(root->left, naryTreeRoot);
        convertToNaryTree(root->right, naryTreeRoot);
        return naryTreeRoot;
    }

    NaryTree * child = newNaryTreeNode(root->data);
    addNaryTreeChildNode(naryTreeRoot, child);

    BinaryTree *leftBinaryNode = root->left;
    BinaryTree *rightBinaryNode = root->right;

    // Рекурсивно добавляем левые и правые вершины бинарного дерева в сильно ветвящееся
    if (leftBinaryNode != NULL) {
        NaryTree *leftNaryNode = newNaryTreeNode(leftBinaryNode->data);
        addNaryTreeChildNode(naryTreeRoot, leftNaryNode);
        convertToNaryTree(leftBinaryNode->left, naryTreeRoot);
    }

    if (rightBinaryNode != NULL) {
        NaryTree *rightNaryNode = newNaryTreeNode(rightBinaryNode->data);
        addNaryTreeChildNode(naryTreeRoot, rightNaryNode);
        convertToNaryTree(rightBinaryNode, naryTreeRoot);
    }

    return naryTreeRoot;
}

// Вывод дерева в файл
void printTreeToFile(NaryTree *root, FILE *file) {
    fprintf(file, "%d\n", root->data);
    if (root->children_count == 0) {
        fprintf(file, " NULL\n");
    } else {
        for (int j = 0; j < root->children_count; j++) {
            fprintf(file, "%d ", root->children[j]->data);
        }
    }
    fprintf(file, "\n");
}

// Поиск узла в бинарном дереве
BinaryTree *findBinaryNode(BinaryTree **nodes, int count, int data) {
    for (int i = 0; i < count; i++) {
        if (nodes[i]->data == data) {
            return nodes[i];
        }
    }
    return NULL;
}

int main() {
    // Выделяем память под бинарное дерево и инициализируем переменные
    BinaryTree *binaryTree = (BinaryTree *) malloc(sizeof(BinaryTree));
    BinaryTree **nodesArr = NULL;
    BinaryTree *temp;


    binaryTree->left = NULL;
    binaryTree->right = NULL;

    // Открываем файлы для чтения и записи
    FILE *inFile = fopen("input.txt", "r"), *outFile = fopen("output.txt", "w");

    int count = 0;
    int data, left, right;
    // Сканируем данные из файла до символа конца файла
    while (fscanf(inFile, "%d %d %d", &data, &left, &right) != EOF) {
        BinaryTree *currentNode = NULL;

        // Если длинна дерева = 0, то добавляем в корень отсканированные данные
        if (count == 0) {
            if (right != 0) {
                printf("По условию задачи у корня не должно быть правого поддерева, ошибка входных данных\n");
                return 1;
            }

            binaryTree->data = data;
            currentNode = binaryTree;
            // Выделяем память под элементы дерева
            nodesArr = (BinaryTree **) realloc(nodesArr, sizeof(BinaryTree *) * (count + 1));
            nodesArr[count++] = currentNode;
        }

        // Ищем элемент с отсканированным ключом в массиве
        currentNode = findBinaryNode(nodesArr, count, data);

        // Если есть существующая вершина (data != 0, 0 - нет потомка), то добавляем левый потомок
        if ((temp = addLeftChild(currentNode, left)) != NULL) {
            nodesArr = (BinaryTree **) realloc(nodesArr, sizeof(BinaryTree *) * (count + 1));
            nodesArr[count] = temp;

            ++count;
        }

        // Если есть существующая вершина (data != 0, 0 - нет потомка), то добавляем правый потомок
        if ((temp = addRightChild(currentNode, right)) != NULL) {
            nodesArr = (BinaryTree **) realloc(nodesArr, sizeof(BinaryTree *) * (count + 1));
            nodesArr[count] = currentNode;

            ++count;
        }
    }

    NaryTree *naryTreeRoot = NULL;
    naryTreeRoot = convertToNaryTree(binaryTree, naryTreeRoot);
    printTreeToFile(naryTreeRoot, outFile);

    fclose(inFile);
    fclose(outFile);

    freeTree(binaryTree);
    freeNaryTree(naryTreeRoot);

    return 0;
}
