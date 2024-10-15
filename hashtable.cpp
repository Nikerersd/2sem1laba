#include <iostream>
#include <string>
#include <sstream>

using namespace std;

const int TABLE_SIZE = 10; // Размер хеш-таблицы

// Структура для хранения ключ-значение и указателя на следующий элемент
struct HashTable {
    string key;
    string value;
    HashTable* next; // Указатель на следующий элемент в цепочке
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
void insertTable(HashTable* table[], const string& key, const string& value) {
    int index = hashFunction(key);
    HashTable* newNode = new HashTable{key, value, nullptr};

    // Проверяем, есть ли уже элементы по этому индексу
    if (table[index] == nullptr) {
        table[index] = newNode; // Если нет, добавляем как первый элемент
    } else {
        // Если есть, ищем, существует ли уже элемент с таким ключом
        HashTable* temp = table[index];
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
string getValueTable(HashTable* table[], const string& key) {
    int index = hashFunction(key);
    HashTable* temp = table[index];
    
    while (temp != nullptr) {
        if (temp->key == key) {
            return temp->value; // Возвращаем значение, если ключ найден
        }
        temp = temp->next;
    }
    return "Key not found"; // Если ключ не найден
}

// Удаление элемента по ключу
void removeValueTable(HashTable* table[], const string& key) {
    int index = hashFunction(key);
    HashTable* temp = table[index];
    HashTable* prev = nullptr;

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
void printTable(HashTable* table[]) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        cout << "Index " << i << ": ";
        HashTable* temp = table[i];
        while (temp != nullptr) {
            cout << "[" << temp->key << ": " << temp->value << "] ";
            temp = temp->next;
        }
        cout << endl;
    }
}

// Очистка памяти, освобождение всех узлов
void freeTable(HashTable* table[]) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        HashTable* temp = table[i];
        while (temp != nullptr) {
            HashTable* toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }
    }
}

int main() {
     HashTable* hashTable[TABLE_SIZE] = {nullptr}; // Инициализация пустой хеш-таблицы

    string command;
    string key, value;

    cout << "Enter a command (insert, get, remove, print, clear, exit):" << endl;

    // Основной цикл для ввода команд
    while (true) {
        cout << "> ";
        getline(cin, command);

        // Используем строковый поток для разделения команды на части
        stringstream ss(command);
        string action;
        ss >> action;

        if (action == "insert") {
            // Чтение ключа и значения для вставки
            if (ss >> key >> value && !key.empty() && !value.empty()) {
                insertTable(hashTable, key, value);
                cout << "Inserted [" << key << ": " << value << "]" << endl;
            } else {
                cout << "Invalid input. Usage: insert <key> <value>" << endl;
            }
        } 
        else if (action == "get") {
            // Чтение ключа для получения значения
            if (ss >> key && !key.empty()) {
                cout << "Value: " << getValueTable(hashTable, key) << endl;
            } else {
                cout << "Invalid input. Usage: get <key>" << endl;
            }
        }
        else if (action == "remove") {
            // Чтение ключа для удаления
            if (ss >> key && !key.empty()) {
                removeValueTable(hashTable, key);
            } else {
                cout << "Invalid input. Usage: remove <key>" << endl;
            }
        } 
        else if (action == "print") {
            // Печать всей таблицы
            printTable(hashTable);
        } 
        else if (action == "clear") {
            // Очистка таблицы
            freeTable(hashTable);
            cout << "Hash table cleared." << endl;
        } 
        else if (action == "exit") {
            // Выход из программы
            freeTable(hashTable);
            cout << "Exiting..." << endl;
            break;
        } 
        else {
            cout << "Unknown command. Available commands: insert, get, remove, print, clear, exit." << endl;
        }
    }

    return 0;
}
