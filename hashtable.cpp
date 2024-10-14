#include <iostream>
#include <string>

using namespace std;

const int TABLE_SIZE = 10; // Размер хеш-таблицы

// Структура для хранения ключ-значение и указателя на следующий элемент
struct Node {
    string key;
    string value;
    Node* next; // Указатель на следующий элемент в цепочке
};

// Хеш-функция
int hashFunction(const string& key) {
    int hash = 0;
    for (char ch : key) {
        hash += ch;
    }
    return hash % TABLE_SIZE;
}

// Добавление элемента (ключ-значение)
void insert(Node* table[], const string& key, const string& value) {
    int index = hashFunction(key);
    Node* newNode = new Node{key, value, nullptr};

    // Проверяем, есть ли уже элементы по этому индексу
    if (table[index] == nullptr) {
        table[index] = newNode; // Если нет, добавляем как первый элемент
    } else {
        // Если есть, ищем, существует ли уже элемент с таким ключом
        Node* temp = table[index];
        while (temp != nullptr) {
            if (temp->key == key) {
                // Обновляем значение, если ключ найден
                temp->value = value;
                delete newNode; // Удаляем ненужный новый узел
                return;
            }
            if (temp->next == nullptr) {
                break; // Найдена последняя нода
            }
            temp = temp->next;
        }
        // Добавляем новый узел в конец списка
        temp->next = newNode;
    }
}

// Получение значения по ключу
string get(Node* table[], const string& key) {
    int index = hashFunction(key);
    Node* temp = table[index];
    
    while (temp != nullptr) {
        if (temp->key == key) {
            return temp->value; // Возвращаем значение, если ключ найден
        }
        temp = temp->next;
    }
    return "Key not found"; // Если ключ не найден
}

// Удаление элемента по ключу
void remove(Node* table[], const string& key) {
    int index = hashFunction(key);
    Node* temp = table[index];
    Node* prev = nullptr;

    while (temp != nullptr) {
        if (temp->key == key) {
            if (prev == nullptr) {
                // Удаляем первый элемент в цепочке
                table[index] = temp->next;
            } else {
                // Удаляем элемент в середине или конце цепочки
                prev->next = temp->next;
            }
            delete temp; // Освобождаем память
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    cout << "Key not found" << endl; // Если ключ не найден
}

// Печать всей хеш-таблицы для проверки
void printTable(Node* table[]) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        cout << "Index " << i << ": ";
        Node* temp = table[i];
        while (temp != nullptr) {
            cout << "[" << temp->key << ": " << temp->value << "] ";
            temp = temp->next;
        }
        cout << endl;
    }
}

// Очистка памяти, освобождение всех узлов
void freeTable(Node* table[]) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        Node* temp = table[i];
        while (temp != nullptr) {
            Node* toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }
    }
}

int main() {
    Node* hashTable[TABLE_SIZE] = {nullptr}; // Инициализация пустой хеш-таблицы

    insert(hashTable, "apple", "green");
    insert(hashTable, "banana", "yellow");
    insert(hashTable, "cherry", "red");
    insert(hashTable, "grape", "purple");
    
    printTable(hashTable);
    
    cout << "Get 'apple': " << get(hashTable, "apple") << endl;
    cout << "Get 'banana': " << get(hashTable, "banana") << endl;
    
    remove(hashTable, "cherry");
    cout << "After removing 'cherry':\n";
    printTable(hashTable);

    // Освобождение памяти
    freeTable(hashTable);
    
    return 0;
}
