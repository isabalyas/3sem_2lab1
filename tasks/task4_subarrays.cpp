#include <iostream>
#include <string>
#include "../new_structures/array/array.h"

using namespace std;

struct SubarrayResult {
    Array* subarrays;  
    int count;         
};

void generateSubarrays(const Array& arr, int start, Array& current, SubarrayResult& result) {
    if (lengthArray(current) > 0) {
        string subarrayStr = "{";
        for (int i = 0; i < lengthArray(current); i++) {
            subarrayStr += getArray(current, i);
            if (i < lengthArray(current) - 1) {
                subarrayStr += ", ";
            }
        }
        subarrayStr += "}";
        appendArray(result.subarrays[result.count], subarrayStr);
        result.count++;
    }
    
    for (int i = start; i < lengthArray(arr); i++) {
        appendArray(current, getArray(arr, i));
        generateSubarrays(arr, i + 1, current, result);
        removeArray(current, lengthArray(current) - 1);
    }
}

void printSubarrays(const SubarrayResult& result) {
    for (int i = 0; i < result.count; i++) {
        for (int j = 0; j < lengthArray(result.subarrays[i]); j++) {
            cout << getArray(result.subarrays[i], j);
        }
        if (i < result.count - 1) {
            cout << ", ";
        }
        if ((i + 1) % 5 == 0) {
            cout << endl;
        }
    }
    cout << endl;
}

void freeSubarrayResult(SubarrayResult& result) {
    for (int i = 0; i < result.count; i++) {
        freeArray(result.subarrays[i]);
    }
    delete[] result.subarrays;
    result.subarrays = nullptr;
    result.count = 0;
}

int main() {
    setlocale(LC_ALL, "rus");
    
    cout << "Задание 4: Различные подмассивы" << endl;
    cout << "===============================" << endl;
    
    int n;
    cout << "Введите количество элементов в массиве: ";
    cin >> n;
    cin.ignore();
    
    if (n <= 0) {
        cout << "Количество элементов должно быть положительным!" << endl;
        return 1;
    }
    
    Array arr;
    initArray(arr, n + 5);
    
    cout << "\nВведите элементы массива:" << endl;
    for (int i = 0; i < n; i++) {
        string element;
        getline(cin, element);
        appendArray(arr, element);
    }
    
    cout << "\nИсходный массив: {";
    for (int i = 0; i < lengthArray(arr); i++) {
        cout << getArray(arr, i);
        if (i < lengthArray(arr) - 1) {
            cout << ", ";
        }
    }
    cout << "}" << endl;
    
    SubarrayResult result;
    result.count = 0;
    result.subarrays = new Array[1 << n];
    
    for (int i = 0; i < (1 << n); i++) {
        initArray(result.subarrays[i], 10);
    }
    
    Array current;
    initArray(current, n);
    
    result.count = 1;
    appendArray(result.subarrays[0], "{}");
    
    generateSubarrays(arr, 0, current, result);
    
    cout << "\nВсе различные подмассивы (" << result.count << "):" << endl;
    printSubarrays(result);
    
    freeArray(arr);
    freeArray(current);
    freeSubarrayResult(result);
    
    return 0;
}