#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>

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

void printTree(NodeT* root, int space = 0, int level = 0) {
    if (root == nullptr) return;

    space += 5;

    printTree(root->right, space, level + 1);

    cout << endl;
    cout << setw(space) << root->key << endl;

    printTree(root->left, space, level + 1);
}

void freeTree(NodeT* root) {
    if (root == nullptr) return;

    freeTree(root->left);
    freeTree(root->right);

    delete root;
}

void writeTreeToFile(NodeT* root, ofstream& file, int space = 0, int level = 0) {

    if (root == nullptr) return;

    space += 5;

    // Рекурсивный вызов для правого поддерева
    writeTreeToFile(root->right, file, space, level + 1);

    // Запись текущего узла в файл
    file << endl;
    file << setw(space) << root->key << endl;

    // Рекурсивный вызов для левого поддерева
    writeTreeToFile(root->left, file, space, level + 1);
}

void writeAVLTreeToFile(NodeT* root, const string& filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Ошибка при открытии файла для записи" << endl;
        return;
    }

    writeTreeToFile(root, file);
    
    file.close();
}