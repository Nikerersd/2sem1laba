#include <iostream>
#include <sstream>

using namespace std;

struct NodeQ {
    int data;
    NodeQ* next;
};

struct Queue {
    NodeQ* head;
    NodeQ* tail;
};

NodeQ* createNodeQ(int val) {
    NodeQ* newNode = new NodeQ;
    newNode->data = val;
    newNode->next = nullptr;  // Инициализируем указатель на следующий узел
    return newNode;
}

void enqueue(Queue& q, int item) {
    NodeQ* newNode = createNodeQ(item);
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
    NodeQ* temp = q.head;
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
    NodeQ* temp = q.head;
    cout << "Очередь: ";
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main() {
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

    return 0;
}
