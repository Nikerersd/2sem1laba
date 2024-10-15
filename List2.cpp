#include <iostream>
#include <sstream>

using namespace std;

struct NodeL {
    int data;
    NodeL* next;
    NodeL* previous;
};

struct DoubleList {
    NodeL* head;
    NodeL* tail;
};

void addToHeadL2(DoubleList& list, int value) {
    NodeL* newNode = new NodeL;
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

void addToTailL2(DoubleList& list, int value) {
    NodeL* newNode = new NodeL;
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

void removeFromHeadL2(DoubleList& list) {
    if (list.head == nullptr) return;

    NodeL* temp = list.head;
    list.head = list.head->next;

    if (list.head != nullptr) {
        list.head->previous = nullptr;
    } else {
        list.tail = nullptr;
    }
    delete temp;
}

void removeFromTailL2(DoubleList& list) {
    if (list.tail == nullptr) return;

    NodeL* temp = list.tail;
    list.tail = list.tail->previous;

    if (list.tail != nullptr) {
        list.tail->next = nullptr;
    } else {
        list.head = nullptr;
    }
    delete temp;
}

void removeByValueL2(DoubleList& list, int value) {
    NodeL* temp = list.head;

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

NodeL* findL2(DoubleList& list, int value) {
    NodeL* temp = list.head;
    while (temp != nullptr) {
        if (temp->data == value) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

void printList2(DoubleList& list) {
    NodeL* temp = list.head;
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

    return 0;
}
