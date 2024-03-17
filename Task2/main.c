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
    // Инициализируем переменные
    int N, element, index;

    // Считываем количество элементов в массиве
    printf("Введите количество элементов: ");
    scanf("%d", &N);
    if (N <= 0) {
        printf("Неверное значение количества элементов массива");
        return 1;
    }

    int arr[N];

    // Инициализация генератора случайных чисел
    srand(time(0));

    // Генерация случайных чисел
    for(int i = 0; i < N; i++) {
        arr[i] = rand() % 10000; // Генерация числа в диапазоне от 0 до 99
    }

    printf("Получившийся массив случайных чисел:\n");
    printArr(arr, N);

    // Частичная быстрая сортировка с порогом
    quickSort(arr, 0, N - 1);
    printf("Массив после быстрой сортировки\n");
    printArr(arr, N);


    // Пузырьковая сортировка
    bubbleSort(arr, N);
    printf("Массив после пузырьковой сортировки\n");
    printArr(arr, N);

    // Ввод элемента для поиска
    printf("Введите элемент для поиска:\n");
    scanf("%d", &element);
    // Бинарный поиск
    index = binarySearch(arr, 0, N - 1, element);

    // Вывод результатов
    printf("Отсортированный массив:\n");
    printArr(arr, N);

    if (index != -1) {
        printf("Найдем элемент с индексом: %d\n", index + 1);
    } else {
        printf("Элемент не найден...\n");
    }

    return 0;
}

// Вывод массива в консоль
void printArr(int *arr, int N) {
    for (int i = 0; i < N; ++i) {
        printf("%d ", arr[i]);
    }

    printf("\n");
    return;
}

// Быстрая сортировка
void quickSort(int *arr, int low, int high) {
    if (low < high) {
        // Если разница индексов больше пороговой, продолжаем сортировку
        if (high - low > CHUNK) {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }
}

// Сортировка массива
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

// Сортировка пузырьком
void bubbleSort(int *arr, int n) {
    int i, j;
    for (i = 0; i < n-1; i++)
        for (j = 0; j < n-i-1; j++)
            if (arr[j] > arr[j+1])
                swap(&arr[j], &arr[j+1]);
}

// Бинарный поиск
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

// Меняем местами элементы массива
void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}
