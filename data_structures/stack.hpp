#ifndef STACK_H
#define STACK_H

#include <iostream>
#include "vector.hpp"

using namespace std;

template <typename T>
struct CustomStack {
private:
    CustomVector<T> stack;

public:
    CustomVector<T> getData() const {
        return stack;
    }

    void push(T val) {
        stack.pushBack(val);
    }

    T pop() {
        if (stack.getLen() == 0) {
            throw runtime_error("Stack is empty");
        }

        int outIndex = stack.getLen() - 1;
        T popped = stack.get(outIndex);
        stack.remove(outIndex);
        
        return popped;
    }
};

template <typename T>
ostream& operator<<(ostream& os, const CustomStack<T>& stack) {
    CustomVector<T> data = stack.getData();

    for (int i = data.getLen() - 1; i >= 0; i--) {
        os << data.get(i) << endl;
    }

    return os;
}

#endif