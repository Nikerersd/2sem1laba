#include <iostream>
#include <sstream>

using namespace std;

void hashtableCmds(HashTable& hashTable) {
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
}

void list1Cmds (ListOne*& head) {
    ListOne* head = nullptr;
    string command;
    int value;

    cout << "Enter a command (addhead, addtail, removehead, removetail, removevalue, search, print, clear, exit):" << endl;

    while (true) {
        cout << "> ";
        getline(cin, command);

        stringstream ss(command);
        string action;
        ss >> action;

        if (action == "addhead") {
            ss >> value;
            if (!ss.fail()) {
                addToHeadL1(head, value);
                cout << "Added to head: " << value << endl;
            } else {
                cout << "Invalid input. Usage: addhead <value>" << endl;
            }
        } else if (action == "addtail") {
            ss >> value;
            if (!ss.fail()) {
                addToTailL1(head, value);
                cout << "Added to tail: " << value << endl;
            } else {
                cout << "Invalid input. Usage: addtail <value>" << endl;
            }
        } else if (action == "removehead") {
            removeHeadL1(head);
            cout << "Head removed" << endl;
        } else if (action == "removetail") {
            removeTailL1(head);
            cout << "Tail removed" << endl;
        } else if (action == "removevalue") {
            ss >> value;
            if (!ss.fail()) {
                removeByValueL1(head, value);
                cout << "Removed value: " << value << endl;
            } else {
                cout << "Invalid input. Usage: removevalue <value>" << endl;
            }
        } else if (action == "search") {
            ss >> value;
            if (!ss.fail()) {
                cout << "Search result for " << value << ": " 
                     << (searchL1(head, value) ? "Found" : "Not found") << endl;
            } else {
                cout << "Invalid input. Usage: search <value>" << endl;
            }
        } else if (action == "print") {
            cout << "List content: ";
            printList1(head);
        } else if (action == "clear") {
            clearList1(head);
            cout << "List cleared" << endl;
        } else if (action == "exit") {
            clearList1(head);
            cout << "Exiting..." << endl;
            break;
        } else {
            cout << "Unknown command. Available commands: addhead, addtail, removehead, removetail, removevalue, search, print, clear, exit." << endl;
        }
    }
}

void list2Cmds (DoubleList*& list) {
    DoubleList list;
    list.head = nullptr;
    list.tail = nullptr;

    string command;
    int value;

    cout << "Enter a command (addhead, addtail, removehead, removetail, removevalue, find, print, exit):" << endl;

    while (true) {
        cout << "> ";
        getline(cin, command);

        stringstream ss(command);
        string action;
        ss >> action;

        if (action == "addhead") {
            ss >> value;
            if (!ss.fail()) {
                addToHeadL2(list, value);
                cout << "Added to head: " << value << endl;
            } else {
                cout << "Invalid input. Usage: addhead <value>" << endl;
            }
        } else if (action == "addtail") {
            ss >> value;
            if (!ss.fail()) {
                addToTailL2(list, value);
                cout << "Added to tail: " << value << endl;
            } else {
                cout << "Invalid input. Usage: addtail <value>" << endl;
            }
        } else if (action == "removehead") {
            removeFromHeadL2(list);
            cout << "Head removed" << endl;
        } else if (action == "removetail") {
            removeFromTailL2(list);
            cout << "Tail removed" << endl;
        } else if (action == "removevalue") {
            ss >> value;
            if (!ss.fail()) {
                removeByValueL2(list, value);
                cout << "Removed value: " << value << endl;
            } else {
                cout << "Invalid input. Usage: removevalue <value>" << endl;
            }
        } else if (action == "find") {
            ss >> value;
            if (!ss.fail()) {
                NodeL* result = findL2(list, value);
                cout << (result ? "Found" : "Not found") << endl;
            } else {
                cout << "Invalid input. Usage: find <value>" << endl;
            }
        } else if (action == "print") {
            cout << "List content: ";
            printList2(list);
        } else if (action == "exit") {
            cout << "Exiting..." << endl;
            break;
        } else {
            cout << "Unknown command. Available commands: addhead, addtail, removehead, removetail, removevalue, find, print, exit." << endl;
        }
    }
}

