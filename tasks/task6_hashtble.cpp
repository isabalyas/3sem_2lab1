#include <iostream>
#include <string>
#include <vector>
#include "../new_structures/hashtable/hashtable.h"

using namespace std;

void initializeRomanTable(HashTable* table[]) {
    insertTable(table, "1000", "M");
    insertTable(table, "900", "CM");
    insertTable(table, "500", "D");
    insertTable(table, "400", "CD");
    insertTable(table, "100", "C");
    insertTable(table, "90", "XC");
    insertTable(table, "50", "L");
    insertTable(table, "40", "XL");
    insertTable(table, "10", "X");
    insertTable(table, "9", "IX");
    insertTable(table, "5", "V");
    insertTable(table, "4", "IV");
    insertTable(table, "1", "I");
}

string intToRomanUsingTable(int num) {
    if (num <= 0 || num > 3999) {
        return "Число должно быть от 1 до 3999";
    }
    
    HashTable* table[TABLE_SIZE] = {nullptr};
    initializeRomanTable(table);
    
    int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    string result = "";
    
    for (int value : values) {
        while (num >= value) {
            string roman = getValueTable(table, to_string(value));
            if (roman != "Ключ не найден") {
                result += roman;
                num -= value;
            }
        }
    }
    
    freeTable(table);
    
    return result;
}

int main() {
    setlocale(LC_ALL, "rus");
    
    cout << "Преобразование целого числа в римскую цифру" << endl;
    cout << "===========================================" << endl;
    
    int number;
    cout << "Введите целое число (от 1 до 3999): ";
    cin >> number;
    
    string roman = intToRomanUsingTable(number);
    cout << "\nРезультат преобразования:" << endl;
    cout << number << " -> " << roman << endl;
    
    return 0;
}