#ifndef FILEWRITE_H
#define FILEWRITE_H

void saveArray(string section, string nameArr, string writeline) {
    ifstream file(FILENAME);  // Открываем файл для чтения

    // Проверяем, что файл успешно открыт
    if (!file.is_open()) {
        throw runtime_error("error opening file");
    }

    Vector<string> fileLines;  // Вектор для хранения строк файла
    string line;
    bool isArraySection = false;
    bool foundArray = false;

    // Читаем файл построчно
    while (getline(file, line)) {
        if (line == section) {
            isArraySection = true;
        } else if (isArraySection && line == "") {
            isArraySection = false;
            if (!foundArray) {
                fileLines.push_back(writeline);
            }
        }

        if (isArraySection) {
            Vector<string> splittedLine = split(line, ' ');

            if (splittedLine.size() == 2 && splittedLine.get(0) == nameArr) {
                // Нашли нужный массив, заменяем его на новый
                line = writeline;
                foundArray = true;
            }
        }

        fileLines.push_back(line);  // Сохраняем строку
    }

    file.close();  // Закрываем файл после чтения

    // Открываем файл для записи (перезаписываем содержимое файла)
    ofstream outFile(FILENAME);
    if (!outFile.is_open()) {
        throw runtime_error("Error opening file for writing");
    }

    // Записываем все строки обратно в файл
    for (int i = 0; i < fileLines.size(); i++) {
        outFile << fileLines.get(i) << endl;
    }

    outFile.close();  // Закрываем файл после записи
}

#endif