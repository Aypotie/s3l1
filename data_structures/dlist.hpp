#ifndef DLIST_H
#define DLIST_H

#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
struct DNode {
    T value;
    DNode<T>* next;
    DNode<T>* prev;

    DNode(const T& val) : value(val), next(nullptr), prev(nullptr) {}
};

template <typename T>
struct Dlist {
private:
    int len;

public:
    DNode<T>* head;
    DNode<T>* tail;

    Dlist() {
        head = nullptr;
        tail = nullptr;
        len = 0;
    }

    int size() const {
        return len;
    }

    T get(int index) const {
        if (index < 0 || index >= len) {
            throw runtime_error("Index out of bounds");
        }

        DNode<T>* current = head;
        int c = 0;
        while (c != index && current != nullptr) {
            current = current->next;
            c++;
        }
        return current->value;
    }

    void pushForward(T value) {
        DNode<T>* node = new DNode<T>(value);
        if (head == nullptr) {
            head = node;
            tail = node; // Хвост и голова совпадают
        } else {
            DNode<T>* oldHead = head;
            head = node;
            node->next = oldHead;
            oldHead->prev = node;
        }
        len++;
    }

    void pushBack(T value) {
        DNode<T>* node = new DNode<T>(value);
        if (head == nullptr) {
            head = node;
            tail = node;
        } else {
            tail->next = node; // Присоединяем к хвосту
            node->prev = tail;
            tail = node; // Обновляем хвост
        }
        len++;
    }

    void removeForward() {
        if (head == nullptr) {
            throw runtime_error("List is empty");
        }

        DNode<T>* oldHead = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr; // Если голова удалена, хвост тоже
        }
        delete oldHead;
        len--;
    }

    void removeBack() {
        if (head == nullptr) {
            throw runtime_error("List is empty");
        }

        if (head->next == nullptr) { // Единственный элемент
            delete head;
            head = nullptr;
            tail = nullptr;
        } else {
            DNode<T>* current = tail; 
            current->prev->next = nullptr; 
            tail = current->prev; // Обновляем хвост
            delete current;
        }
        len--;
    }

        void removeValue(const T& value) {
        DNode<T>* current = head;

        while (current != nullptr) {
            if (current->value == value) {
                DNode<T>* toDelete = current;
                if (current->prev != nullptr) { // Узел не первый
                    current->prev->next = current->next;
                } else { // Первый узел
                    head = current->next;
                }

                if (current->next != nullptr) { // Узел не последний
                    current->next->prev = current->prev;
                } else { // Последний узел
                    tail = current->prev; 
                }

                current = current->next;
                delete toDelete;
                len--;
            } else {
                current = current->next;
            }
        }
    }

    int findByValue(const T& value) {
        DNode<T>* current = head;
        int c = 0;
        while (current != nullptr) {
            if (current->value == value) {
                return c;
            }
            current = current->next;
            c++;
        }
        return -1;
    }

    string join(char delimiter) {
        string result;
        DNode<string>* current = head;

        while (current != nullptr) {
            result += current->value;
            if (current->next != nullptr) {
                result += delimiter;
            }
            current = current->next;
        }

        return result;
    }
};


template <typename T>
ostream& operator<<(ostream& os, const Dlist<T>& list) {
    auto head = list.head;
    while (head != nullptr) {
        os << head->value << " ";
        head = head->next;
    }
    return os;
}

#endif
