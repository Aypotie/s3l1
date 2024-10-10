#ifndef AVLMENU_H
#define AVLMENU_H

#include "../data_structures/avl.hpp"
#include "../file/fileread.hpp"
#include "../file/filewrite.hpp"

const string AVL_SECTION = "AvlTree";

void avlTreeMenu(Vector<string> arguments) {
    string command = arguments.get(0);

    if (command == "TPUSH") {
        if (arguments.size() != 3) {
            throw runtime_error("incorrect count of arguments");
        }
        string name = arguments.get(1);
        int number;
        try {
            number = stoi(arguments.get(2));
        } catch (invalid_argument& e) {
            throw runtime_error("argument should be number");
        }

        AVLTree tree = readTree(name);
        tree.insertNum(number);
        save(AVL_SECTION, name, name + " " + tree.serialize());
    } else if (command == "TDEL") {
        if (arguments.size() != 3) {
            throw runtime_error("incorrect count of arguments");
        }
        string name = arguments.get(1);
        int number;
        try {
            number = stoi(arguments.get(2));
        } catch (invalid_argument& e) {
            throw runtime_error("argument should be number");
        }

        AVLTree tree = readTree(name);
        tree.removeNum(number);
        save(AVL_SECTION, name, name + " " + tree.serialize());
    } else if (command == "TGET") {
        if (arguments.size() != 2) {
            throw runtime_error("incorrect count of arguments");
        }
        string name = arguments.get(1);

        AVLTree tree = readTree(name);
        cout << tree << endl;
    } else if (command == "TFIND") {
        if (arguments.size() != 3) {
            throw runtime_error("incorrect count of arguments");
        }
        string name = arguments.get(1);
        int elem;
        elem = stoi(arguments.get(2));

        AVLTree tree = readTree(name);

        if(tree.find(elem)){
            cout << "true" << endl;
        } else {
            cout << "false" << endl;
        }
    }
}
#endif