#ifndef DLIST_MENU
#define DLIST_MENU
#include "../data_structures/dlist.hpp"
#include "../file/fileread.hpp"
#include "../file/filewrite.hpp"

const string DLIST_SECTION = "Dlist";

void dlistMenu(Vector<string> arguments) {
    string command = arguments.get(0);

    if (command == "DLPUSH") {
        if (arguments.size() != 3) {
            throw runtime_error("incorrect count of arguments");
        }
        string nameArr = arguments.get(1);
        string element = arguments.get(2);

        if (element.find(",") != string::npos) {
            throw runtime_error(", shouldn't be in pushed element");
        }

        Dlist<string> dlist = readDlist(nameArr);
        dlist.pushBack(element);
        save(DLIST_SECTION, nameArr, nameArr + " " + dlist.join(','));
    } else if (command == "DLDEL") {
        if (arguments.size() != 2) {
            throw runtime_error("incorrect count of arguments");
        }
        string nameArr = arguments.get(1);

        Dlist<string> dlist = readDlist(nameArr);
        dlist.removeBack();
        save(DLIST_SECTION, nameArr, nameArr + " " + dlist.join(','));
    } else if (command == "DLGET") {
        if (arguments.size() != 3) {
            throw runtime_error("incorrect count of arguments");
        }
        string nameArr = arguments.get(1);
        int index;
        try {
            index = stoi(arguments.get(2));
        } catch (invalid_argument& e) {
            throw runtime_error("argument should be number");
        }

        Dlist<string> dlist = readDlist(nameArr);
        cout << dlist.get(index) << endl;
    } else if (command == "DLPRINT") {
        if (arguments.size() != 2) {
            throw runtime_error("incorrect count of arguments");
        }
        string nameArr = arguments.get(1);

        Dlist<string> dlist = readDlist(nameArr);
        cout << dlist << endl;
    }
}

#endif