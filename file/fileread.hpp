#ifndef FILEREAD_H
#define FILEREAD_H
#include <iostream>
#include <fstream>
#include <regex>

#include "../data_structures/vector.hpp"
#include "../data_structures/queue.hpp"
#include "../data_structures/stack.hpp"
#include "../data_structures/string.hpp"
#include "../data_structures/dlist.hpp"
#include "../data_structures/map.hpp"
#include "../data_structures/avl.hpp"

using namespace std;

const string FILENAME = "file.data";

Vector<string> readArray(string name) {
    Vector<string> array;

    ifstream file(FILENAME);

    if (!file.is_open()) {
        throw runtime_error("Error opening file");
    }

    string line;
    
    bool isArray = false;
    while (getline(file, line)) {
        if (line == "Array") {
            isArray = true;
        }  else if (line == "" && isArray) {
            break;
        } else if (isArray) {
            Vector<string> splittedLine = split(line, ' ');

            if (splittedLine.size() != 2) {
                continue;
            }

            if (splittedLine.get(0) == name) {
                array = split(splittedLine.get(1), ','); // делим по запятым второй аргумент
                if (array.size() == 1 && array.get(0) == "") { // при пустой строке создаётся массив с пустой строкой, надо удалить эту строку, чтоб сделать пустой массив
                    array.remove(0);
                }
                return array;
            }
        }
    }

    file.close();

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
        }  else if (line == "" && isArray) {
            break;
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
        }
    }

    file.close();

    return queue;
}

Stack<string> readStack(string name) {
    Stack<string> stack;

    ifstream file(FILENAME);

    if (!file.is_open()) {
        throw runtime_error("Error opening file");
    }

    string line;
    
    bool isArray = false;
    while (getline(file, line)) {
        if (line == "Stack") {
            isArray = true;
        }  else if (line == "" && isArray) {
            break;
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
                    stack.push(array.get(i));
                }
                return stack;
            }
        }
    }

    file.close();

    return stack;
}

Dlist<string> readDlist(string name) {
    Dlist<string> dlist;

    ifstream file(FILENAME);

    if (!file.is_open()) {
        throw runtime_error("Error opening file");
    }

    string line;
    
    bool isArray = false;
    while (getline(file, line)) {
        if (line == "Dlist") {
            isArray = true;
        } else if (line == "" && isArray) {
            break;
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
                    dlist.pushBack(array.get(i));
                }
                return dlist;
            }
        }
    }

    file.close();

    return dlist;
}

Map<string> readMap(string name) {
    Map<string> map;

    ifstream file(FILENAME);

    if (!file.is_open()) {
        throw runtime_error("Error opening file");
    }

    string line;
    
    bool isArray = false;
    while (getline(file, line)) {
        if (line == "Map") {
            isArray = true;
        } else if (line == "" && isArray) {
            break;
        } else if (isArray) {
            Vector<string> splittedLine = split(line, ' ');

            if (splittedLine.size() != 2) {
                continue;
            }

            if (splittedLine.get(0) == name) {
                Vector<string> array = split(splittedLine.get(1), ';'); // делим по точке-запятой второй аргумент
                if (array.size() == 1 && array.get(0) == "") { // при пустой строке создаётся массив с пустой строкой, надо удалить эту строку, чтоб сделать пустой массив
                    array.remove(0);
                } else {
                    for (int i = 0; i < array.size(); i++) {
                        Vector<string> keyval = split(array.get(i), ',');
                        if (keyval.size() != 2) {
                            throw runtime_error("invalid map format");
                        }
                        string key = keyval.get(0);
                        string value = keyval.get(1);
                        map.put(key, value);
                    }
                }
                
                return map;
            }
        }
    }

    file.close();

    return map;
}

AVLTree readTree(string name) {
    AVLTree tree;

    ifstream file(FILENAME);

    if (!file.is_open()) {
        throw runtime_error("Error opening file");
    }

    string line;
    
    bool isArray = false;
    while (getline(file, line)) {
        if (line == "AvlTree") {
            isArray = true;
        }  else if (line == "" && isArray) {
            break;
        } else if (isArray) {
            Vector<string> splittedLine = split(line, ' ');

            if (splittedLine.size() != 2) {
                continue;
            }

            if (splittedLine.get(0) == name) {
                tree.unserialize(splittedLine.get(1));
                return tree;
            }
        }
    }

    file.close();

    return tree;
}

#endif