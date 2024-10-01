#include <iostream>

// Структура для массива
struct DynamicArray {
    int* data;       // Указатель на массив
    int size;        // Текущий размер массива
    int capacity;    // Максимальная вместимость массива
};

// Инициализация массива с заданной емкостью
void init(DynamicArray& arr, int cap) {
    arr.data = new int[cap];
    arr.size = 0;
    arr.capacity = cap;
}

// Освобождение памяти
void destroy(DynamicArray& arr) {
    delete[] arr.data;
    arr.data = nullptr;
    arr.size = 0;
    arr.capacity = 0;
}

// Добавление элемента в конец массива
void append(DynamicArray& arr, int value) {
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
void insert(DynamicArray& arr, int index, int value) {
    if (index < 0 || index > arr.size) {
        std::cerr << "Index out of bounds" << std::endl;
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
int get(const DynamicArray& arr, int index) {
    if (index < 0 || index >= arr.size) {
        std::cerr << "Index out of bounds" << std::endl;
        return -1; // Возвращаем -1 в случае ошибки
    }
    return arr.data[index];
}

// Удаление элемента по индексу
void remove(DynamicArray& arr, int index) {
    if (index < 0 || index >= arr.size) {
        std::cerr << "Index out of bounds" << std::endl;
        return;
    }
    for (int i = index; i < arr.size - 1; ++i) {
        arr.data[i] = arr.data[i + 1];
    }
    arr.size--;
}

// Замена элемента по индексу
void replace(DynamicArray& arr, int index, int value) {
    if (index < 0 || index >= arr.size) {
        std::cerr << "Index out of bounds" << std::endl;
        return;
    }
    arr.data[index] = value;
}

// Получение длины массива
int length(const DynamicArray& arr) {
    return arr.size;
}

// Вывод элементов массива
void display(const DynamicArray& arr) {
    for (int i = 0; i < arr.size; ++i) {
        std::cout << arr.data[i] << " ";
    }
    std::cout << std::endl;
}

// Основная функция для тестирования
int main() {
    DynamicArray arr;

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

    std::cout << "Length: " << length(arr) << std::endl; // Вывод: 3

    // Освобождение памяти
    destroy(arr);

    return 0;
}
