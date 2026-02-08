#include <iostream>
#include <string>
#include <vector>
#include "../new_structures/hashtable/hashtable.h"

using namespace std;

void initializeRomanTable(HashTableWithRehash& ht) {
    ht.insertTable("1000", "M");
    ht.insertTable("900", "CM");
    ht.insertTable("500", "D");
    ht.insertTable("400", "CD");
    ht.insertTable("100", "C");
    ht.insertTable("90", "XC");
    ht.insertTable("50", "L");
    ht.insertTable("40", "XL");
    ht.insertTable("10", "X");
    ht.insertTable("9", "IX");
    ht.insertTable("5", "V");
    ht.insertTable("4", "IV");
    ht.insertTable("1", "I");
}

string intToRomanUsingHashTable(int num) {
    if (num <= 0 || num > 3999) {
        return "Число должно быть от 1 до 3999";
    }
    
    HashTableWithRehash ht;
    initializeRomanTable(ht);
    
    int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    string result = "";
    
    for (int value : values) {
        while (num >= value) {
            string roman = ht.getValueTable(to_string(value));
            if (roman != "Ключ не найден") {
                result += roman;
                num -= value;
            }
        }
    }
    
    return result;
}

int main() {
    setlocale(LC_ALL, "rus");
    
    cout << "Преобразование целого числа в римскую цифру" << endl;
    cout << "===========================================" << endl;
    
    int number;
    cout << "Введите целое число (от 1 до 3999): ";
    cin >> number;
    
    string roman = intToRomanUsingHashTable(number);
    cout << "\nРезультат преобразования:" << endl;
    cout << number << " -> " << roman << endl;
    
    return 0;
}