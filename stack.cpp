#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
};

struct Stack {
    Node* top;
};

void push(Stack& stack, int value) {
    Node* newNode = new Node(); 
    newNode->data = value;
    newNode->next = stack.top;   // Новый узел указывает на текущую вершину
    stack.top = newNode;         // Новый узел становится вершиной
}

void pop(Stack& stack) {
    if (stack.top == nullptr) {
        cout << "Стек пуст" << endl;
        return;
    }
    Node* temp = stack.top;
    stack.top = stack.top->next;
    delete temp;
}

void printStack(Stack& stack) {
    if (stack.top == nullptr) {
        cout << "Стек пуст" << endl;
        return;
    }
    Node* temp = stack.top;
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

    push(stack, 10);
    push(stack, 20);
    push(stack, 30);

    printStack(stack);

    pop(stack);

    printStack(stack);

    pop(stack);
    pop(stack);
    pop(stack); // Попытка удалить элемент из пустого стека

    return 0;
}
