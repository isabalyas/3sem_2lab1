#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

struct ListOne {
    string data;
    ListOne* next = nullptr;
};

void addToHeadL1(ListOne*& head, const string& value);
void addToTailL1(ListOne*& head, const string& value);
void addBeforeL1(ListOne*& head, const string& targetValue, const string& newValue);
void addAfterL1(ListOne*& head, const string& targetValue, const string& newValue);
void removeHeadL1(ListOne*& head);
void removeTailL1(ListOne*& head);
void removeByValueL1(ListOne*& head, const string& value);
void removeBeforeL1(ListOne*& head, const string& value);
void removeAfterL1(ListOne*& head, const string& value);
bool searchL1(ListOne* head, const string& value);
void printList1(ListOne* head);
void freeList1(ListOne*& head);
void writeListToFile(ListOne* head, const string& filename);