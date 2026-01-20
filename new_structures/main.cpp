#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "hashtable/hashtable.h"
#include "1list/1list.h"
#include "2list/2list.h"
#include "array/array.h"
#include "queue/queue.h"
#include "stack/stack.h"
#include "tree/fullbintree.h"

using namespace std;

string extractQuotedString(stringstream& ss) {
    string token;
    ss >> token;
    
    if (!token.empty() && token[0] == '\'') {
        if (token.back() == '\'') {
            return token.substr(1, token.length() - 2);
        }
        else {
            string result = token.substr(1); 
            string nextToken;
            while (ss >> nextToken) {
                result += " " + nextToken;
                if (!nextToken.empty() && nextToken.back() == '\'') {
                    return result.substr(0, result.length() - 1); 
                }
            }
            return result; 
        }
    }
    return token; 
}

void hashtableCmds(HashTable* hashTable[]) {
    string command;
    string key, value;

    cout << "Введите команду (INSERT, GET, REMOVE, PRINT, EXIT):" << endl;

    while (true) {
        cout << "> ";
        getline(cin, command);

        stringstream ss(command);
        string action; 
        ss >> action;

        if (action == "INSERT") {
            key = extractQuotedString(ss);
            value = extractQuotedString(ss);
            if (!key.empty() && !value.empty()) {
                insertTable(hashTable, key, value);
                writeHashTableToFile(hashTable, "hashtable.txt");
            }
            else {
                cout << "> Неверный ввод. Необходимо ввести: INSERT 'ключ' 'значение'" << endl;
            }
        }
        else if (action == "GET") {
            key = extractQuotedString(ss);
            if (!key.empty()) {
                cout << "Значение: " << getValueTable(hashTable, key) << endl;
            } else {
                cout << "> Неверный ввод. Необходимо ввести: GET 'ключ'" << endl;
            }
        }
        else if (action == "REMOVE") {
            key = extractQuotedString(ss);
            if (!key.empty()) {
                removeValueTable(hashTable, key);
                writeHashTableToFile(hashTable, "hashtable.txt");
            }
            else {
                cout << "> Неверный ввод. Необходимо ввести: REMOVE 'ключ'" << endl;
            }
        }
        else if (action == "PRINT") {
            printTable(hashTable);
        }
        else if (action == "EXIT") {
            break;
        }
        else {
            cout << "> Неизвестная команда. Допутимые команды: INSERT, GET, REMOVE, PRINT, EXIT." << endl;
        }
    }
}

