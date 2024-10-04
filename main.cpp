#include <iostream>
#include "data_structures/vector.hpp"
#include "data_structures/string.hpp"
#include "menu/vector.hpp"
#include "menu/queue.hpp"

using namespace std;

int main() {
    string str;

    while (true) {
        cout << ">> ";
        getline(cin, str);

        Vector<string> splittedStr = split(str, ' ');
        string command = splittedStr.get(0);

        if (command[0] == 'M') {
            try {
                vectorMenu(splittedStr);
            } catch (invalid_argument& e) {
                cerr << e.what() << endl;
            }
        } else if (command[0] == 'Q') {
            try {
                queueMenu(splittedStr);
            } catch (invalid_argument& e) {
                cerr << e.what() << endl;
            }
        } else {
            cerr << "Unknown command" << endl;
        }
    }

    return 0;
}
