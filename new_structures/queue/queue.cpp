#include "queue.h"

NodeQ* createNodeQ(const string& val) {
    NodeQ* newNode = new NodeQ;
    newNode->data = val;
    newNode->next = nullptr;
    return newNode;
}

void enqueue(Queue& q, const string& item) {
    NodeQ* newNode = createNodeQ(item);
    if (q.tail == nullptr) {
        q.head = q.tail = newNode;
        return;
    }
    q.tail->next = newNode;
    q.tail = newNode;
}

string dequeue(Queue& q) {
    if (q.head == nullptr) {
        cout << "Очередь пуста" << endl;
        return "";
    }
    NodeQ* temp = q.head;
    string item = q.head->data;
    q.head = q.head->next;
    if (q.head == nullptr) {
        q.tail = nullptr;
    }
    delete temp;
    return item;
}

void printQueue(const Queue& q) {
    if (q.head == nullptr) {
        cout << "Очередь пуста" << endl;
        return;
    }
    NodeQ* temp = q.head;
    cout << "Очередь: ";
    while (temp != nullptr) {
        cout << "'" << temp->data << "' ";
        temp = temp->next;
    }
    cout << endl;
}

void freeQueue(Queue& q) {
    while (q.head != nullptr) {
        NodeQ* temp = q.head;
        q.head = q.head->next;
        delete temp;
    }
    q.tail = nullptr;
}

void writeQueueToFile(const Queue& q, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка при открытии файла для записи" << endl;
        return;
    }

    NodeQ* temp = q.head;
    while (temp != nullptr) {
        file << temp->data << endl;
        temp = temp->next;
    }

    file.close();
}