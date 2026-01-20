#include "stack.h"

void pushStack(Stack& stack, const string& value) {
    NodeS* newNode = new NodeS();
    newNode->data = value;
    newNode->next = stack.top;
    stack.top = newNode;
}

string popStack(Stack& stack) {  
    if (stack.top == nullptr) {
        cout << "Стек пуст" << endl;
        return "";
    }
    NodeS* temp = stack.top;
    string item = stack.top->data;
    stack.top = stack.top->next;
    delete temp;
    return item;
}

void printStack(const Stack& stack) {
    if (stack.top == nullptr) {
        cout << "Стек пуст" << endl;
        return;
    }
    NodeS* temp = stack.top;
    cout << "Элементы стека: ";
    while (temp != nullptr) {
        cout << "'" << temp->data << "' ";
        temp = temp->next;
    }
    cout << endl;
}

void freeStack(Stack& stack) {
    while (stack.top != nullptr) {
        NodeS* temp = stack.top;
        stack.top = stack.top->next;
        delete temp;
    }
}

void writeStackToFile(const Stack& stack, const string& filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Ошибка при открытии файла для записи" << endl;
        return;
    }

    NodeS* temp = stack.top;
    while (temp != nullptr) {
        file << temp->data << endl;
        temp = temp->next;
    }

    file.close();
}