#include <iostream>
#include <sstream>

using namespace std;

// Структура узла АВЛ-дерева
struct NodeT {
    int key;
    int height;
    NodeT* left;
    NodeT* right;

    NodeT(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
};

// Функция для получения высоты узла
int heightTree(NodeT* n) {
    return n ? n->height : 0;
}

// Функция для получения баланса узла
int getBalance(NodeT* n) {
    return n ? heightTree(n->left) - heightTree(n->right) : 0;
}

// Функция для обновления высоты узла
void updateHeight(NodeT* n) {
    if (n) {
        n->height = 1 + max(heightTree(n->left), heightTree(n->right));
    }
}

// Правое вращение вокруг узла y
NodeT* rotateRight(NodeT* y) {
    NodeT* x = y->left;
    NodeT* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// Левое вращение вокруг узла x
NodeT* rotateLeft(NodeT* x) {
    NodeT* y = x->right;
    NodeT* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// Вставка узла в АВЛ-дерево
NodeT* insertTree(NodeT* node, int key) {
    if (!node) return new NodeT(key);

    if (key < node->key) {
        node->left = insertTree(node->left, key);
    } else if (key > node->key) {
        node->right = insertTree(node->right, key);
    } else {
        return node;  // Дубликаты не допускаются
    }

    updateHeight(node);

    // Проверка баланса узла и балансировка
    int balance = getBalance(node);

    // Левый поворот
    if (balance > 1 && key < node->left->key) {
        return rotateRight(node);
    }

    // Правый поворот
    if (balance < -1 && key > node->right->key) {
        return rotateLeft(node);
    }

    // Левый-правый поворот
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Правый-левый поворот
    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Поиск узла по ключу
NodeT* searchTree(NodeT* root, int key) {
    if (!root || root->key == key) {
        return root;
    }

    if (key < root->key) {
        return searchTree(root->left, key);
    }

    return searchTree(root->right, key);
}

// Функция для нахождения узла с минимальным значением
NodeT* minValueNode(NodeT* node) {
    NodeT* current = node;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

// Удаление узла из АВЛ-дерева
NodeT* deleteNodeT(NodeT* root, int key) {
    if (!root) return root;

    if (key < root->key) {
        root->left = deleteNodeT(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNodeT(root->right, key);
    } else {
        // Узел найден
        if (!root->left || !root->right) {
            NodeT* temp = root->left ? root->left : root->right;

            if (!temp) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp;
            }
            delete temp;
        } else {
            NodeT* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNodeT(root->right, temp->key);
        }
    }

    if (!root) return root;

    updateHeight(root);

    int balance = getBalance(root);

    // Левый поворот
    if (balance > 1 && getBalance(root->left) >= 0) {
        return rotateRight(root);
    }

    // Правый поворот
    if (balance < -1 && getBalance(root->right) <= 0) {
        return rotateLeft(root);
    }

    // Левый-правый поворот
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Правый-левый поворот
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Обход дерева в порядке возрастания
void inOrder(NodeT* root) {
    if (root) {
        inOrder(root->left);
        cout << root->key << " ";
        inOrder(root->right);
    }
}

int main() {
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

    return 0;
}
