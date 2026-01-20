#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

struct NodeL {
    string data;
    NodeL* next;
    NodeL* previous;
};

struct DoubleList {
    NodeL* head;
    NodeL* tail;
};

// Все функции, которые не изменяют список, должны принимать const DoubleList&
void addToHeadL2(DoubleList& list, const string& value);
void addToTailL2(DoubleList& list, const string& value);
void addBeforeL2(DoubleList& list, const string& targetValue, const string& newValue);
void addAfterL2(DoubleList& list, const string& targetValue, const string& newValue);
void removeFromHeadL2(DoubleList& list);
void removeFromTailL2(DoubleList& list);
void removeByValueL2(DoubleList& list, const string& value);
void removeBeforeL2(DoubleList& list, const string& value);
void removeAfterL2(DoubleList& list, const string& value);
NodeL* findL2(const DoubleList& list, const string& value); // const
void printList2(const DoubleList& list); // const
void freeList2(DoubleList& list);
void writeDoubleListToFile(const DoubleList& list, const string& filename); // const