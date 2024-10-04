#ifndef QUEUEMENU_H
#define QUEUEMENU_H

#include "../data_structures/vector.hpp"
#include "../file/fileread.hpp"
#include "../file/filewrite.hpp"

void queueMenu(Vector<string> arguments) {
    string command = arguments.get(0);

    if (command == "QPUSH") {
        if (arguments.size() != 3) {
            throw runtime_error("incorrect count of arguments");
        }
        string nameArr = arguments.get(1);
        string element = arguments.get(2);

        if (element.find(",") != string::npos) {
            throw runtime_error(", shouldn't be in pushed element");
        }

        Queue<string> queue = readQueue(nameArr);
        queue.enqueue(element);
        saveArray("Queue", nameArr, nameArr + " " + join(queue.getData(), ','));
    } else if (command == "QDEL") {
        if (arguments.size() != 2) {
            throw invalid_argument("incorrect count of arguments");
        }
        string nameArr = arguments.get(1);

        Queue<string> queue = readQueue(nameArr);
        queue.dequeue();
        saveArray("Queue", nameArr, nameArr + " " + join(queue.getData(), ','));
    } else if (command == "QGET") {
        if (arguments.size() != 2) {
            throw invalid_argument("incorrect count of arguments");
        }
        string nameArr = arguments.get(1);

        Queue<string> queue = readQueue(nameArr);
        cout << queue << endl;
    }
}

#endif