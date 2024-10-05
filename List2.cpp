#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node* previous;
};

struct DoubleList {
    Node* head;
    Node* tail;
};

void addToHead(DoubleList& list, int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = list.head;
    newNode->previous = nullptr;

    if (list.head != nullptr) {
        list.head->previous = newNode;
    } 
    else {
        list.tail = newNode;
    }
    list.head = newNode;
}

void addToTail(DoubleList& list, int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;
    newNode->previous = list.tail;

    if (list.tail != nullptr) {
        list.tail->next = newNode;
    } else {
        list.head = newNode;
    }
    list.tail = newNode;
}

void removeFromHead(DoubleList& list) {
    if (list.head == nullptr) return;

    Node* temp = list.head;
    list.head = list.head->next;

    if (list.head != nullptr) {
        list.head->previous = nullptr;
    } else {
        list.tail = nullptr;
    }
    delete temp;
}

void removeFromTail(DoubleList& list) {
    if (list.tail == nullptr) return;

    Node* temp = list.tail;
    list.tail = list.tail->previous;

    if (list.tail != nullptr) {
        list.tail->next = nullptr;
    } else {
        list.head = nullptr;
    }
    delete temp;
}

void removeByValue(DoubleList& list, int value) {
    Node* temp = list.head;

    while (temp != nullptr) {
        if (temp->data == value) {
            if (temp->previous != nullptr) {
                temp->previous->next = temp->next;
            } 
            else {
                list.head = temp->next; // Удаляемый элемент - это голова
            }

            if (temp->next != nullptr) {
                temp->next->previous = temp->previous;
            } 
            else {
                list.tail = temp->previous; // Удаляемый элемент - это хвост
            }

            delete temp;
            return;
        }
        temp = temp->next;
    }
}

Node* find(DoubleList& list, int value) {
    Node* temp = list.head;
    while (temp != nullptr) {
        if (temp->data == value) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

void printList(DoubleList& list) {
    Node* temp = list.head;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main() {
    DoubleList list;
    list.head = nullptr;
    list.tail = nullptr;

    addToHead(list, 10);
    addToTail(list, 20);
    addToHead(list, 5);
    printList(list);

    removeFromHead(list);
    printList(list);

    removeByValue(list, 20);
    printList(list);

    addToTail(list, 30);
    addToTail(list, 40);
    printList(list);

    removeFromTail(list);
    printList(list);

    return 0;
}
