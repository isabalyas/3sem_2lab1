#include "array.h"

void initArray(Array& arr, int cap) {
    arr.data = new string[cap];
    arr.size = 0;
    arr.capacity = cap;
}

void appendArray(Array& arr, const string& value) {
    if (arr.size >= arr.capacity) {
        arr.capacity *= 2;
        string* newData = new string[arr.capacity];
        for (int i = 0; i < arr.size; ++i) {
            newData[i] = arr.data[i];
        }
        delete[] arr.data;
        arr.data = newData;
    }
    arr.data[arr.size++] = value;
}

void insertArray(Array& arr, int index, const string& value) {
    if (index < 0 || index > arr.size) {
        cerr << "Индекс за пределами допустимого" << endl;
        return;
    }
    if (arr.size >= arr.capacity) {
        arr.capacity *= 2;
        string* newData = new string[arr.capacity];
        for (int i = 0; i < arr.size; ++i) {
            newData[i] = arr.data[i];
        }
        delete[] arr.data;
        arr.data = newData;
    }
    for (int i = arr.size; i > index; --i) {
        arr.data[i] = arr.data[i - 1];
    }
    arr.data[index] = value;
    arr.size++;
}

string getArray(const Array& arr, int index) {
    if (index < 0 || index >= arr.size) {
        cerr << "Индекс за пределами допустимого" << endl;
        return "";
    }
    return arr.data[index];
}

void removeArray(Array& arr, int index) {
    if (index < 0 || index >= arr.size) {
        cerr << "Индекс за пределами допустимого" << endl;
        return;
    }
    for (int i = index; i < arr.size - 1; ++i) {
        arr.data[i] = arr.data[i + 1];
    }
    arr.size--;
}

void replaceArray(Array& arr, int index, const string& value) {
    if (index < 0 || index >= arr.size) {
        cerr << "Индекс за пределами допустимого" << endl;
        return;
    }
    arr.data[index] = value;
}

int lengthArray(const Array& arr) {
    return arr.size;
}

void displayArray(const Array& arr) {
    for (int i = 0; i < arr.size; ++i) {
        cout << "'" << arr.data[i] << "' ";
    }
    cout << endl;
}

void freeArray(Array& arr) {
    delete[] arr.data;
    arr.data = nullptr;
    arr.size = 0;
    arr.capacity = 0;
}

void writeArrayToFile(const Array& arr, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка при открытии файла для записи" << endl;
        return;
    }
    for (int i = 0; i < arr.size; ++i) {
        file << arr.data[i] << endl;
    }
    file.close();
}