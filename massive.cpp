#include <iostream>
#include <sstream>

using namespace std;

struct Array {
    int* data;
    int size;        // Текущий размер массива
    int capacity;    // Максимальная вместимость массива
};

void initArray(Array& arr, int cap) {
    arr.data = new int[cap];
    arr.size = 0;
    arr.capacity = cap;
}

void destroyArray(Array& arr) {
    delete[] arr.data;
    arr.data = nullptr;
    arr.size = 0;
    arr.capacity = 0;
}

void appendArray(Array& arr, int value) {
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

void insertArray(Array& arr, int index, int value) {
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

int getArray(const Array& arr, int index) {
    if (index < 0 || index >= arr.size) {
        cerr << "Индекс за пределами допустимого" << endl;
        return -1;
    }
    return arr.data[index];
}

void removeArray(Array& arr, int index) {
    if (index < 0 || index >= arr.size) {
        cerr << "Индекс за пределами допустимого" << endl;
        return;
    }
    for (int i = index; i < arr.size - 1; ++i) {
        arr.data[i] = arr.data[i + 1];
    }
    arr.size--;
}

void replaceArray(Array& arr, int index, int value) {
    if (index < 0 || index >= arr.size) {
        cerr << "Индекс за пределами допустимого" << endl;
        return;
    }
    arr.data[index] = value;
}

int lengthArray(const Array& arr) {
    return arr.size;
}

void displayArray(const Array& arr) {
    for (int i = 0; i < arr.size; ++i) {
        cout << arr.data[i] << " ";
    }
    cout << endl;
}

int main() {
    Array arr;
    initArray(arr, 2);

    string command;
    int index, value;

    cout << "Enter a command (append, insert, remove, replace, get, display, length, exit):" << endl;

    while (true) {
        cout << "> ";
        getline(cin, command);

        stringstream ss(command);
        string action;
        ss >> action;

        if (action == "append") {
            ss >> value;
            if (!ss.fail()) {
                appendArray(arr, value);
                cout << "Appended: " << value << endl;
            } else {
                cout << "Invalid input. Usage: append <value>" << endl;
            }
        } else if (action == "insert") {
            ss >> index >> value;
            if (!ss.fail()) {
                insertArray(arr, index, value);
                cout << "Inserted " << value << " at index " << index << endl;
            } else {
                cout << "Invalid input. Usage: insert <index> <value>" << endl;
            }
        } else if (action == "remove") {
            ss >> index;
            if (!ss.fail()) {
                removeArray(arr, index);
                cout << "Removed element at index " << index << endl;
            } else {
                cout << "Invalid input. Usage: remove <index>" << endl;
            }
        } else if (action == "replace") {
            ss >> index >> value;
            if (!ss.fail()) {
                replaceArray(arr, index, value);
                cout << "Replaced element at index " << index << " with " << value << endl;
            } else {
                cout << "Invalid input. Usage: replace <index> <value>" << endl;
            }
        } else if (action == "get") {
            ss >> index;
            if (!ss.fail()) {
                int result = getArray(arr, index);
                if (result != -1) {
                    cout << "Element at index " << index << ": " << result << endl;
                }
            } else {
                cout << "Invalid input. Usage: get <index>" << endl;
            }
        } else if (action == "display") {
            cout << "Array content: ";
            displayArray(arr);
        } else if (action == "length") {
            cout << "Array length: " << lengthArray(arr) << endl;
        } else if (action == "exit") {
            cout << "Exiting..." << endl;
            break;
        } else {
            cout << "Unknown command. Available commands: append, insert, remove, replace, get, display, length, exit." << endl;
        }
    }

    destroyArray(arr);
    return 0;
}
