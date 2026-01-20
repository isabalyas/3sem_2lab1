#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;

struct Array {
    string* data = nullptr;
    int size = 0;        
    int capacity = 0;    
};

void initArray(Array& arr, int cap);
void appendArray(Array& arr, const string& value);
void insertArray(Array& arr, int index, const string& value);
string getArray(const Array& arr, int index);
void removeArray(Array& arr, int index);
void replaceArray(Array& arr, int index, const string& value);
int lengthArray(const Array& arr);
void displayArray(const Array& arr);
void freeArray(Array& arr);
void writeArrayToFile(const Array& arr, const string& filename);