void list1Cmds(ListOne*& head) {
    string command;
    string value;

    cout << "Введите команду (ADDHEAD, ADDTAIL, ADDBEFORE, ADDAFTER, REMOVEHEAD, REMOVETAIL, REMOVEVALUE, REMOVEBEFORE, REMOVEAFTER, SEARCH, PRINT, EXIT):" << endl;

    while (true) {
        cout << "> ";
        getline(cin, command);

        stringstream ss(command);
        string action;
        ss >> action;

        if (action == "ADDHEAD") {
            value = extractQuotedString(ss);
            if (!value.empty()) {
                addToHeadL1(head, value);
                writeListToFile(head, "list1.txt");
            } else {
                cout << "> Неверный ввод. Необходимо ввести: ADDHEAD 'значение'" << endl;
            }
        }
        else if (action == "ADDTAIL") {
            value = extractQuotedString(ss);
            if (!value.empty()) {
                addToTailL1(head, value);
                writeListToFile(head, "list1.txt");
            }
            else {
                cout << "> Неверный ввод. Необходимо ввести: ADDTAIL 'значение'" << endl;
            }
        }
        else if (action == "ADDBEFORE") {
            string targetValue = extractQuotedString(ss);
            string newValue = extractQuotedString(ss);
            if (!targetValue.empty() && !newValue.empty()) {
                addBeforeL1(head, targetValue, newValue);
                writeListToFile(head, "list1.txt");
            }
            else {
                cout << "> Неверный ввод. Необходимо ввести: ADDBEFORE 'целевое_значение' 'новое_значение'" << endl;
            }
        }
        else if (action == "ADDAFTER") {
            string targetValue = extractQuotedString(ss);
            string newValue = extractQuotedString(ss);
            if (!targetValue.empty() && !newValue.empty()) {
                addAfterL1(head, targetValue, newValue);
                writeListToFile(head, "list1.txt");
            }
            else {
                cout << "> Неверный ввод. Необходимо ввести: ADDAFTER 'целевое_значение' 'новое_значение'" << endl;
            }
        }
        else if (action == "REMOVEHEAD") {
            removeHeadL1(head);
            writeListToFile(head, "list1.txt");
        }
        else if (action == "REMOVETAIL") {
            removeTailL1(head);
            writeListToFile(head, "list1.txt");
        }
        else if (action == "REMOVEVALUE") {
            value = extractQuotedString(ss);
            if (!value.empty()) {
                removeByValueL1(head, value);
                writeListToFile(head, "list1.txt");
            }
            else {
                cout << "> Неверный ввод. Необходимо ввести: REMOVEVALUE 'значение'" << endl;
            }
        }
        else if (action == "REMOVEBEFORE") {
            value = extractQuotedString(ss);
            if (!value.empty()) {
                removeBeforeL1(head, value);
                writeListToFile(head, "list1.txt");
            }
            else {
                cout << "> Неверный ввод. Необходимо ввести: REMOVEBEFORE 'значение'" << endl;
            }
        }
        else if (action == "REMOVEAFTER") {
            value = extractQuotedString(ss);
            if (!value.empty()) {
                removeAfterL1(head, value);
                writeListToFile(head, "list1.txt");
            }
            else {
                cout << "> Неверный ввод. Необходимо ввести: REMOVEAFTER 'значение'" << endl;
            }
        }
        else if (action == "SEARCH") {
            value = extractQuotedString(ss);
            if (!value.empty()) {
                cout << "Результат поиска для значения '" << value << "': "
                     << (searchL1(head, value) ? "Найдено" : "Не найдено") << endl;
            }
            else {
                cout << "> Неверный ввод. Необходимо ввести: SEARCH 'значение'" << endl;
            }
        }
        else if (action == "PRINT") {
            cout << "Содержимое списка: ";
            printList1(head);
        }
        else if (action == "EXIT") {
            break;
        }
        else {
            cout << "> Неизвестная команда. Допутимые команды: ADDHEAD, ADDTAIL, REMOVEHEAD, REMOVETAIL, REMOVEVALUE, REMOVEBEFORE, REMOVEAFTER, SEARCH, PRINT, EXIT." << endl;
        }
    }
}

