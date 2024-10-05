#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include "vector.hpp"

using namespace std;


template <typename T>
struct Queue {
private:
    Vector<T> queue;
    int len;

public:
    Queue() {
        len = 0;
    }
    
    Vector<T> getData() const {
        return queue;
    }

    int size() {
        return len;
    }

    void enqueue(T val) {
        queue.pushBack(val);
    }

    T dequeue() {
        if (queue.size() == 0) {
            throw runtime_error("Queue is empty");
        }

        T dequeued = queue.get(0);
        queue.remove(0);

        return dequeued;
    }
};

template <typename T>
ostream& operator<<(ostream& os, const Queue<T>& queue) {
    Vector<T> data = queue.getData();

    for (int i = 0; i < data.size(); i++) {
        os << data.get(i) << " ";
    }

    return os;
}

#endif
