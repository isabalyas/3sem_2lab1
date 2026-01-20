#include <iostream>
#include <string>
#include <fstream>
#include "../new_structures/hashtable/hashtable.h"

using namespace std;

void saveHashTableToFile(HashTable* table[], const string& filename, bool asSet = true) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла!" << endl;
        return;
    }
    
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashTable* temp = table[i];
        while (temp != nullptr) {
            if (asSet) {
                file << temp->key << endl;
            } else {
                file << temp->key << " " << temp->value << endl;
            }
            temp = temp->next;
        }
    }
    file.close();
}

void loadHashTableFromFile(HashTable* table[], const string& filename, bool asSet = true) {
    ifstream file(filename);
    if (!file.is_open()) {
        return;
    }
    
    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            if (asSet) {
                insertTable(table, line, line);
            } else {
                size_t spacePos = line.find(' ');
                if (spacePos != string::npos) {
                    string key = line.substr(0, spacePos);
                    string value = line.substr(spacePos + 1);
                    insertTable(table, key, value);
                }
            }
        }
    }
    file.close();
}

int main(int argc, char* argv[]) {
    cout << "Задание 2: Основные операции со множеством" << endl;
    cout << "==========================================" << endl;
    
    HashTable* table[TABLE_SIZE] = {nullptr};
    
    cout << "Команды:" << endl;
    cout << "  ADD <значение> - добавить элемент" << endl;
    cout << "  REMOVE <значение> - удалить элемент" << endl;
    cout << "  CHECK <значение> - проверить наличие" << endl;
    cout << "  PRINT - показать множество" << endl;
    cout << "  SAVE <файл> - сохранить в файл" << endl;
    cout << "  LOAD <файл> - загрузить из файла" << endl;
    cout << "  EXIT - выход" << endl;
    cout << "==========================================" << endl;
    
    string command;
    while (true) {
        cout << "\n> ";
        getline(cin, command);
        
        if (command == "EXIT") {
            freeTable(table);
            break;
        }
        
        size_t spacePos = command.find(' ');
        string cmd = command.substr(0, spacePos);
        string value = (spacePos != string::npos) ? command.substr(spacePos + 1) : "";
        
        if (cmd == "ADD" && !value.empty()) {
            insertTable(table, value, value);
            cout << "Добавлено: " << value << endl;
        } else if (cmd == "REMOVE" && !value.empty()) {
            removeValueTable(table, value);
            cout << "Удалено: " << value << endl;
        } else if (cmd == "CHECK" && !value.empty()) {
            string result = getValueTable(table, value);
            cout << (result != "Ключ не найден" ? "YES" : "NO") << endl;
        } else if (cmd == "PRINT") {
            printTable(table);
        } else if (cmd == "SAVE" && !value.empty()) {
            saveHashTableToFile(table, value, true);
            cout << "Сохранено в файл: " << value << endl;
        } else if (cmd == "LOAD" && !value.empty()) {
            loadHashTableFromFile(table, value, true);
            cout << "Загружено из файла: " << value << endl;
        } else {
            cout << "Неверная команда!" << endl;
        }
    }
    
    return 0;
}