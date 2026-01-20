#include <iostream>
#include <string>
#include <algorithm>
#include "../new_structures/tree/fullbintree.h"

using namespace std;

struct BSTNode {
    int value;
    BSTNode* left;
    BSTNode* right;
    
    BSTNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

BSTNode* insertBST(BSTNode* node, int value) {
    if (node == nullptr) {
        return new BSTNode(value);
    }
    
    if (value < node->value) {
        node->left = insertBST(node->left, value);
    } else if (value > node->value) {
        node->right = insertBST(node->right, value);
    }
    
    return node;
}

bool containsBST(BSTNode* node, int value) {
    if (node == nullptr) {
        return false;
    }
    
    if (value == node->value) {
        return true;
    } else if (value < node->value) {
        return containsBST(node->left, value);
    } else {
        return containsBST(node->right, value);
    }
}

int heightBST(BSTNode* node) {
    if (node == nullptr) {
        return 0;
    }
    
    int leftHeight = heightBST(node->left);
    int rightHeight = heightBST(node->right);
    
    return max(leftHeight, rightHeight) + 1;
}

void printTree(BSTNode* node, int depth = 0) {
    if (node == nullptr) return;
    printTree(node->right, depth + 1);
    
    for (int i = 0; i < depth; i++) {
        cout << "    ";
    }

    cout << node->value << endl;
    
    printTree(node->left, depth + 1);
}

void freeBST(BSTNode* node) {
    if (node == nullptr) return;
    freeBST(node->left);
    freeBST(node->right);
    delete node;
}

int main() {
    setlocale(LC_ALL, "rus");
    
    cout << "Задание 5: Высота бинарного дерева поиска" << endl;
    cout << "========================================" << endl;
    
    BSTNode* root = nullptr;
    string input;
    
    int counter = 0;
    while (true) {
        getline(cin, input);
        
        if (input.empty()) {
            if (counter == 0) {
                cout << "Введите хотя бы одно число!" << endl;
                continue;
            }
            break;
        }
        
        try {
            int value = stoi(input);
            
            if (containsBST(root, value)) {
                cout << "Число " << value << " уже есть в дереве" << endl;
            } else {
                root = insertBST(root, value);
                counter++;
            }
        } catch (...) {
            cout << "Ошибка! Введите целое число" << endl;
        }
    }
    
    cout << "\n" << string(50, '=') << endl;
    cout << "РЕЗУЛЬТАТЫ" << endl;
    cout << string(50, '=') << endl;
    
    if (root == nullptr) {
        cout << "Дерево пустое" << endl;
    } else {
        int treeHeight = heightBST(root);
        cout << "Высота дерева: " << treeHeight << endl;
        
        printTree(root);
    }
    
    freeBST(root);
    return 0;
}


/*10
5
15
3
7
12
20*/