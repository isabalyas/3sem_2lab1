#include <iostream>
#include <string>
#include <sstream>
#include "../new_structures/open_hash/open_hash.h"

using namespace std;

struct LRUNode {
    string key;
    string value;
    LRUNode* prev;
    LRUNode* next;
    
    LRUNode(const string& k, const string& v) : 
        key(k), value(v), prev(nullptr), next(nullptr) {}
};

struct LRUCache {
    OpenHashTable* hashTable;
    LRUNode* head;
    LRUNode* tail;
    int capacity;
    int size;
    
    LRUCache(int cap) {
        capacity = cap;
        size = 0;
        head = nullptr;
        tail = nullptr;
        hashTable = new OpenHashTable(cap * 2);
    }
    
    ~LRUCache() {
        LRUNode* current = head;
        while (current) {
            LRUNode* next = current->next;
            delete current;
            current = next;
        }
        delete hashTable;
    }
};

void moveToFront(LRUCache* cache, LRUNode* node) {
    if (node == cache->head) return;
    
    if (node->prev) node->prev->next = node->next;
    if (node->next) node->next->prev = node->prev;
    
    if (node == cache->tail) {
        cache->tail = node->prev;
    }
    
    node->next = cache->head;
    node->prev = nullptr;
    
    if (cache->head) {
        cache->head->prev = node;
    }
    
    cache->head = node;
    
    if (!cache->tail) {
        cache->tail = node;
    }
}

void removeLRU(LRUCache* cache) {
    if (!cache->tail) return;
    
    LRUNode* toRemove = cache->tail;
    
    hashRemove(cache->hashTable, toRemove->key);
    
    if (toRemove->prev) {
        toRemove->prev->next = nullptr;
    }
    
    cache->tail = toRemove->prev;
    
    if (cache->head == toRemove) {
        cache->head = nullptr;
    }
    
    delete toRemove;
    cache->size--;
}

void lruSet(LRUCache* cache, const string& key, const string& value) {
    if (hashContains(cache->hashTable, key)) {
        hashInsert(cache->hashTable, key, value);
        
        LRUNode* current = cache->head;
        while (current) {
            if (current->key == key) {
                current->value = value;
                moveToFront(cache, current);
                break;
            }
            current = current->next;
        }
    } else {
        if (cache->size >= cache->capacity) {
            removeLRU(cache);
        }
        
        LRUNode* newNode = new LRUNode(key, value);
        
        newNode->next = cache->head;
        if (cache->head) {
            cache->head->prev = newNode;
        }
        
        cache->head = newNode;
        
        if (!cache->tail) {
            cache->tail = newNode;
        }
        
        hashInsert(cache->hashTable, key, value);
        cache->size++;
    }
}

string lruGet(LRUCache* cache, const string& key) {
    string value = hashGet(cache->hashTable, key);
    if (value.empty()) {
        return "-1";
    }
    
    LRUNode* current = cache->head;
    while (current) {
        if (current->key == key) {
            moveToFront(cache, current);
            break;
        }
        current = current->next;
    }
    
    return value;
}

void printCache(LRUCache* cache) {
    LRUNode* current = cache->head;
    while (current) {
        cout << "[" << current->key << ":" << current->value << "] ";
        current = current->next;
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "rus");
    
    int capacity, queries;
    
    cout << "\nВведите емкость кэша: ";
    cin >> capacity;
    
    cout << "Введите количество запросов: ";
    cin >> queries;
    cin.ignore();
    
    LRUCache* cache = new LRUCache(capacity);
    
    string line;
    for (int i = 0; i < queries; i++) {
        cout << "\nЗапрос " << (i + 1) << ": ";
        getline(cin, line);
        
        stringstream ss(line);
        string command, key, value;
        ss >> command;
        
        if (command == "SET") {
            if (ss >> key >> value) {
                lruSet(cache, key, value);
                cout << "Установлено: " << key << " -> " << value << endl;
                printCache(cache);
            } else {
                cout << "Ошибка: неверный формат SET" << endl;
            }
        } else if (command == "GET") {
            if (ss >> key) {
                string result = lruGet(cache, key);
                cout << "Результат GET " << key << ": " << result << endl;
                printCache(cache);
            } else {
                cout << "Ошибка: неверный формат GET" << endl;
            }
        } else {
            cout << "Неизвестная команда: " << command << endl;
        }
    }
    
    delete cache;
    
    cout << "\nПрограмма завершена." << endl;
    return 0;
}