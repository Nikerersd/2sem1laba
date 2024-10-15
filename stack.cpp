#include <iostream>
#include <sstream>

using namespace std;

struct NodeS {
    int data;
    NodeS* next;
};

struct Stack {
    NodeS* top;
};

void pushStack(Stack& stack, int value) {
    NodeS* newNode = new NodeS(); 
    newNode->data = value;
    newNode->next = stack.top;   // Новый узел указывает на текущую вершину
    stack.top = newNode;         // Новый узел становится вершиной
}

void popStack(Stack& stack) {
    if (stack.top == nullptr) {
        cout << "Стек пуст" << endl;
        return;
    }
    NodeS* temp = stack.top;
    stack.top = stack.top->next;
    delete temp;
}

void printStack(Stack& stack) {
    if (stack.top == nullptr) {
        cout << "Стек пуст" << endl;
        return;
    }
    NodeS* temp = stack.top;
    cout << "Элементы стека: ";
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main() {
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

    return 0;
}
