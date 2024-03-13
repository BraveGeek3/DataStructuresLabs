#include "../DataStructures/BinaryTree.c"
#include "../DataStructures/NaryTree.c"

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
        fprintf(file, "%d", nodes[i].data);
        if (nodes[i].children_count == 0) {
            fprintf(file, " NULL");
        } else {
            for (int j = 0; j < nodes[i].children_count; j++) {
                fprintf(file, " %d", nodes[i].children[j]->data);
            }
        }
        fprintf(file, "\n");
    }
}

BinaryTree* findBinaryNode(BinaryTree** nodes, int count, int data) {
    for (int i = 0; i < count; i++) {
        if (nodes[i]->data == data) {
            return nodes[i];
        }
    }
    return NULL;
}

void addBinaryNodeToArr(BinaryTree* node, BinaryTree** arr, int* count) {
    // не добавляем узел если он 0
    if (node->data == 0) {
        return;
    }

    arr[*count] = node;
}


int main() {
    printf("Start!\n");

    BinaryTree* tree = (BinaryTree*)malloc(sizeof(BinaryTree));
    BinaryTree** nodesArr = NULL;
    BinaryTree* temp;


    tree->left = NULL;
    tree->right = NULL;

    FILE *inFile = fopen("input.txt", "r"), *outFile = fopen("output.txt", "w");

    int count = 0;
    int data, left, right;
    while (fscanf(inFile, "%d %d %d", &data, &left, &right) != EOF) {
        BinaryTree* currentNode = NULL;
        if (count == 0) {
            tree->data = data;
            currentNode = tree;
            nodesArr = (BinaryTree**)realloc(nodesArr, sizeof(BinaryTree*) * (count + 1));
            nodesArr[count++] = currentNode;
        }

        currentNode = findBinaryNode(nodesArr, count, data);

        if ((temp = addLeftChild(currentNode, left)) != NULL) {
            nodesArr = (BinaryTree**)realloc(nodesArr, sizeof(BinaryTree*) * (count + 1));
            nodesArr[count] = temp;

            ++count;
        }

        if ((temp = addRightChild(currentNode, right)) != NULL) {
            nodesArr = (BinaryTree**)realloc(nodesArr, sizeof(BinaryTree*) * (count + 1));
            nodesArr[count] = currentNode;

            ++count;
        }
    }

    return 0;
}
