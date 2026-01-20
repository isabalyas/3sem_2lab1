#include "2list.h"

void addToHeadL2(DoubleList& list, const string& value) {
    NodeL* newNode = new NodeL;
    newNode->data = value;
    newNode->next = list.head;
    newNode->previous = nullptr;

    if (list.head != nullptr) {
        list.head->previous = newNode;
    }
    else {
        list.tail = newNode;
    }
    list.head = newNode;
}

void addToTailL2(DoubleList& list, const string& value) {
    NodeL* newNode = new NodeL;
    newNode->data = value;
    newNode->next = nullptr;
    newNode->previous = list.tail;

    if (list.tail != nullptr) {
        list.tail->next = newNode;
    } else {
        list.head = newNode;
    }
    list.tail = newNode;
}

void addBeforeL2(DoubleList& list, const string& targetValue, const string& newValue) {
    NodeL* temp = list.head;

    while (temp != nullptr) {
        if (temp->data == targetValue) {
            NodeL* newNode = new NodeL;
            newNode->data = newValue;
            newNode->next = temp;
            newNode->previous = temp->previous;

            if (temp->previous != nullptr) {
                temp->previous->next = newNode;
            } else {
                list.head = newNode; 
            }

            temp->previous = newNode;
            return;
        }
        temp = temp->next;
    }
}

void addAfterL2(DoubleList& list, const string& targetValue, const string& newValue) {
    NodeL* temp = list.head;

    while (temp != nullptr) {
        if (temp->data == targetValue) {
            NodeL* newNode = new NodeL;
            newNode->data = newValue;
            newNode->next = temp->next;
            newNode->previous = temp;

            if (temp->next != nullptr) {
                temp->next->previous = newNode;
            } else {
                list.tail = newNode; 
            }

            temp->next = newNode;
            return;
        }
        temp = temp->next;
    }
}

void removeFromHeadL2(DoubleList& list) {
    if (list.head == nullptr) return;

    NodeL* temp = list.head;
    list.head = list.head->next;

    if (list.head != nullptr) {
        list.head->previous = nullptr;
    } else {
        list.tail = nullptr;
    }
    delete temp;
}

void removeFromTailL2(DoubleList& list) {
    if (list.tail == nullptr) return;

    NodeL* temp = list.tail;
    list.tail = list.tail->previous;

    if (list.tail != nullptr) {
        list.tail->next = nullptr;
    } else {
        list.head = nullptr;
    }
    delete temp;
}

void removeByValueL2(DoubleList& list, const string& value) {
    NodeL* temp = list.head;

    while (temp != nullptr) {
        if (temp->data == value) {
            if (temp->previous != nullptr) {
                temp->previous->next = temp->next;
            }
            else {
                list.head = temp->next;
            }

            if (temp->next != nullptr) {
                temp->next->previous = temp->previous;
            }
            else {
                list.tail = temp->previous;
            }

            delete temp;
            return;
        }
        temp = temp->next;
    }
}

void removeBeforeL2(DoubleList& list, const string& value) {
    NodeL* temp = list.head;

    while (temp != nullptr) {
        if (temp->data == value) {
            if (temp->previous != nullptr) {
                NodeL* toDelete = temp->previous;
                
                if (toDelete->previous != nullptr) {
                    toDelete->previous->next = temp;
                } else {
                    list.head = temp;
                }
                
                temp->previous = toDelete->previous;
                delete toDelete;
            }
            return;
        }
        temp = temp->next;
    }
}

void removeAfterL2(DoubleList& list, const string& value) {
    NodeL* temp = list.head;

    while (temp != nullptr) {
        if (temp->data == value) {
            if (temp->next != nullptr) {
                NodeL* toDelete = temp->next;
                
                if (toDelete->next != nullptr) {
                    toDelete->next->previous = temp;
                } else {
                    list.tail = temp;
                }
                
                temp->next = toDelete->next;
                delete toDelete;
            }
            return;
        }
        temp = temp->next;
    }
}

NodeL* findL2(const DoubleList& list, const string& value) {
    NodeL* temp = list.head;
    while (temp != nullptr) {
        if (temp->data == value) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

void printList2(const DoubleList& list) {
    NodeL* temp = list.head;
    while (temp != nullptr) {
        cout << "'" << temp->data << "' ";
        temp = temp->next;
    }
    cout << endl;
}

void freeList2(DoubleList& list) {
    NodeL* current = list.head;
    while (current != nullptr) {
        NodeL* toDelete = current;
        current = current->next;
        delete toDelete;
    }
    list.head = nullptr;
    list.tail = nullptr;
}

void writeDoubleListToFile(const DoubleList& list, const string& filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Ошибка при открытии файла для записи" << endl;
        return;
    }

    NodeL* temp = list.head;
    while (temp != nullptr) {
        file << temp->data << endl;
        temp = temp->next;
    }

    file.close();
}