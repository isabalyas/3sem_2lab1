#include "open_hash.h"
#include <iostream>

int hashFunc(const string& key, int capacity) {
    int hash = 0;
    for (size_t i = 0; i < key.length(); i++) {
        hash = (hash * 31 + key[i]) % capacity;
    }
    return hash;
}

int findKeyIndex(OpenHashTable* ht, const string& key) {
    int index = hashFunc(key, ht->capacity);
    int startIndex = index;
    
    do {
        if (ht->table[index].status == EMPTY_SLOT) {
            return -1;
        }
        if (ht->table[index].status == OCCUPIED_SLOT && 
            ht->table[index].key == key) {
            return index;
        }
        index = (index + 1) % ht->capacity;
    } while (index != startIndex);
    
    return -1;
}

bool hashInsert(OpenHashTable* ht, const string& key, const string& value) {
    if (ht->size >= ht->capacity) {
        return false;
    }
    
    int existingIndex = findKeyIndex(ht, key);
    if (existingIndex != -1) {
        ht->table[existingIndex].value = value;
        return true;
    }
    
    int index = hashFunc(key, ht->capacity);
    int startIndex = index;
    
    do {
        if (ht->table[index].status != OCCUPIED_SLOT) {
            ht->table[index].key = key;
            ht->table[index].value = value;
            ht->table[index].status = OCCUPIED_SLOT;
            ht->size++;
            return true;
        }
        index = (index + 1) % ht->capacity;
    } while (index != startIndex);
    
    return false;
}

string hashGet(OpenHashTable* ht, const string& key) {
    int index = findKeyIndex(ht, key);
    if (index != -1 && ht->table[index].status == OCCUPIED_SLOT) {
        return ht->table[index].value;
    }
    return "";
}

bool hashRemove(OpenHashTable* ht, const string& key) {
    int index = findKeyIndex(ht, key);
    if (index != -1 && ht->table[index].status == OCCUPIED_SLOT) {
        ht->table[index].status = DELETED_SLOT;
        ht->size--;
        return true;
    }
    return false;
}

bool hashContains(OpenHashTable* ht, const string& key) {
    return findKeyIndex(ht, key) != -1;
}

void hashPrint(OpenHashTable* ht) {
    cout << "Хэш-таблица (размер: " << ht->size << "/" << ht->capacity << "):\n";
    for (int i = 0; i < ht->capacity; i++) {
        cout << "[" << i << "]: ";
        if (ht->table[i].status == OCCUPIED_SLOT) {
            cout << ht->table[i].key << " -> " << ht->table[i].value;
        } else if (ht->table[i].status == DELETED_SLOT) {
            cout << "<УДАЛЕНО>";
        } else {
            cout << "<ПУСТО>";
        }
        cout << endl;
    }
}

int hashSize(OpenHashTable* ht) {
    return ht->size;
}

void hashClear(OpenHashTable* ht) {
    for (int i = 0; i < ht->capacity; i++) {
        ht->table[i].status = EMPTY_SLOT;
    }
    ht->size = 0;
}