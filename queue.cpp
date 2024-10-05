#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
};

struct Queue {
    Node* head;
    Node* tail;
};

Node* createNode(int val) {
    Node* newNode = new Node;
    newNode->data = val;
    newNode->next = nullptr;  // Инициализируем указатель на следующий узел
    return newNode;
}

void enqueue(Queue& q, int item) {
    Node* newNode = createNode(item);
    if (q.tail == nullptr) {
        q.head = q.tail = newNode;
        return;
    }
    q.tail->next = newNode; // Добавляем новый узел в конец очереди
    q.tail = newNode; // Обновляем указатель на последний элемент
}

int dequeue(Queue& q) {
    if (q.head == nullptr) {
        cout << "Очередь пуста" << endl;
        return -1;
    }
    Node* temp = q.head;
    int item = q.head->data;
    q.head = q.head->next;
    if (q.head == nullptr) {
        q.tail = nullptr;
    }
    delete temp;
    return item;
}

void printQueue (Queue& q) {
    if (q.head == nullptr) {
        cout << "Очередь пуста" << endl;
        return;
    }
    Node* temp = q.head;
    cout << "Очередь: ";
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main() {
    Queue q; // Создаем очередь
    q.head = q.tail = nullptr; // Инициализируем указатели на первый и последний элементы

    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);
    
    printQueue(q);

    dequeue(q);
    dequeue(q);

    printQueue(q);

    dequeue(q); // Удаляем последний элемент
    dequeue(q); // Попытка удалить из пустой очереди

    return 0;
}