void arrayCmds (Array*& arr) {
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
}

void queueCmds (Queue& q) {
    Queue q;
    q.head = q.tail = nullptr;

    string command;
    int value;

    cout << "Введите команду (enqueue, dequeue, print, exit):" << endl;

    while (true) {
        cout << "> ";
        getline(cin, command);

        stringstream ss(command);
        string action;
        ss >> action;

        if (action == "enqueue") {
            ss >> value;
            if (!ss.fail()) {
                enqueue(q, value);
                cout << "Элемент " << value << " добавлен в очередь." << endl;
            } else {
                cout << "Неверный ввод. Используйте: enqueue <value>" << endl;
            }
        } else if (action == "dequeue") {
            int result = dequeue(q);
            if (result != -1) {
                cout << "Удален элемент: " << result << endl;
            }
        } else if (action == "print") {
            printQueue(q);
        } else if (action == "exit") {
            cout << "Выход..." << endl;
            break;
        } else {
            cout << "Неизвестная команда. Доступные команды: enqueue, dequeue, print, exit." << endl;
        }
    }
}

void stackCmds (Stack& stack) {
    Stack stack;
    stack.top = nullptr;

    string command;
    int value;

    cout << "Введите команду (push, pop, print, exit):" << endl;

    while (true) {
        cout << "> ";
        getline(cin, command);

        stringstream ss(command);
        string action;
        ss >> action;

        if (action == "push") {
            ss >> value;
            if (!ss.fail()) {
                pushStack(stack, value);
                cout << "Элемент " << value << " добавлен в стек." << endl;
            } else {
                cout << "Неверный ввод. Используйте: push <value>" << endl;
            }
        } else if (action == "pop") {
            popStack(stack);
        } else if (action == "print") {
            printStack(stack);
        } else if (action == "exit") {
            cout << "Выход..." << endl;
            break;
        } else {
            cout << "Неизвестная команда. Доступные команды: push, pop, print, exit." << endl;
        }
    }
}

void treeCmds (NodeT*& root) {
    NodeT* root = nullptr;
    string command;
    int value;

    cout << "Введите команду (insert, delete, search, print, exit):" << endl;

    while (true) {
        cout << "> ";
        getline(cin, command);

        stringstream ss(command);
        string action;
        ss >> action;

        if (action == "insert") {
            ss >> value;
            if (!ss.fail()) {
                root = insertTree(root, value);
                cout << "Элемент " << value << " добавлен." << endl;
            } else {
                cout << "Неверный ввод. Используйте: insert <value>" << endl;
            }
        } else if (action == "delete") {
            ss >> value;
            if (!ss.fail()) {
                root = deleteNodeT(root, value);
                cout << "Элемент " << value << " удален." << endl;
            } else {
                cout << "Неверный ввод. Используйте: delete <value>" << endl;
            }
        } else if (action == "search") {
            if (ss >> value) {  // Проверяем, был ли введен аргумент
                NodeT* result = searchTree(root, value);
                if (result) {
                    cout << "Элемент " << value << " найден." << endl;
                } else {
                    cout << "Элемент " << value << " не найден." << endl;
                }
            } 
            else {
                cout << "Неверный ввод. Используйте: search <value>" << endl;
            }
        } 
        else if (action == "print") {
            cout << "Обход дерева in-order: ";
            inOrder(root);
            cout << endl;
        } 
        else if (action == "exit") {
            cout << "Выход..." << endl;
            break;
        } 
        else {
            cout << "Неизвестная команда. Доступные команды: insert, delete, search, print, exit." << endl;
        }
    }
}

int main() {

}