#include "DataStructures/BinaryTree.c"
#include "DataStructures/NaryTree.c"

// Функция для преобразования бинарного дерева в сильно ветвящееся дерево
NaryTree* convertToNaryTree(BinaryTree* root) {
    if (root == NULL) {
        return NULL;
    }

    NaryTree* naryRoot = newNaryTreeNode(root->data);
    BinaryTree* temp = root->left;

    while (temp != NULL) {
        addNaryTreeNode(naryRoot, convertToNaryTree(temp));
        temp = temp->right; // Переходим к следующему "сыну" в бинарном представлении
    }

    return naryRoot;
}

void printTreeToFile(NaryTree* nodes, int count, FILE* file) {
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s", nodes[i].name);
        if (nodes[i].children_count == 0) {
            fprintf(file, " NULL");
        } else {
            for (int j = 0; j < nodes[i].children_count; j++) {
                fprintf(file, " %s", nodes[i].children[j]->name);
            }
        }
        fprintf(file, "\n");
    }
}

BinaryTree* findBinaryNode(BinaryTree nodes[], int count, int data) {
    for (int i = 0; i < count; i++) {
        if (nodes[i].data == data) {
            return &nodes[i];
        }
    }
    return NULL;
}

void addBinaryNodeToArr(BinaryTree* node, BinaryTree** arr, int* count) {
    // не добавляем узел если он 0
    if (node->data == 0) {
        return;
    }

    arr[count] = node;
}

int main() {
    printf("Hello, World!\n");

    BinaryTree** nodes;

    FILE *inFile = fopen("input.txt", "r"), *outFile = fopen("output.txt", "w");

    int count = 0;
    int *name, *left, *right;
    while (fscanf(inFile, "%d %d %d", name, left, right) != EOF) {
        BinaryTree* currentNode = findBinaryNode(*nodes, count, *name);
        if (!currentNode) {
            nodes[++count] = currentNode;
        }

        currentNode->data = *name;

        BinaryTree* leftChild = addLeftChild(currentNode, *left);
        BinaryTree* rightChild = addRightChild(currentNode, *right);


    }

    return 0;
}
