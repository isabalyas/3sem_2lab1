#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct NodeS {
    string data;
    NodeS* next;
};

struct Stack {
    NodeS* top;
};

void pushStack(Stack& stack, const string& value);
string popStack(Stack& stack);
void printStack(const Stack& stack);
void freeStack(Stack& stack);
void writeStackToFile(const Stack& stack, const string& filename);