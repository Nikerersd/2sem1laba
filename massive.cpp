#include <iostream>

using namespace std;

struct Array {
    int* data;
    int size;        // Текущий размер массива
    int capacity;    // Максимальная вместимость массива
};

void init(Array& arr, int cap) {
    arr.data = new int[cap];
    arr.size = 0;
    arr.capacity = cap;
}

void destroy(Array& arr) {
    delete[] arr.data;
    arr.data = nullptr;
    arr.size = 0;
    arr.capacity = 0;
}

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

int get(const Array& arr, int index) {
    if (index < 0 || index >= arr.size) {
        cerr << "Индекс за пределами допустимого" << endl;
        return -1;
    }
    return arr.data[index];
}

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

void replace(Array& arr, int index, int value) {
    if (index < 0 || index >= arr.size) {
        cerr << "Индекс за пределами допустимого" << endl;
        return;
    }
    arr.data[index] = value;
}

int length(const Array& arr) {
    return arr.size;
}

void display(const Array& arr) {
    for (int i = 0; i < arr.size; ++i) {
        cout << arr.data[i] << " ";
    }
    cout << endl;
}

int main() {
    Array arr;

    init(arr, 2);

    append(arr, 10);
    append(arr, 20);
    append(arr, 30);
    display(arr);

    insert(arr, 1, 15);
    display(arr);

    remove(arr, 2);
    display(arr);

    replace(arr, 0, 5);
    display(arr);

    cout << "Length: " << length(arr) << endl;

    destroy(arr);

    return 0;
}
