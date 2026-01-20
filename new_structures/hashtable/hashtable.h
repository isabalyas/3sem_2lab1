#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

const int TABLE_SIZE = 10;

struct HashTable {
    string key;
    string value;
    HashTable* next = nullptr;
};
int hashFunction(const string& key);
void insertTable(HashTable* table[], const string& key, const string& value);
string getValueTable(HashTable* table[], const string& key);
void removeValueTable(HashTable* table[], const string& key);
void printTable(HashTable* table[]);
void freeTable(HashTable* table[]);
void writeHashTableToFile(HashTable* table[], const string& filename);
