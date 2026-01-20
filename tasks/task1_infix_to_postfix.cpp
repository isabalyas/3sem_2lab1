#include <iostream>
#include <string>
#include <cctype>
#include "../new_structures/stack/stack.h"

using namespace std;

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

string infixToPostfix(const string& expression) {
    Stack operators;
    operators.top = nullptr;
    
    string postfix;
    
    for (size_t i = 0; i < expression.length(); ++i) {
        char token = expression[i];
        
        if (token == ' ') {
            continue;
        }
        
        if (isalnum(token)) {
            postfix += token;
            postfix += ' ';
        } else if (isOperator(token)) {
            while (operators.top != nullptr && 
                   precedence(operators.top->data[0]) >= precedence(token)) {
                postfix += popStack(operators);
                postfix += ' ';
            }
            pushStack(operators, string(1, token));
        } else if (token == '(') {
            pushStack(operators, string(1, token));
        } else if (token == ')') {
            while (operators.top != nullptr && operators.top->data != "(") {
                postfix += popStack(operators);
                postfix += ' ';
            }
            if (operators.top != nullptr && operators.top->data == "(") {
                popStack(operators);
            }
        }
    }
    
    while (operators.top != nullptr) {
        postfix += popStack(operators);
        postfix += ' ';
    }
    
    if (!postfix.empty() && postfix.back() == ' ') {
        postfix.pop_back();
    }
    
    freeStack(operators);
    return postfix;
}

int main() {
    setlocale(LC_ALL, "rus");
    
    cout << "Задание 1: Преобразование инфиксной нотации в постфиксную" << endl;
    cout << "========================================================" << endl;
    
    string infixExpression;
    cout << "Введите инфиксное выражение ";
    getline(cin, infixExpression);
    
    string postfixExpression = infixToPostfix(infixExpression);
    cout << "Постфиксное выражение: " << postfixExpression << endl;
}