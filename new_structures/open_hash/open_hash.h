#pragma once
#include <string>

using namespace std;

#define DEFAULT_TABLE_SIZE 20

enum SlotStatus {
    EMPTY_SLOT,
    OCCUPIED_SLOT,
    DELETED_SLOT
};

struct HashSlot {
    string key;
    string value;
    SlotStatus status;
    
    HashSlot() : status(EMPTY_SLOT) {}
};

struct OpenHashTable {
    HashSlot* table;
    int capacity;
    int size;
    
    OpenHashTable(int cap = DEFAULT_TABLE_SIZE) {
        capacity = cap;
        size = 0;
        table = new HashSlot[capacity];
        for (int i = 0; i < capacity; i++) {
            table[i].status = EMPTY_SLOT;
        }
    }
    
    ~OpenHashTable() {
        delete[] table;
    }
};

// Функции хэш-таблицы
int hashFunc(const string& key, int capacity);
bool hashInsert(OpenHashTable* ht, const string& key, const string& value);
string hashGet(OpenHashTable* ht, const string& key);
bool hashRemove(OpenHashTable* ht, const string& key);
bool hashContains(OpenHashTable* ht, const string& key);
void hashPrint(OpenHashTable* ht);
int hashSize(OpenHashTable* ht);
void hashClear(OpenHashTable* ht);
bool rehash(OpenHashTable* ht);