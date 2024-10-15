#include <iostream>
#include <sstream>

using namespace std;

struct ListOne {
    int data;
    ListOne* next;
};

void addToHeadL1(ListOne*& head, int value) {
    ListOne* newNode = new ListOne;
    newNode->data = value;
    newNode->next = head;
    head = newNode;
}

void addToTailL1(ListOne*& head, int value) {
    ListOne* newNode = new ListOne;
    newNode->data = value;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
    } else {
        ListOne* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void removeHeadL1(ListOne*& head) {
    if (head != nullptr) {
        ListOne* temp = head;
        head = head->next;
        delete temp;
    }
}

void removeTailL1(ListOne*& head) {
    if (head == nullptr) {
        return;
    }
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
    } 
    else {
        ListOne* temp = head;
        while (temp->next->next != nullptr) {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = nullptr;
    }
}

void removeByValueL1(ListOne*& head, int value) {
    if (head == nullptr) {
        return;
    }

    if (head->data == value) {
        ListOne* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    ListOne* temp = head;
    while (temp->next != nullptr && temp->next->data != value) {
        temp = temp->next;
    }

    if (temp->next != nullptr) {
        ListOne* toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
    }
}

bool searchL1(ListOne* head, int value) {
    ListOne* temp = head;
    while (temp != nullptr) {
        if (temp->data == value) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void printList1(ListOne* head) {
    ListOne* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "nullptr" << endl;
}

void clearList1(ListOne*& head) {
    while (head != nullptr) {
        removeHeadL1(head);
    }
}

int main() {
    ListOne* head = nullptr;
    string command;
    int value;

    cout << "Enter a command (addhead, addtail, removehead, removetail, removevalue, search, print, clear, exit):" << endl;

    // Основной цикл для ввода команд
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

    return 0;
}