void list2Cmds(DoubleList& list) {
    list.head = nullptr;
    list.tail = nullptr;

    string command;
    string value;

    cout << "Введите команду (ADDHEAD, ADDTAIL, ADDBEFORE, ADDAFTER, REMOVEHEAD, REMOVETAIL, REMOVEVALUE, REMOVEBEFORE, REMOVEAFTER, FIND, PRINT, EXIT):" << endl;

    while (true) {
        cout << "> ";
        getline(cin, command);

        stringstream ss(command);
        string action;
        ss >> action;

        if (action == "ADDHEAD") {
            value = extractQuotedString(ss);
            if (!value.empty()) {
                addToHeadL2(list, value);
                writeDoubleListToFile(list, "list2.txt");
            }
            else {
                cout << "> Неверный ввод. Необходимо ввести: ADDHEAD 'значение'" << endl;
            }
        }
        else if (action == "ADDTAIL") {
            value = extractQuotedString(ss);
            if (!value.empty()) {
                addToTailL2(list, value);
                writeDoubleListToFile(list, "list2.txt");
            }
            else {
                cout << "> Неверный ввод. Необходимо ввести: ADDTAIL 'значение'" << endl;
            }
        }
        else if (action == "ADDBEFORE") {
            string targetValue = extractQuotedString(ss);
            string newValue = extractQuotedString(ss);
            if (!targetValue.empty() && !newValue.empty()) {
                addBeforeL2(list, targetValue, newValue);
                writeDoubleListToFile(list, "list2.txt");
            }
            else {
                cout << "> Неверный ввод. Необходимо ввести: ADDBEFORE 'целевое_значение' 'новое_значение'" << endl;
            }
        }
        else if (action == "ADDAFTER") {
            string targetValue = extractQuotedString(ss);
            string newValue = extractQuotedString(ss);
            if (!targetValue.empty() && !newValue.empty()) {
                addAfterL2(list, targetValue, newValue);
                writeDoubleListToFile(list, "list2.txt");
            }
            else {
                cout << "> Неверный ввод. Необходимо ввести: ADDAFTER 'целевое_значение' 'новое_значение'" << endl;
            }
        }
        else if (action == "REMOVEHEAD") {
            removeFromHeadL2(list);
            writeDoubleListToFile(list, "list2.txt");
        }
        else if (action == "REMOVETAIL") {
            removeFromTailL2(list);
            writeDoubleListToFile(list, "list2.txt");
        }
        else if (action == "REMOVEVALUE") {
            value = extractQuotedString(ss);
            if (!value.empty()) {
                removeByValueL2(list, value);
                writeDoubleListToFile(list, "list2.txt");
            }
            else {
                cout << "> Неверный ввод. Необходимо ввести: REMOVEVALUE 'значение'" << endl;
            }
        }
        else if (action == "REMOVEBEFORE") {
            value = extractQuotedString(ss);
            if (!value.empty()) {
                removeBeforeL2(list, value);
                writeDoubleListToFile(list, "list2.txt");
            }
            else {
                cout << "> Неверный ввод. Необходимо ввести: REMOVEBEFORE 'значение'" << endl;
            }
        }
        else if (action == "REMOVEAFTER") {
            value = extractQuotedString(ss);
            if (!value.empty()) {
                removeAfterL2(list, value);
                writeDoubleListToFile(list, "list2.txt");
            }
            else {
                cout << "> Неверный ввод. Необходимо ввести: REMOVEAFTER 'значение'" << endl;
            }
        }
        else if (action == "FIND") {
            value = extractQuotedString(ss);
            if (!value.empty()) {
                NodeL* result = findL2(list, value);
                cout << "Результат поиска для значения '" << value << "': "
                     << (result ? "Найдено" : "Не найдено") << endl;
            }
            else {
                cout << "> Неверный ввод. Необходимо ввести: FIND 'значение'" << endl;
            }
        }
        else if (action == "PRINT") {
            cout << "Содержимое списка: ";
            printList2(list);
        }
        else if (action == "EXIT") {
            break;
        }
        else {
            cout << "> Неизвестная команда. Допутимые команды: ADDHEAD, ADDTAIL, REMOVEHEAD, REMOVETAIL, REMOVEVALUE, REMOVEBEFORE, REMOVEAFTER, FIND, PRINT, EXIT." << endl;
        }
    }
}

