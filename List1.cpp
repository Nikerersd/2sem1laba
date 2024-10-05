#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
};

void addToHead(Node*& head, int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = head;
    head = newNode;
}

void addToTail(Node*& head, int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void removeHead(Node*& head) {
    if (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void removeTail(Node*& head) {
    if (head == nullptr) {
        return;
    }
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
    } 
    else {
        Node* temp = head;
        while (temp->next->next != nullptr) {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = nullptr;
    }
}

void removeByValue(Node*& head, int value) {
    if (head == nullptr) {
        return;
    }

    if (head->data == value) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node* temp = head;
    while (temp->next != nullptr && temp->next->data != value) {
        temp = temp->next;
    }

    if (temp->next != nullptr) {
        Node* toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
    }
}

bool search(Node* head, int value) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data == value) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void printList(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "nullptr" << endl;
}

void clearList(Node*& head) {
    while (head != nullptr) {
        removeHead(head);
    }
}

int main() {
    Node* head = nullptr;

    addToHead(head, 10);
    addToTail(head, 20);
    addToHead(head, 5);

    cout << "Список после добавления элементов: ";
    printList(head);

    removeHead(head);
    cout << "Список после удаления головы: ";
    printList(head);

    removeTail(head);
    cout << "Список после удаления хвоста: ";
    printList(head);

    addToTail(head, 30);
    addToTail(head, 40);
    cout << "Список после добавления элементов в хвост: ";
    printList(head);

    removeByValue(head, 30);
    cout << "Список после удаления элемента со значением 30: ";
    printList(head);

    cout << "Поиск элемента 40: " << (search(head, 40) ? "Найден" : "Не найден") << std::endl;

    clearList(head);
    cout << "Список после очистки: ";
    printList(head);

    return 0;
}
