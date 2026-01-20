#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <random>
#include "../new_structures/hashtable/hashtable.h"
#include "../new_structures/open_hash/open_hash.h"

using namespace std;
using namespace std::chrono;

// Генератор случайных строк
string generateRandomString(int length) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    
    string result;
    result.reserve(length);
    
    for (int i = 0; i < length; ++i) {
        result += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    
    return result;
}

// Тест цепочечного хеширования
void testChainingHash(int numOperations, int tableSize) {
    cout << "\n=== ТЕСТ ЦЕПОЧЕЧНОГО ХЕШИРОВАНИЯ ===" << endl;
    cout << "Количество операций: " << numOperations << endl;
    cout << "Размер таблицы: " << tableSize << endl;
    
    // Временно изменяем TABLE_SIZE
    #define OLD_TABLE_SIZE TABLE_SIZE
    #undef TABLE_SIZE
    #define TABLE_SIZE tableSize
    
    HashTable* table[TABLE_SIZE] = {nullptr};
    
    vector<string> keys;
    vector<string> values;
    
    // Генерация данных
    srand(time(nullptr));
    for (int i = 0; i < numOperations; i++) {
        keys.push_back("key_" + to_string(i) + "_" + generateRandomString(5));
        values.push_back("value_" + to_string(i) + "_" + generateRandomString(10));
    }
    
    // Тест вставки
    auto start = high_resolution_clock::now();
    
    for (int i = 0; i < numOperations; i++) {
        insertTable(table, keys[i], values[i]);
    }
    
    auto stop = high_resolution_clock::now();
    auto duration_insert = duration_cast<milliseconds>(stop - start);
    
    // Тест поиска
    start = high_resolution_clock::now();
    
    for (int i = 0; i < numOperations; i++) {
        getValueTable(table, keys[i]);
    }
    
    stop = high_resolution_clock::now();
    auto duration_search = duration_cast<milliseconds>(stop - start);
    
    // Тест удаления
    start = high_resolution_clock::now();
    
    for (int i = 0; i < numOperations; i++) {
        removeValueTable(table, keys[i]);
    }
    
    stop = high_resolution_clock::now();
    auto duration_delete = duration_cast<milliseconds>(stop - start);
    
    cout << "Результаты:" << endl;
    cout << "  Вставка: " << duration_insert.count() << " мс" << endl;
    cout << "  Поиск: " << duration_search.count() << " мс" << endl;
    cout << "  Удаление: " << duration_delete.count() << " мс" << endl;
    
    freeTable(table);
    
    // Восстанавливаем TABLE_SIZE
    #undef TABLE_SIZE
    #define TABLE_SIZE OLD_TABLE_SIZE
}

// Тест линейного пробирования
void testOpenHash(int numOperations, int tableSize) {
    cout << "\n=== ТЕСТ ЛИНЕЙНОГО ПРОБИРОВАНИЯ ===" << endl;
    cout << "Количество операций: " << numOperations << endl;
    cout << "Размер таблицы: " << tableSize << endl;
    
    OpenHashTable* table = new OpenHashTable(tableSize);
    
    vector<string> keys;
    vector<string> values;
    
    // Генерация данных
    srand(time(nullptr) + 1); // Разное seed для разнообразия
    for (int i = 0; i < numOperations; i++) {
        keys.push_back("key_" + to_string(i) + "_" + generateRandomString(5));
        values.push_back("value_" + to_string(i) + "_" + generateRandomString(10));
    }
    
    // Тест вставки
    auto start = high_resolution_clock::now();
    
    for (int i = 0; i < numOperations; i++) {
        hashInsert(table, keys[i], values[i]);
    }
    
    auto stop = high_resolution_clock::now();
    auto duration_insert = duration_cast<milliseconds>(stop - start);
    
    // Тест поиска
    start = high_resolution_clock::now();
    
    for (int i = 0; i < numOperations; i++) {
        hashGet(table, keys[i]);
    }
    
    stop = high_resolution_clock::now();
    auto duration_search = duration_cast<milliseconds>(stop - start);
    
    // Тест удаления
    start = high_resolution_clock::now();
    
    for (int i = 0; i < numOperations; i++) {
        hashRemove(table, keys[i]);
    }
    
    stop = high_resolution_clock::now();
    auto duration_delete = duration_cast<milliseconds>(stop - start);
    
    cout << "Результаты:" << endl;
    cout << "  Вставка: " << duration_insert.count() << " мс" << endl;
    cout << "  Поиск: " << duration_search.count() << " мс" << endl;
    cout << "  Удаление: " << duration_delete.count() << " мс" << endl;
    
    delete table;
}