void arrayCmds(Array& arr) {
    string command;
    int index;
    string value;

    cout << "Введите команду (APPEND, INSERT, REMOVE, REPLACE, GET, DISPLAY, LENGTH, EXIT):" << endl;

    while (true) {
        cout << "> ";
        getline(cin, command);

        stringstream ss(command);
        string action;
        ss >> action;

        if (action == "APPEND") {
            value = extractQuotedString(ss);
            if (!value.empty()) {
                appendArray(arr, value);
                writeArrayToFile(arr, "array.txt");
            }
            else {
                cout << "> Неверный ввод. Необходимо ввести: APPEND 'значение'" << endl;
            }
        }
        else if (action == "INSERT") {
            ss >> index;
            value = extractQuotedString(ss);
            if (!ss.fail() && !value.empty()) {
                insertArray(arr, index, value);
                writeArrayToFile(arr, "array.txt");
            }
            else {
                cout << "> Неверный ввод. Необходимо ввести: INSERT <индекс> 'значение'" << endl;
            }
        }
        else if (action == "REMOVE") {
            ss >> index;
            if (!ss.fail()) {
                removeArray(arr, index);
                writeArrayToFile(arr, "array.txt");
            }
            else {
                cout << "> Неверный ввод. Необходимо ввести: REMOVE <индекс>" << endl;
            }
        }
        else if (action == "REPLACE") {
            ss >> index;
            value = extractQuotedString(ss);
            if (!ss.fail() && !value.empty()) {
                replaceArray(arr, index, value);
                writeArrayToFile(arr, "array.txt");
            }
            else {
                cout << "> Неверный ввод. Необходимо ввести: REPLACE <индекс> 'значение'" << endl;
            }
        }
        else if (action == "GET") {
            ss >> index;
            if (!ss.fail()) {
                string result = getArray(arr, index);
                if (!result.empty()) {
                    cout << "Элемент по индексу " << index << ": '" << result << "'" << endl;
                }
            }
            else {
                cout << "> Неверный ввод. Необходимо ввести: GET <индекс>" << endl;
            }
        }
        else if (action == "DISPLAY") {
            cout << "Содержимое массива: ";
            displayArray(arr);
        }
        else if (action == "LENGTH") {
            cout << "Длина массива: " << lengthArray(arr) << endl;
        }
        else if (action == "EXIT") {
            break;
        }
        else {
            cout << "> Неизвестная команда. Допутимые команды: APPEND, INSERT, REMOVE, REPLACE, GET, DISPLAY, LENGTH, EXIT." << endl;
        }
    }
}

void queueCmds(Queue& q) {
    q.head = q.tail = nullptr;

    string command;
    string value;

    cout << "Введите команду (ENQUEUE, DEQUEUE, PRINT, EXIT):" << endl;

    while (true) {
        cout << "> ";
        getline(cin, command);

        stringstream ss(command);
        string action;
        ss >> action;

        if (action == "ENQUEUE") {
            value = extractQuotedString(ss);
            if (!value.empty()) {
                enqueue(q, value);
                writeQueueToFile(q, "queue.txt");
            }
            else {
                cout << "> Неверный ввод. Необходимо ввести: ENQUEUE 'значение'" << endl;
            }
        }
        else if (action == "DEQUEUE") {
            string result = dequeue(q);
            if (!result.empty()) {
                cout << "Извлеченный элемент: '" << result << "'" << endl;
            }
            writeQueueToFile(q, "queue.txt");
        }
        else if (action == "PRINT") {
            printQueue(q);
        }
        else if (action == "EXIT") {
            break;
        }
        else {
            cout << "> Неизвестная команда. Допутимые команды: ENQUEUE, DEQUEUE, PRINT, EXIT." << endl;
        }
    }
}

void stackCmds(Stack& stack) {
    stack.top = nullptr;

    string command;
    string value;

    cout << "Введите команду (PUSH, POP, PRINT, EXIT):" << endl;

    while (true) {
        cout << "> ";
        getline(cin, command);

        stringstream ss(command);
        string action;
        ss >> action;

        if (action == "PUSH") {
            value = extractQuotedString(ss);
            if (!value.empty()) {
                pushStack(stack, value);
                writeStackToFile(stack, "stack.txt");
            } else {
                cout << "> Неверный ввод. Необходимо ввести: PUSH 'значение'" << endl;
            }
        }
        else if (action == "POP") {
            popStack(stack);
            writeStackToFile(stack, "stack.txt");
        }
        else if (action == "PRINT") {
            printStack(stack);
        }
        else if (action == "EXIT") {
            break;
        }
        else {
            cout << "> Неизвестная команда. Допутимые команды: PUSH, POP, PRINT, EXIT." << endl;
        }
    }
}

