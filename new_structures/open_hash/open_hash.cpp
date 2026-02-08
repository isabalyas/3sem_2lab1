#include "open_hash.h"
#include <iostream>

// Вспомогательная функция для поиска индекса ключа
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

// Основная хэш-функция
int hashFunc(const string& key, int capacity) {
    int hash = 0;
    for (size_t i = 0; i < key.length(); i++) {
        hash = (hash * 31 + key[i]) % capacity;
    }
    return hash;
}

// Функция перехэширования
bool rehash(OpenHashTable* ht) {
    int oldCapacity = ht->capacity;
    int newCapacity = oldCapacity * 2;  // Увеличиваем размер в 2 раза
    
    // Сохраняем старую таблицу
    HashSlot* oldTable = ht->table;
    int oldSize = ht->size;
    
    // Создаем новую таблицу
    ht->table = new HashSlot[newCapacity];
    if (ht->table == nullptr) {
        // Восстанавливаем старую таблицу при ошибке
        ht->table = oldTable;
        return false;
    }
    
    // Инициализируем новую таблицу
    for (int i = 0; i < newCapacity; i++) {
        ht->table[i].status = EMPTY_SLOT;
    }
    
    ht->capacity = newCapacity;
    ht->size = 0;
    
    // Перемещаем все элементы из старой таблицы в новую
    for (int i = 0; i < oldCapacity; i++) {
        if (oldTable[i].status == OCCUPIED_SLOT) {
            // Используем внутреннюю логику вставки для избежания рекурсии
            int index = hashFunc(oldTable[i].key, newCapacity);
            int startIndex = index;
            
            // Ищем свободное место в новой таблице
            bool inserted = false;
            do {
                if (ht->table[index].status != OCCUPIED_SLOT) {
                    ht->table[index].key = oldTable[i].key;
                    ht->table[index].value = oldTable[i].value;
                    ht->table[index].status = OCCUPIED_SLOT;
                    ht->size++;
                    inserted = true;
                    break;
                }
                index = (index + 1) % newCapacity;
            } while (index != startIndex);
            
            // Если не удалось вставить (маловероятно)
            if (!inserted) {
                // Восстанавливаем состояние
                delete[] ht->table;
                ht->table = oldTable;
                ht->capacity = oldCapacity;
                ht->size = oldSize;
                return false;
            }
        }
    }
    
    // Освобождаем память старой таблицы
    delete[] oldTable;
    return true;
}

// Вставка элемента с автоматическим перехэшированием
bool hashInsert(OpenHashTable* ht, const string& key, const string& value) {
    const double LOAD_FACTOR_THRESHOLD = 0.75;
    
    // Проверяем, нужно ли перехэширование
    if ((double)ht->size / ht->capacity > LOAD_FACTOR_THRESHOLD) {
        std::cout << "Перехэширование: коэффициент заполнения " 
                  << (double)ht->size / ht->capacity * 100 
                  << "% > " << LOAD_FACTOR_THRESHOLD * 100 << "%" << std::endl;
        if (!rehash(ht)) {
            std::cout << "Ошибка перехэширования!" << std::endl;
            return false;
        }
    }
    
    // Проверяем, есть ли уже такой ключ
    int existingIndex = findKeyIndex(ht, key);
    if (existingIndex != -1) {
        ht->table[existingIndex].value = value;
        return true;
    }
    
    // Если таблица полностью заполнена
    if (ht->size >= ht->capacity) {
        std::cout << "Таблица полностью заполнена! Попытка перехэширования..." << std::endl;
        if (!rehash(ht)) {
            return false;
        }
    }
    
    // Находим место для вставки
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

// Получение значения по ключу
string hashGet(OpenHashTable* ht, const string& key) {
    int index = findKeyIndex(ht, key);
    if (index != -1 && ht->table[index].status == OCCUPIED_SLOT) {
        return ht->table[index].value;
    }
    return "";
}

// Удаление элемента
bool hashRemove(OpenHashTable* ht, const string& key) {
    int index = findKeyIndex(ht, key);
    if (index != -1 && ht->table[index].status == OCCUPIED_SLOT) {
        ht->table[index].status = DELETED_SLOT;
        ht->size--;
        return true;
    }
    return false;
}

// Проверка наличия ключа
bool hashContains(OpenHashTable* ht, const string& key) {
    return findKeyIndex(ht, key) != -1;
}

// Вывод таблицы
void hashPrint(OpenHashTable* ht) {
    cout << "Хэш-таблица (размер: " << ht->size << "/" << ht->capacity 
         << ", заполнение: " << (double)ht->size / ht->capacity * 100 << "%):\n";
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
    cout << "-----------------------------" << endl;
}

// Получение размера
int hashSize(OpenHashTable* ht) {
    return ht->size;
}

// Очистка таблицы
void hashClear(OpenHashTable* ht) {
    for (int i = 0; i < ht->capacity; i++) {
        ht->table[i].status = EMPTY_SLOT;
    }
    ht->size = 0;
}