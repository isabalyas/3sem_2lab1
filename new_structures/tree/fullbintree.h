#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <queue>

using namespace std;

struct NodeT {
    int key;
    NodeT* left;
    NodeT* right;

    NodeT(int k) : key(k), left(nullptr), right(nullptr) {}
};

// Основные функции работы с деревом
NodeT* insertTree(NodeT* node, int key);
NodeT* searchTree(NodeT* root, int key);
void printTree(NodeT* root, int space = 0, int level = 0);
void freeTree(NodeT* root);

// Функции проверки Full Binary Tree
bool isFullBinaryTree(NodeT* root);
bool checkFullTreeProperty(NodeT* root);
void printTreeInfo(NodeT* root);

// Вспомогательные функции
int countNodes(NodeT* root);
int countLeaves(NodeT* root);

// Функции работы с файлами
void writeTreeToFile(NodeT* root, ofstream& file, int space = 0, int level = 0);
void writeFullTreeToFile(NodeT* root, const string& filename);

// Функция для создания тестового Full Binary Tree
NodeT* createPerfectFullTree(int height, int& counter);