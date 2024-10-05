#ifndef STACKMENU_H
#define STACKMENU_H

#include "../data_structures/stack.hpp"
#include "../file/fileread.hpp"
#include "../file/filewrite.hpp"

const string STACK_SECTION = "Stack";

void stackMenu(Vector<string> arguments) {
    string command = arguments.get(0);

    if (command == "SPUSH") {
        if (arguments.size() != 3) {
            throw runtime_error("incorrect count of arguments");
        }
        string nameArr = arguments.get(1);
        string element = arguments.get(2);

        if (element.find(",") != string::npos) {
            throw runtime_error(", shouldn't be in pushed element");
        }

        Stack<string> stack = readStack(nameArr);
        stack.push(element);
        save(STACK_SECTION, nameArr, nameArr + " " + join(stack.getData(), ','));
    } else if (command == "SPOP") {
        if (arguments.size() != 2) {
            throw runtime_error("incorrect count of arguments");
        }
        string nameArr = arguments.get(1);

        Stack<string> stack = readStack(nameArr);
        cout << "Popped: " << stack.pop() << endl;
        save(STACK_SECTION, nameArr, nameArr + " " + join(stack.getData(), ','));
    } else if (command == "SPRINT") {
        if (arguments.size() != 2) {
            throw runtime_error("incorrect count of arguments");
        }
        string nameArr = arguments.get(1);

        Stack<string> stack = readStack(nameArr);
        cout << stack << endl;
    }
}

#endif