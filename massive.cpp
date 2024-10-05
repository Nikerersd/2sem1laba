#include <iostream>

using namespace std;

// Структура для массива
struct Array {
    int* data;       // Указатель на массив
    int size;        // Текущий размер массива
    int capacity;    // Максимальная вместимость массива
};

// Инициализация массива с заданной емкостью
void init(Array& arr, int cap) {
    arr.data = new int[cap];
    arr.size = 0;
    arr.capacity = cap;
}

// Освобождение памяти
void destroy(Array& arr) {
    delete[] arr.data;
    arr.data = nullptr;
    arr.size = 0;
    arr.capacity = 0;
}

// Добавление элемента в конец массива
void append(Array& arr, int value) {
    if (arr.size >= arr.capacity) {
        // Увеличение емкости массива
        arr.capacity *= 2;
        int* newData = new int[arr.capacity];
        for (int i = 0; i < arr.size; ++i) {
            newData[i] = arr.data[i];
        }
        delete[] arr.data;
        arr.data = newData;
    }
    arr.data[arr.size++] = value;
}

// Вставка элемента по индексу
void insert(Array& arr, int index, int value) {
    if (index < 0 || index > arr.size) {
        cerr << "Индекс за пределами допустимого" << endl;
        return;
    }
    if (arr.size >= arr.capacity) {
        arr.capacity *= 2;
        int* newData = new int[arr.capacity];
        for (int i = 0; i < arr.size; ++i) {
            newData[i] = arr.data[i];
        }
        delete[] arr.data;
        arr.data = newData;
    }
    for (int i = arr.size; i > index; --i) {
        arr.data[i] = arr.data[i - 1];
    }
    arr.data[index] = value;
    arr.size++;
}

// Получение элемента по индексу
int get(const Array& arr, int index) {
    if (index < 0 || index >= arr.size) {
        cerr << "Индекс за пределами допустимого" << endl;
        return -1;
    }
    return arr.data[index];
}

// Удаление элемента по индексу
void remove(Array& arr, int index) {
    if (index < 0 || index >= arr.size) {
        cerr << "Индекс за пределами допустимого" << endl;
        return;
    }
    for (int i = index; i < arr.size - 1; ++i) {
        arr.data[i] = arr.data[i + 1];
    }
    arr.size--;
}

// Замена элемента по индексу
void replace(Array& arr, int index, int value) {
    if (index < 0 || index >= arr.size) {
        cerr << "Индекс за пределами допустимого" << endl;
        return;
    }
    arr.data[index] = value;
}

// Получение длины массива
int length(const Array& arr) {
    return arr.size;
}

// Вывод элементов массива
void display(const Array& arr) {
    for (int i = 0; i < arr.size; ++i) {
        cout << arr.data[i] << " ";
    }
    cout << endl;
}

// Основная функция для тестирования
int main() {
    Array arr;

    // Инициализация массива с начальной емкостью 2
    init(arr, 2);

    append(arr, 10);
    append(arr, 20);
    append(arr, 30); // Увеличится емкость
    display(arr); // Вывод: 10 20 30

    insert(arr, 1, 15);
    display(arr); // Вывод: 10 15 20 30

    remove(arr, 2);
    display(arr); // Вывод: 10 15 30

    replace(arr, 0, 5);
    display(arr); // Вывод: 5 15 30

    cout << "Length: " << length(arr) << endl; // Вывод: 3

    // Освобождение памяти
    destroy(arr);

    return 0;
}
