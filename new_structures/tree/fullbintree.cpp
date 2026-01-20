#include "fullbintree.h"

bool isFullBinaryTree(NodeT* root) {
    if (root == nullptr) {
        return true;
    }

    if (root->left == nullptr && root->right == nullptr) {
        return true;
    }

    if (root->left != nullptr && root->right != nullptr) {
        return isFullBinaryTree(root->left) && isFullBinaryTree(root->right);
    }

    return false;
}

NodeT* insertTree(NodeT* root, int key) {
    if (root == nullptr) {
        return new NodeT(key);
    }
    
    queue<NodeT*> q;
    q.push(root);
    
    while (!q.empty()) {
        NodeT* temp = q.front();
        q.pop();
        
        if (temp->left == nullptr) {
            temp->left = new NodeT(key);
            break;
        } else {
            q.push(temp->left);
        }
        
        if (temp->right == nullptr) {
            temp->right = new NodeT(key);
            break;
        } else {
            q.push(temp->right);
        }
    }
    
    return root;
}

NodeT* searchTree(NodeT* root, int key) {
    if (!root || root->key == key) {
        return root;
    }

    if (key < root->key) {
        return searchTree(root->left, key);
    }

    return searchTree(root->right, key);
}

int countNodes(NodeT* root) {
    if (root == nullptr) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int countLeaves(NodeT* root) {
    if (root == nullptr) return 0;
    
    if (root->left == nullptr && root->right == nullptr) {
        return 1;
    }
    
    return countLeaves(root->left) + countLeaves(root->right);
}

bool checkFullTreeProperty(NodeT* root) {
    if (root == nullptr) return true;
    
    int totalNodes = countNodes(root);
    int leaves = countLeaves(root);
    int internalNodes = totalNodes - leaves;
    
    return leaves == internalNodes + 1;
}

void printTree(NodeT* root, int space, int level) {
    if (root == nullptr) return;

    space += 5;

    printTree(root->right, space, level + 1);

    cout << endl;
    cout << setw(space) << root->key;
    
    if (root->left == nullptr && root->right == nullptr) {
        cout << " (leaf)";
    } else if (root->left != nullptr && root->right != nullptr) {
        cout << " (full)";
    } else {
        cout << " (half)";
    }
    cout << endl;

    printTree(root->left, space, level + 1);
}

void printTreeInfo(NodeT* root) {
    cout << "=== Информация о дереве ===" << endl;
    cout << "Общее количество узлов: " << countNodes(root) << endl;
    cout << "Количество листьев: " << countLeaves(root) << endl;
    cout << "Количество внутренних узлов: " << countNodes(root) - countLeaves(root) << endl;
    
    bool isFull = isFullBinaryTree(root);
    bool propertyHolds = checkFullTreeProperty(root);
    
    cout << "Является Full Binary Tree: " << (isFull ? "ДА" : "НЕТ") << endl;
    cout << "Свойство (листья = внутр.узлы + 1): " << (propertyHolds ? "ВЫПОЛНЕНО" : "НЕ ВЫПОЛНЕНО") << endl;
    
    if (isFull && propertyHolds) {
        cout << "✓ Дерево удовлетворяет всем свойствам Full Binary Tree!" << endl;
    } else {
        cout << "✗ Дерево НЕ является Full Binary Tree" << endl;
        if (!isFull) {
            cout << "  - Найдены узлы только с одним потомком" << endl;
        }
        if (!propertyHolds) {
            cout << "  - Нарушено свойство: листья != внутренние узлы + 1" << endl;
        }
    }
    cout << "============================" << endl;
}

void freeTree(NodeT* root) {
    if (root == nullptr) return;

    freeTree(root->left);
    freeTree(root->right);

    delete root;
}

void writeTreeToFile(NodeT* root, ofstream& file, int space, int level) {
    if (root == nullptr) return;

    space += 5;

    writeTreeToFile(root->right, file, space, level + 1);

    file << endl;
    file << setw(space) << root->key;
    
    if (root->left == nullptr && root->right == nullptr) {
        file << " (leaf)";
    } else if (root->left != nullptr && root->right != nullptr) {
        file << " (full)";
    } else {
        file << " (half)";
    }
    file << endl;

    writeTreeToFile(root->left, file, space, level + 1);
}

void writeFullTreeToFile(NodeT* root, const string& filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Ошибка при открытии файла для записи" << endl;
        return;
    }
    
    writeTreeToFile(root, file);
   
    file.close();
}

NodeT* createPerfectFullTree(int height, int& counter) {
    if (height <= 0) return nullptr;
    
    NodeT* root = new NodeT(counter++);
    
    if (height > 1) {
        root->left = createPerfectFullTree(height - 1, counter);
        root->right = createPerfectFullTree(height - 1, counter);
    }
    
    return root;
}