// Демонстрация работы обоих методов
void demoBothMethods() {
    cout << "\n=== ДЕМОНСТРАЦИЯ РАБОТЫ ОБОИХ МЕТОДОВ ===" << endl;
    
    // Маленький пример для наглядности
    cout << "\n1. ЦЕПОЧЕЧНОЕ ХЕШИРОВАНИЕ:" << endl;
    
    HashTable* chainTable[10] = {nullptr};
    
    cout << "   Вставляем: apple -> red, banana -> yellow, orange -> orange" << endl;
    insertTable(chainTable, "apple", "red");
    insertTable(chainTable, "banana", "yellow");
    insertTable(chainTable, "orange", "orange");
    
    cout << "   Ищем banana: " << getValueTable(chainTable, "banana") << endl;
    cout << "   Удаляем apple" << endl;
    removeValueTable(chainTable, "apple");
    cout << "   Ищем apple: " << getValueTable(chainTable, "apple") << endl;
    
    freeTable(chainTable);
    
    cout << "\n2. ЛИНЕЙНОЕ ПРОБИРОВАНИЕ:" << endl;
    
    OpenHashTable* openTable = new OpenHashTable(10);
    
    cout << "   Вставляем: car -> fast, bus -> big, bike -> small" << endl;
    hashInsert(openTable, "car", "fast");
    hashInsert(openTable, "bus", "big");
    hashInsert(openTable, "bike", "small");
    
    cout << "   Ищем bus: " << hashGet(openTable, "bus") << endl;
    cout << "   Удаляем car" << endl;
    hashRemove(openTable, "car");
    cout << "   Ищем car: " << hashGet(openTable, "car") << endl;
    
    delete openTable;
}

int main() {
    setlocale(LC_ALL, "rus");
    
    cout << "ЗАДАНИЕ 7: СРАВНЕНИЕ МЕТОДОВ ХЕШИРОВАНИЯ" << endl;
    cout << "========================================" << endl;
    
    int choice;
    
    do {
        cout << "\nМЕНЮ:" << endl;
        cout << "1. Тестирование производительности" << endl;
        cout << "2. Демонстрация работы методов" << endl;
        cout << "3. Сравнение с разными размерами таблиц" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите действие: ";
        cin >> choice;
        
        switch (choice) {
            case 1: {
                int numOps, tableSize;
                cout << "\nВведите количество операций: ";
                cin >> numOps;
                cout << "Введите размер таблицы: ";
                cin >> tableSize;
                
                testChainingHash(numOps, tableSize);
                testOpenHash(numOps, tableSize);
                break;
            }
            
            case 2:
                demoBothMethods();
                break;
                
            case 3: {
                cout << "\n=== СРАВНЕНИЕ С РАЗНЫМИ РАЗМЕРАМИ ТАБЛИЦ ===" << endl;
                cout << "Тест с 1000 операций:" << endl;
                
                cout << "\n--- Маленькая таблица (размер 100) ---" << endl;
                testChainingHash(1000, 100);
                testOpenHash(1000, 100);
                
                cout << "\n--- Большая таблица (размер 10000) ---" << endl;
                testChainingHash(1000, 10000);
                testOpenHash(1000, 10000);
                break;
            }
                
            case 0:
                cout << "Выход..." << endl;
                break;
                
            default:
                cout << "Неверный выбор!" << endl;
        }
        
    } while (choice != 0);
    
    return 0;
}
