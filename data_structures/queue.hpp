#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include "dlist.hpp"

using namespace std;


template <typename T>
struct Queue {
private:
    Dlist<T> list;

public:
    Queue() {}
    
    Dlist<T> data() const {
        return list;
    }

    int size() const {
        return list.size();
    }

    void enqueue(const T& val) {
        list.pushBack(val);
    }

    T dequeue() {
        if (size() == 0) {
            throw runtime_error("Queue is empty");
        }

        T dequeued = list.head->value;
        list.removeForward();

        return dequeued;
    }
};

template <typename T>
ostream& operator<<(ostream& os, const Queue<T>& queue) {
    os << queue.data() << endl;
    return os;
}

#endif
