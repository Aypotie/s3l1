#ifndef DLIST_H
#define DLIST_H

#include <iostream>

using namespace std;

template <typename T>
struct DNode {
    T value;
    DNode<T>* next;
    DNode<T>* prev;

    DNode(const T& val) : value(val), next(nullptr), prev(nullptr) {}
};

template <typename T>
struct DLinkedList {
private:
    int len;

public:
    DNode<T>* head;

    DLinkedList() {
        head = nullptr;
        len = 0;
    }
    // ~DLinkedList() {
    //     while (head!= nullptr) {
    //         DNode<T>* oldHead = head;
    //         head = head->next;
    //         delete oldHead;
    //     }
    // }

    void pushForward(DNode<T>* node) {
        DNode<T>* oldHead = head;
        head = node;
        node->next = oldHead;
        len++;
    }

    void pushBack(T value) {
        DNode<T>* node = new DNode<T>(value);
        if (head == nullptr) {
            head = node;
            return;
        }

        DNode<T>* current = head;
        while (current->next!= nullptr) {
            current = current->next;
        }
        current->next = node;
        node->prev = current;
        len++;
    }

    void removeForward() {
        if (head == nullptr) {
            throw runtime_error("List is empty");
        }

        DNode<T>* oldHead = head;
        head = head->next;
        delete oldHead;
        len--;
    }

    void removeBack() {
        if (head == nullptr) {
            throw runtime_error("List is empty");
        }

        DNode<T>* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        delete current;
        len--;
    }

    void removeValue(const T& value) {
        DNode<T>* current = head;

        while (current != nullptr) {
            if (current->value == value) {
                DNode<T>* toDelete = current;
                if (current->prev != nullptr) { // node not first
                    current->prev->next = current->next;
                } else { // first node
                    head = current->next;
                }

                if (current->next != nullptr) { // node not last
                    current->next->prev = current->prev;
                }

                current = current->next;
                delete toDelete;
                len--;
            } else {
                current = current->next;
            }
        }
    }

    DNode<T>* findByValue(const T& value) {
        DNode<T>* current = head;
        while (current != nullptr) {
            if (current->value == value) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }
};

template <typename T>
ostream& operator<<(ostream& os, const DLinkedList<T>& list) {
    auto head = list.head;
    while (head != nullptr) {
        cout << head->value << endl;
        head = head->next;
    }
    return os;
}

#endif