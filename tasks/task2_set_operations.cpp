#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "new_structures/hashtable/hashtable.h"

using namespace std;

void saveHashTableToFile(HashTableWithRehash& ht, const string& filename, bool verbose) {
    if (verbose) {
        cout << "Сохранение хэш-таблицы в файл: " << filename << endl;
    }
    
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла для записи: " << filename << endl;
        return;
    }
    
    // В данном случае просто сохраним информацию о таблице
    // Для полного сохранения нужен метод сериализации в классе
    file << "HashTable with rehashing" << endl;
    file << "Size: " << ht.getSize() << endl;
    file << "Capacity: " << ht.getCapacity() << endl;
    file << "Load factor: " << ht.getLoadFactor() * 100 << "%" << endl;
    
    file.close();
    if (verbose) {
        cout << "Хэш-таблица сохранена в файл: " << filename << endl;
    }
}

void loadHashTableFromFile(HashTableWithRehash& ht, const string& filename, bool verbose) {
    if (verbose) {
        cout << "Загрузка хэш-таблицы из файла: " << filename << endl;
    }
    
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла для чтения: " << filename << endl;
        return;
    }
    
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        // Простая логика загрузки - каждая строка это ключ=значение
        size_t pos = line.find('=');
        if (pos != string::npos) {
            string key = line.substr(0, pos);
            string value = line.substr(pos + 1);
            ht.insertTable(key, value);
        } else {
            // Если нет '=', используем всю строку как ключ и значение
            ht.insertTable(line, line);
        }
    }
    
    file.close();
    if (verbose) {
        cout << "Хэш-таблица загружена из файла: " << filename << endl;
    }
}

int main(int argc, char* argv[]) {
    HashTableWithRehash ht;
    
    cout << "=== Операции с множествами на основе хэш-таблицы ===" << endl;
    cout << "Команды:" << endl;
    cout << "  ADD <значение> - добавить элемент" << endl;
    cout << "  REMOVE <значение> - удалить элемент" << endl;
    cout << "  CONTAINS <значение> - проверить наличие" << endl;
    cout << "  PRINT - вывести все элементы" << endl;
    cout << "  SAVE <имя_файла> - сохранить в файл" << endl;
    cout << "  LOAD <имя_файла> - загрузить из файла" << endl;
    cout << "  INFO - информация о таблице" << endl;
    cout << "  EXIT - выход" << endl;
    
    string command;
    while (true) {
        cout << "\nВведите команду: ";
        getline(cin, command);
        
        if (command.empty()) continue;
        
        stringstream ss(command);
        string cmd;
        ss >> cmd;
        
        if (cmd == "EXIT" || cmd == "exit") {
            break;
        } else if (cmd == "ADD" || cmd == "add") {
            string value;
            ss >> value;
            if (!value.empty()) {
                ht.insertTable(value, value);
                cout << "Элемент '" << value << "' добавлен" << endl;
            }
        } else if (cmd == "REMOVE" || cmd == "remove") {
            string value;
            ss >> value;
            if (!value.empty()) {
                ht.removeValueTable(value);
                cout << "Элемент '" << value << "' удален (если существовал)" << endl;
            }
        } else if (cmd == "CONTAINS" || cmd == "contains") {
            string value;
            ss >> value;
            if (!value.empty()) {
                string result = ht.getValueTable(value);
                if (result != "Ключ не найден") {
                    cout << "Элемент '" << value << "' найден" << endl;
                } else {
                    cout << "Элемент '" << value << "' не найден" << endl;
                }
            }
        } else if (cmd == "PRINT" || cmd == "print") {
            ht.printTable();
        } else if (cmd == "SAVE" || cmd == "save") {
            string filename;
            ss >> filename;
            if (!filename.empty()) {
                saveHashTableToFile(ht, filename, true);
            }
        } else if (cmd == "LOAD" || cmd == "load") {
            string filename;
            ss >> filename;
            if (!filename.empty()) {
                // Очищаем текущую таблицу перед загрузкой
                // Нужно создать новую или добавить метод clear()
                HashTableWithRehash newHt;
                ht = newHt; // Присваиваем новую пустую таблицу
                loadHashTableFromFile(ht, filename, true);
            }
        } else if (cmd == "INFO" || cmd == "info") {
            cout << "Информация о хэш-таблице:" << endl;
            cout << "  Размер: " << ht.getSize() << endl;
            cout << "  Емкость: " << ht.getCapacity() << endl;
            cout << "  Коэффициент заполнения: " << ht.getLoadFactor() * 100 << "%" << endl;
            cout << "  Порог перехэширования: 75%" << endl;
        } else {
            cout << "Неизвестная команда. Попробуйте снова." << endl;
        }
    }
    
    return 0;
}