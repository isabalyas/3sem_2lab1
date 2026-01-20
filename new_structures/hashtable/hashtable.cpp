#include "hashtable.h"

int hashFunction(const string& key) {
    int hash = 0;
    for (char ch : key) {
        hash += ch;
    }
    return hash % TABLE_SIZE;
}

void insertTable(HashTable* table[], const string& key, const string& value) {
    int index = hashFunction(key);
    HashTable* newNode = new HashTable{key, value, nullptr};

    if (table[index] == nullptr) {
        table[index] = newNode; 
    } else {
        HashTable* temp = table[index];
        while (temp != nullptr) {
            if (temp->key == key) {
                temp->value = value;
                delete newNode;
                return;
            }
            if (temp->next == nullptr) {
                break;
            }
            temp = temp->next;
        }
        temp->next = newNode;
    }
}


string getValueTable(HashTable* table[], const string& key) {
    int index = hashFunction(key);
    HashTable* temp = table[index];
   
    while (temp != nullptr) {
        if (temp->key == key) {
            return temp->value;
        }
        temp = temp->next;
    }
    return "Ключ не найден";
}

void removeValueTable(HashTable* table[], const string& key) {
    int index = hashFunction(key);
    HashTable* temp = table[index];
    HashTable* prev = nullptr;

    while (temp != nullptr) {
        if (temp->key == key) {
            if (prev == nullptr) {
                table[index] = temp->next;
            } else {
                prev->next = temp->next;
            }
            delete temp;
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    cout << "Ключ не найден" << endl;
}

void printTable(HashTable* table[]) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        cout << "Index " << i << ": ";
        HashTable* temp = table[i];
        while (temp != nullptr) {
            cout << "[" << temp->key << ": " << temp->value << "] ";
            temp = temp->next;
        }
        cout << endl;
    }
}

void freeTable(HashTable* table[]) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        HashTable* temp = table[i];
        while (temp != nullptr) {
            HashTable* toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }
    }
}

void writeHashTableToFile(HashTable* table[], const string& filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Ошибка при открытии файла для записи" << endl;
        return;
    }

    for (int i = 0; i < TABLE_SIZE; ++i) {
        HashTable* temp = table[i];
        while (temp != nullptr) {
            file << "[" << temp->key << ": " << temp->value << "] ";
            temp = temp->next;
        }
        file << endl;
    }

    file.close();
}