#ifndef SLIST_H
#define SLIST_H

#include <iostream>

using namespace std;

template <typename T>
struct SNode {
    T value;
    SNode<T>* next;

    SNode(const T& val) : value(val), next(nullptr) {}
};

template <typename T>
struct SLinkedList {
private:
    int len;

public:
    SNode<T>* head;

    SLinkedList() {
        head = nullptr;
        len = 0;
    }
    // ~LinkedList() {
    //     while (head!= nullptr) {
    //         SNode<T>* oldHead = head;
    //         head = head->next;
    //         delete oldHead;
    //     }
    // }

    void pushForward(SNode<T>* node) {
        SNode<T>* oldHead = head;
        head = node;
        node->next = oldHead;
        len++;
    }

    void pushBack(T value) {
        SNode<T>* node = new SNode<T>(value);
        if (head == nullptr) {
            head = node;
            return;
        }

        SNode<T>* current = head;
        while (current->next!= nullptr) {
            current = current->next;
        }
        current->next = node;
        len++;
    }

    void removeForward() {
        if (head == nullptr) {
            throw runtime_error("List is empty");
        }

        SNode<T>* oldHead = head;
        head = head->next;
        delete oldHead;
        len--;
    }

    void removeBack() {
        if (head == nullptr) {
            throw runtime_error("List is empty");
        }

        SNode<T>* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        delete current;
        len--;
    }

    void removeValue(const T& value) {
        SNode<T>* prev = nullptr;
        SNode<T>* current = head;

        while(current != nullptr) {
            if(current->value == value) {
                if (prev != nullptr) {
                    prev->next = current->next;
                    delete current;
                    current = prev->next;
                } else {
                    head = current->next;
                    delete current;
                    current = head;
                }
            } else {
                prev = current;
                current = current->next;
            }
        }
    }

    SNode<T>* findByValue(const T& value) {
        SNode<T>* current = head;
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
ostream& operator<<(ostream& os, const SLinkedList<T>& list) {
    auto head = list.head;
    while (head != nullptr) {
        cout << head->value << endl;
        head = head->next;
    }
    return os;
}

#endif