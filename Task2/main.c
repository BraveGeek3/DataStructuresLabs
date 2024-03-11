#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CHUNK 6

void quickSort(int *arr, int low, int high);
void bubbleSort(int *arr, int n);
int binarySearch(int *arr, int l, int r, int x);
int partition(int *arr, int low, int high);
void swap(int *a, int *b);
void printArr(int *arr, int N);

int main() {
    int N, element, index;

    // Запросите N и элемент для поиска
    printf("Enter number of elements: ");
    scanf("%d", &N);

    int arr[N];

    // Инициализация генератора случайных чисел
    srand(time(0));

    // Генерация случайных чисел
    for(int i = 0; i < N; i++) {
        arr[i] = rand() % 100; // Генерация числа в диапазоне от 0 до 99
    }

    printf("Random array\n");
    printArr(arr, N);

    // Частичная быстрая сортировка с порогом
    quickSort(arr, 0, N - 1);
    printf("Array after quicksort\n");
    printArr(arr, N);


    // Пузырьковая сортировка
    bubbleSort(arr, N);
    printf("Array after bubble sort\n");
    printArr(arr, N);


    printf("Enter the element to search: ");
    scanf("%d", &element);
    // Бинарный поиск
    index = binarySearch(arr, 0, N - 1, element);

    // Вывод результатов
    printf("Sorted array:\n");
    printArr(arr, N);

    if (index != -1) {
        printf("Element found at index: %d\n", index);
    } else {
        printf("Element not found in the array\n");
    }

    return 0;
}

void printArr(int *arr, int N) {
    for (int i = 0; i < N; ++i) {
        printf("%d ", arr[i]);
    }

    printf("\n");
    return;
}

void quickSort(int *arr, int low, int high) {
    if (low < high) {
        if (high - low > CHUNK) {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }
}

int partition(int *arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void bubbleSort(int *arr, int n) {
    int i, j;
    for (i = 0; i < n-1; i++)
        for (j = 0; j < n-i-1; j++)
            if (arr[j] > arr[j+1])
                swap(&arr[j], &arr[j+1]);
}

int binarySearch(int *arr, int l, int r, int x) {
    while (l <= r) {
        int m = l + (r-l) / 2;
        if (arr[m] == x)
            return m;
        if (arr[m] < x)
            l = m + 1;
        else
            r = m - 1;
    }
    return -1;
}

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}
