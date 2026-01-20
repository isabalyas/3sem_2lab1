#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "../new_structures/hashtable/hashtable.h"

using namespace std;

vector<string> getAllFromTable(HashTable* table[]) {
    vector<string> result;
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashTable* temp = table[i];
        while (temp != nullptr) {
            result.push_back(temp->key);
            temp = temp->next;
        }
    }
    return result;
}

void copyTable(HashTable* source[], HashTable* dest[]) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        dest[i] = nullptr;
    }
    
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashTable* temp = source[i];
        while (temp != nullptr) {
            insertTable(dest, temp->key, temp->value);
            temp = temp->next;
        }
    }
}

void clearTable(HashTable* table[]) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashTable* temp = table[i];
        while (temp != nullptr) {
            HashTable* toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }
        table[i] = nullptr;
    }
}

void inputSet(HashTable* table[], const string& name) {
    clearTable(table);
    
    int n;
    cout << "Введите количество элементов множества " << name << ": ";
    cin >> n;
    cin.ignore();
    
    cout << "Введите " << n << " элементов:" << endl;
    for (int i = 0; i < n; i++) {
        string element;
        getline(cin, element);
        insertTable(table, element, element);
    }
}

void printSet(HashTable* table[], const string& name) {
    cout << name << " = {";
    vector<string> elements = getAllFromTable(table);
    for (size_t i = 0; i < elements.size(); i++) {
        cout << elements[i];
        if (i < elements.size() - 1) cout << ", ";
    }
    cout << "}" << endl;
}

void unionSets(HashTable* setA[], HashTable* setB[], HashTable* result[]) {
    clearTable(result);
    
    vector<string> elementsA = getAllFromTable(setA);
    for (const auto& elem : elementsA) {
        insertTable(result, elem, elem);
    }
    
    vector<string> elementsB = getAllFromTable(setB);
    for (const auto& elem : elementsB) {
        if (getValueTable(setA, elem) == "Ключ не найден") {
            insertTable(result, elem, elem);
        }
    }
}

void intersectSets(HashTable* setA[], HashTable* setB[], HashTable* result[]) {
    clearTable(result);
    
    vector<string> elementsA = getAllFromTable(setA);
    for (const auto& elem : elementsA) {
        if (getValueTable(setB, elem) != "Ключ не найден") {
            insertTable(result, elem, elem);
        }
    }
}

void differenceSets(HashTable* setA[], HashTable* setB[], HashTable* result[]) {
    clearTable(result);
    
    vector<string> elementsA = getAllFromTable(setA);
    for (const auto& elem : elementsA) {
        if (getValueTable(setB, elem) == "Ключ не найден") {
            insertTable(result, elem, elem);
        }
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    
    cout << "Задание 3: Дополнительные операции над множествами" << endl;
    cout << "==================================================" << endl;
    
    HashTable* setA[TABLE_SIZE] = {nullptr};
    HashTable* setB[TABLE_SIZE] = {nullptr};
    HashTable* result[TABLE_SIZE] = {nullptr};
    
    cout << "\n=== Множество A ===" << endl;
    inputSet(setA, "A");
    
    cout << "\n=== Множество B ===" << endl;
    inputSet(setB, "B");
    
    printSet(setA, "A");
    printSet(setB, "B");
    cout << endl;
    
    unionSets(setA, setB, result);
    printSet(result, "A ∪ B (Объединение)");
    
    intersectSets(setA, setB, result);
    printSet(result, "A ∩ B (Пересечение)");
    
    differenceSets(setA, setB, result);
    printSet(result, "A \\ B (Разность A - B)");
    
    differenceSets(setB, setA, result);
    printSet(result, "B \\ A (Разность B - A)");
    
    freeTable(setA);
    freeTable(setB);
    freeTable(result);
    
    return 0;
}