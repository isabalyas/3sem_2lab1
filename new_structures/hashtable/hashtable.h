#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

const int INITIAL_TABLE_SIZE = 10;
const double LOAD_FACTOR_THRESHOLD = 0.75; // Порог для перехэширования

struct HashTable {
    string key;
    string value;
    HashTable* next = nullptr;
};

class HashTableWithRehash {
private:
    vector<HashTable*> table;
    int capacity; // Текущая вместимость
    int size; // Количество элементов
    
    int hashFunction(const string& key, int tableSize);
    bool needRehash();
    void performRehash();
    
public:
    HashTableWithRehash(int initialCapacity = INITIAL_TABLE_SIZE);
    ~HashTableWithRehash();
    
    void insertTable(const string& key, const string& value);
    string getValueTable(const string& key);
    void removeValueTable(const string& key);
    void printTable();
    void writeHashTableToFile(const string& filename);
    int getSize() const { return size; }
    int getCapacity() const { return capacity; }
    double getLoadFactor() const { return (double)size / capacity; }
};