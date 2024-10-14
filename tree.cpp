#include <iostream>
using namespace std;

// Структура узла АВЛ-дерева
struct Node {
    int key;
    int height;
    Node* left;
    Node* right;

    Node(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
};

// Функция для получения высоты узла
int height(Node* n) {
    return n ? n->height : 0;
}

// Функция для получения баланса узла
int getBalance(Node* n) {
    return n ? height(n->left) - height(n->right) : 0;
}

// Функция для обновления высоты узла
void updateHeight(Node* n) {
    if (n) {
        n->height = 1 + max(height(n->left), height(n->right));
    }
}

// Правое вращение вокруг узла y
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// Левое вращение вокруг узла x
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// Вставка узла в АВЛ-дерево
Node* insert(Node* node, int key) {
    if (!node) return new Node(key);

    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
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
Node* search(Node* root, int key) {
    if (!root || root->key == key) {
        return root;
    }

    if (key < root->key) {
        return search(root->left, key);
    }

    return search(root->right, key);
}

// Функция для нахождения узла с минимальным значением
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

// Удаление узла из АВЛ-дерева
Node* deleteNode(Node* root, int key) {
    if (!root) return root;

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        // Узел найден
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;

            if (!temp) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp;
            }
            delete temp;
        } else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
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
void inOrder(Node* root) {
    if (root) {
        inOrder(root->left);
        cout << root->key << " ";
        inOrder(root->right);
    }
}

int main() {
    Node* root = nullptr;

    // Вставка элементов
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    cout << "In-order traversal of the constructed AVL tree is: ";
    inOrder(root);
    cout << endl;

    // Удаление узла
    root = deleteNode(root, 20);
    cout << "In-order traversal after deletion of 20: ";
    inOrder(root);
    cout << endl;

    // Поиск узла
    Node* result = search(root, 30);
    if (result) {
        cout << "Element 30 found in the tree." << endl;
    } else {
        cout << "Element 30 not found in the tree." << endl;
    }

    return 0;
}
