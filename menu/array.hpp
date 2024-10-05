#ifndef VECTORMENU_H
#define VECTORMENU_H

#include "../data_structures/vector.hpp"
#include "../file/fileread.hpp"
#include "../file/filewrite.hpp"

const string ARRAY_SECTION = "Array";

void vectorMenu(Vector<string> arguments) {
    string command = arguments.get(0);

    if (command == "MPUSH") {
        if (arguments.size() != 3) {
            throw runtime_error("incorrect count of arguments");
        }
        string nameArr = arguments.get(1);
        string element = arguments.get(2);

        if (element.find(",") != string::npos) {
            throw runtime_error(", shouldn't be in pushed element");
        }

        Vector<string> array = readArray(nameArr);
        array.pushBack(element);
        save(ARRAY_SECTION, nameArr, nameArr + " " + join(array, ','));
    } else if (command == "MDEL") {
        if (arguments.size() != 3) {
            throw invalid_argument("incorrect count of arguments");
        }
        string nameArr = arguments.get(1);
        int index;
        try {
            index = stoi(arguments.get(2));
        } catch (invalid_argument& e) {
            throw invalid_argument("argument should be number");
        }

        Vector<string> array = readArray(nameArr);
        try {
            array.remove(index);
        } catch (invalid_argument& e) {
            throw invalid_argument("incorrect index");
        }
        save(ARRAY_SECTION, nameArr, nameArr + " " + join(array, ','));
    } else if (command == "MGET") {
        if (arguments.size() != 3) {
            throw invalid_argument("incorrect count of arguments");
        }
        string nameArr = arguments.get(1);
        int index;
        try {
            index = stoi(arguments.get(2));
        } catch (invalid_argument& e) {
            throw invalid_argument("argument should be number");
        }

        Vector<string> array = readArray(nameArr);
        cout << array.get(index) << endl;
    }
}

#endif