void treeCmds(NodeT*& root) {
    string command;
    int value;

    cout << "Введите команду (INSERT, SEARCH, PRINT, CHECK, INFO, EXIT):" << endl;

    while (true) {
        cout << "> ";
        getline(cin, command);

        stringstream ss(command);
        string action;
        ss >> action;

        if (action == "INSERT") {
            ss >> value;
            if (!ss.fail()) {
                root = insertTree(root, value);
                writeFullTreeToFile(root, "tree.txt");
                cout << "> Узел " << value << " добавлен" << endl;
            }
            else {
                cout << "> Неверный ввод. Необходимо ввести: INSERT <значение>" << endl;
            }
        }
        else if (action == "SEARCH") {
            if (ss >> value) {
                NodeT* result = searchTree(root, value);
                cout << "> Результат поиска для значения " << value << ": "
                     << (result ? "Найдено" : "Не найдено") << endl;
            }
            else {
                cout << "> Неверный ввод. Необходимо ввести: SEARCH <значение>" << endl;
            }
        }
        else if (action == "PRINT") {
            if (root == nullptr) {
                cout << "> Дерево пустое" << endl;
            } else {
                printTree(root);
                cout << endl;
            }
        }
        else if (action == "CHECK") {
            bool isFull = isFullBinaryTree(root);
            bool propertyHolds = checkFullTreeProperty(root);
            
            cout << "> Проверка Full Binary Tree:" << endl;
            cout << ">   - Структурная проверка: " << (isFull ? "ПРОЙДЕНА" : "НЕ ПРОЙДЕНА") << endl;
            cout << ">   - Математическое свойство: " << (propertyHolds ? "ВЫПОЛНЕНО" : "НЕ ВЫПОЛНЕНО") << endl;
            
            if (isFull && propertyHolds) {
                cout << "> Дерево является Full Binary Tree!" << endl;
            } else {
                cout << "> Дерево НЕ является Full Binary Tree" << endl;
            }
        }
        else if (action == "INFO") {
            if (root == nullptr) {
                cout << "> Дерево пустое" << endl;
            } else {
                printTreeInfo(root);
            }
        }
        else if (action == "EXIT") {
            break;
        }
        else {
            cout << "> Неизвестная команда. Допустимые команды: INSERT, SEARCH, PRINT, CHECK, INFO, EXIT." << endl;
        }
    }
}

int main() {
    HashTable* hashTable[TABLE_SIZE] = {nullptr};
    ListOne* head = nullptr;
    DoubleList list;
    Array arr;
    initArray(arr, 2);
    Queue q;
    Stack stack;
    NodeT* root = nullptr;

    string command;

    cout << "> Выберите структуру данных (HASHTABLE, LIST1, LIST2, ARRAY, QUEUE, STACK, FULLBINTREE, EXIT):" << endl;

    while (true) {
        cout << "> ";
        getline(cin, command);

        if (command == "HASHTABLE") {
            hashtableCmds(hashTable);
        }
        else if (command == "LIST1") {
            list1Cmds(head);
        }
        else if (command == "LIST2") {
            list2Cmds(list);
        }
        else if (command == "ARRAY") {
            arrayCmds(arr);
        }
        else if (command == "QUEUE") {
            queueCmds(q);
        }
        else if (command == "STACK") {
            stackCmds(stack);
        }
        else if (command == "FULLBINTREE") {
            treeCmds(root);
        }
        else if (command == "EXIT") {
            break;
        }
        else {
            cout << "> Неизвестная команда. Доступные команды: HASHTABLE, LIST1, LIST2, ARRAY, QUEUE, STACK, FULLBINTREE, EXIT." << endl;
        }
    }

    freeTable(hashTable);
    freeList1(head);
    freeList2(list);
    freeArray(arr);
    freeQueue(q);
    freeStack(stack);
    freeTree(root);

    cout << "Программа завершена. Все ресурсы освобождены." << endl;
    return 0;
}