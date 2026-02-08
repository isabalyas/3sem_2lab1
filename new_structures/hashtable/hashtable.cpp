#include "hashtable.h"

// Конструктор
HashTableWithRehash::HashTableWithRehash(int initialCapacity) {
    capacity = initialCapacity;
    size = 0;
    table.resize(capacity, nullptr);
}

// Деструктор
HashTableWithRehash::~HashTableWithRehash() {
    for (int i = 0; i < capacity; ++i) {
        HashTable* temp = table[i];
        while (temp != nullptr) {
            HashTable* toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }
    }
}

// Хэш-функция
int HashTableWithRehash::hashFunction(const string& key, int tableSize) {
    int hash = 0;
    for (char ch : key) {
        hash = (hash * 31 + ch) % tableSize;
    }
    return hash % tableSize;
}

// Проверка необходимости перехэширования
bool HashTableWithRehash::needRehash() {
    return getLoadFactor() > LOAD_FACTOR_THRESHOLD;
}

// Перехэширование
void HashTableWithRehash::performRehash() {
    int newCapacity = capacity * 2;
    
    cout << "Выполняется перехэширование: " 
         << capacity << " -> " << newCapacity 
         << " (заполнение: " << getLoadFactor() * 100 << "%)" << endl;
    
    // Создаем новую таблицу
    vector<HashTable*> newTable(newCapacity, nullptr);
    
    // Перераспределяем все элементы
    for (int i = 0; i < capacity; ++i) {
        HashTable* current = table[i];
        while (current != nullptr) {
            HashTable* next = current->next;
            
            // Вычисляем новый индекс
            int newIndex = hashFunction(current->key, newCapacity);
            
            // Вставляем в новую таблицу
            if (newTable[newIndex] == nullptr) {
                newTable[newIndex] = current;
                current->next = nullptr;
            } else {
                // Находим конец цепочки
                HashTable* temp = newTable[newIndex];
                while (temp->next != nullptr) {
                    temp = temp->next;
                }
                temp->next = current;
                current->next = nullptr;
            }
            
            current = next;
        }
    }
    
    // Обновляем таблицу
    table = newTable;
    capacity = newCapacity;
}

// Вставка с автоматическим перехэшированием
void HashTableWithRehash::insertTable(const string& key, const string& value) {
    // Проверяем необходимость перехэширования
    if (needRehash()) {
        performRehash();
    }
    
    int index = hashFunction(key, capacity);
    HashTable* newNode = new HashTable{key, value, nullptr};

    if (table[index] == nullptr) {
        table[index] = newNode;
        size++;
    } else {
        HashTable* temp = table[index];
        HashTable* prev = nullptr;
        
        while (temp != nullptr) {
            if (temp->key == key) {
                // Обновляем существующий ключ
                temp->value = value;
                delete newNode;
                return;
            }
            prev = temp;
            temp = temp->next;
        }
        
        // Добавляем в конец цепочки
        if (prev != nullptr) {
            prev->next = newNode;
        }
        size++;
    }
}

// Получение значения
string HashTableWithRehash::getValueTable(const string& key) {
    int index = hashFunction(key, capacity);
    HashTable* temp = table[index];
   
    while (temp != nullptr) {
        if (temp->key == key) {
            return temp->value;
        }
        temp = temp->next;
    }
    return "Ключ не найден";
}

// Удаление
void HashTableWithRehash::removeValueTable(const string& key) {
    int index = hashFunction(key, capacity);
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
            size--;
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    cout << "Ключ не найден" << endl;
}

// Вывод таблицы
void HashTableWithRehash::printTable() {
    cout << "Хэш-таблица (размер: " << size << "/" << capacity 
         << ", заполнение: " << getLoadFactor() * 100 << "%):" << endl;
    
    for (int i = 0; i < capacity; i++) {
        cout << "Index " << i << ": ";
        HashTable* temp = table[i];
        while (temp != nullptr) {
            cout << "[" << temp->key << ": " << temp->value << "] ";
            temp = temp->next;
        }
        cout << endl;
    }
    cout << "-----------------------------" << endl;
}

// Запись в файл
void HashTableWithRehash::writeHashTableToFile(const string& filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Ошибка при открытии файла для записи" << endl;
        return;
    }

    file << "Хэш-таблица (размер: " << size << "/" << capacity 
         << ", заполнение: " << getLoadFactor() * 100 << "%):" << endl;
    
    for (int i = 0; i < capacity; ++i) {
        file << "Index " << i << ": ";
        HashTable* temp = table[i];
        while (temp != nullptr) {
            file << "[" << temp->key << ": " << temp->value << "] ";
            temp = temp->next;
        }
        file << endl;
    }

    file.close();
}