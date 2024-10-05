#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

struct AVLTreeNode {
    int value;
    int height;
    AVLTreeNode* left;
    AVLTreeNode* right;

    AVLTreeNode(const int val) : value(val), height(1), left(nullptr), right(nullptr) {}
};

struct AVLTree {
    AVLTreeNode* head;
    AVLTree() : head(nullptr) {}

    // Функция для получения высоты узла
    int height(AVLTreeNode* node) {
        return node == nullptr ? 0 : node->height;
    }

    // Функция для обновления высоты узла
    void updateHeight(AVLTreeNode* node) {
        if (node != nullptr) {
            node->height = max(height(node->left), height(node->right)) + 1;
        }
    }

    // Функция для получения баланса узла
    int getBalance(AVLTreeNode* node) {
        return node == nullptr ? 0 : height(node->left) - height(node->right);
    }

    // Правое вращение
    AVLTreeNode* rotateRight(AVLTreeNode* y) {
        AVLTreeNode* x = y->left;
        AVLTreeNode* T2 = x->right;

        // Выполняем вращение
        x->right = y;
        y->left = T2;

        // Обновляем высоты
        updateHeight(y);
        updateHeight(x);

        return x;
    }

    // Левое вращение
    AVLTreeNode* rotateLeft(AVLTreeNode* x) {
        AVLTreeNode* y = x->right;
        AVLTreeNode* T2 = y->left;

        // Выполняем вращение
        y->left = x;
        x->right = T2;

        // Обновляем высоты
        updateHeight(x);
        updateHeight(y);

        return y;
    }

    // Балансировка узла
    AVLTreeNode* balanceNode(AVLTreeNode* node) {
        updateHeight(node);
        int balance = getBalance(node);

        // Левое вращение, если баланс > 1 и вставка произошла в левое поддерево
        if (balance > 1 && getBalance(node->left) >= 0) {
            return rotateRight(node);
        }

        // Правое вращение, если баланс < -1 и вставка произошла в правое поддерево
        if (balance < -1 && getBalance(node->right) <= 0) {
            return rotateLeft(node);
        }

        // Левое-правое вращение, если баланс > 1 и вставка произошла в правое поддерево левого поддерева
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Правое-левое вращение, если баланс < -1 и вставка произошла в левое поддерево правого поддерева
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // Вставка узла с балансировкой
    AVLTreeNode* insert(AVLTreeNode* node, int value) {
        if (node == nullptr) {
            return new AVLTreeNode(value);
        }

        if (value < node->value) {
            node->left = insert(node->left, value);
        } else if (value > node->value) {
            node->right = insert(node->right, value);
        } else {
            // Дубликаты не допускаются
            return node;
        }

        // Балансировка узла после вставки
        return balanceNode(node);
    }

    // Метод вставки нового значения
    void insertNum(int value) {
        head = insert(head, value);
    }

    // Удаление узла
    AVLTreeNode* remove(AVLTreeNode* node, int value) {
        if (node == nullptr) {
            return node;
        }

        // Находим узел для удаления
        if (value < node->value) {
            node->left = remove(node->left, value);
        } else if (value > node->value) {
            node->right = remove(node->right, value);
        } else {
            // Узел найден
            if (node->left == nullptr || node->right == nullptr) {
                AVLTreeNode* temp = node->left ? node->left : node->right;
                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
            } else {
                AVLTreeNode* temp = getMinValueNode(node->right);
                node->value = temp->value;
                node->right = remove(node->right, temp->value);
            }
        }

        if (node == nullptr) {
            return node;
        }

        // Балансировка узла после удаления
        return balanceNode(node);
    }

    // Получение минимального значения узла
    AVLTreeNode* getMinValueNode(AVLTreeNode* node) {
        AVLTreeNode* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    // Метод удаления узла по значению
    void removeNum(int value) {
        head = remove(head, value);
    }

    // Поиск узла по значению
    AVLTreeNode* search(AVLTreeNode* node, int value) {
        if (node == nullptr || node->value == value) {
            return node;
        }

        if (value < node->value) {
            return search(node->left, value);
        } else {
            return search(node->right, value);
        }
    }

    // Метод поиска узла по значению
    AVLTreeNode* find(int value) {
        return search(head, value);
    }

    void serializeNode(AVLTreeNode* node, string& result) {
        if (node == nullptr) {
            result += "#-";  // символ для обозначения null
            return;
        }
        result += to_string(node->value) + "-";  // записываем значение узла
        serializeNode(node->left, result);           // левое поддерево
        serializeNode(node->right, result);          // правое поддерево
    }

    string serialize() {
        string result;
        serializeNode(head, result);
        return result;
    }

    void unserialize(const string& data) {
        istringstream ss(data);  // используем строковый поток для работы с данными
        head = unserializeSS(ss);  // восстанавливаем дерево из потока
    }

    // Рекурсивная функция для восстановления дерева
    AVLTreeNode* unserializeSS(istringstream& ss) {
        string val;
        getline(ss, val, '-');

        if (val == "#") {
            return nullptr;  // если встречаем символ пустого узла, возвращаем nullptr
        }

        AVLTreeNode* node = new AVLTreeNode(stoi(val));  // создаём новый узел
        node->left = unserializeSS(ss);              // восстанавливаем левое поддерево
        node->right = unserializeSS(ss);             // восстанавливаем правое поддерево

        return node;
    }
};

// Функция для печати дерева
void printAVLTree(string& result, AVLTreeNode* tree, int depth = 0, string prefix = "") {
    if (tree == nullptr) {
        return;
    }

    // Выводим правое поддерево (расположено выше в консоли)
    if (tree->right != nullptr) {
        printAVLTree(result, tree->right, depth + 1, prefix + "\t");
    }

    // Выводим текущий узел с отступом
    result += prefix;
    if (depth > 0) {
        result += "└──";
    }
    result += "[" + to_string(tree->value) + "]\n";

    // Выводим левое поддерево (расположено ниже в консоли)
    if (tree->left != nullptr) {
        printAVLTree(result, tree->left, depth + 1, prefix + "\t");
    }
}

ostream& operator<<(ostream& os, const AVLTree& tree) {
    string stringTree = "";
    printAVLTree(stringTree, tree.head);
    os << stringTree;
    return os;
}

#endif
