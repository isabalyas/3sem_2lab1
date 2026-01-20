#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

struct NodeQ {
    string data;
    NodeQ* next = nullptr;
};

struct Queue {
    NodeQ* head = nullptr;
    NodeQ* tail = nullptr;
};

NodeQ* createNodeQ(const string& val);
void enqueue(Queue& q, const string& item);
string dequeue(Queue& q);
void printQueue(const Queue& q);
void freeQueue(Queue& q);
void writeQueueToFile(const Queue& q, const string& filename);