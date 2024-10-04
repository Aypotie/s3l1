#ifndef FILEREAD_H
#define FILEREAD_H
#include <iostream>
#include <fstream>
#include <regex>

#include "../data_structures/vector.hpp"
#include "../data_structures/queue.hpp"
#include "../data_structures/string.hpp"

using namespace std;

const string FILENAME = "file.data";

Vector<string> readArray(string name) {
    ifstream file(FILENAME);

    if (!file.is_open()) {
        throw runtime_error("Error opening file");
    }

    string line;
    
    bool isArray = false;
    while (getline(file, line)) {
        if (line == "Array") {
            isArray = true;
        } else if (isArray) {
            Vector<string> splittedLine = split(line, ' ');

            if (splittedLine.size() != 2) {
                continue;
            }

            if (splittedLine.get(0) == name) {
                Vector<string> array = split(splittedLine.get(1), ','); // делим по запятым второй аргумент
                if (array.size() == 1 && array.get(0) == "") { // при пустой строке создаётся массив с пустой строкой, надо удалить эту строку, чтоб сделать пустой массив
                    array.remove(0);
                }
                return array;
            }
        } else if (line == "" && isArray) {
            break;
        }
    }

    file.close();

    Vector<string> array;
    return array;
}

Queue<string> readQueue(string name) {
    Queue<string> queue;

    ifstream file(FILENAME);

    if (!file.is_open()) {
        throw runtime_error("Error opening file");
    }

    string line;
    
    bool isArray = false;
    while (getline(file, line)) {
        if (line == "Queue") {
            isArray = true;
        } else if (isArray) {
            Vector<string> splittedLine = split(line, ' ');

            if (splittedLine.size() != 2) {
                continue;
            }

            if (splittedLine.get(0) == name) {
                Vector<string> array = split(splittedLine.get(1), ','); // делим по запятым второй аргумент
                if (array.size() == 1 && array.get(0) == "") { // при пустой строке создаётся массив с пустой строкой, надо удалить эту строку, чтоб сделать пустой массив
                    array.remove(0);
                }
                for (int i = 0; i < array.size(); i++) {
                    queue.enqueue(array.get(i));
                }
                return queue;
            }
        } else if (line == "" && isArray) {
            break;
        }
    }

    file.close();

    return queue;
}

#endif