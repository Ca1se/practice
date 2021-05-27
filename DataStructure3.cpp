#include <bits/stdc++.h>
using namespace std;

template <class T, int initialSize = 500, int extendSize = 500>
class Stack {
private:
    size_t size;
    size_t nowMaxSize;
    T* data;

public:
    Stack(): size(0), nowMaxSize(initialSize), data(new T[nowMaxSize]) {}
    ~Stack() {
        delete[] data;
    }

    void push(const T & e) {
        if(size == nowMaxSize) {
            nowMaxSize += extendSize;
            T* t = new T[nowMaxSize];
            memcpy(t, data, sizeof(T) * size);
            delete[] data;
            data = t;
        }
        data[size++] = e;
    }

    void pop() {
        if(size)    size--;
    }

    const T& top() const {
        if(size == 0) {
            throw "stack is empty.";
        }
        return data[size - 1];
    }

    bool empty() const {
        return size == 0;
    }
};
//中缀转后缀
string infix2suffix(const string& infix) {
    map<char, int> priority = {{'(', 0}, {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};
    Stack<char> s;
    string res; 
    for(auto ch: infix) {
        if(ch == ' ')   continue;
        else if('0' <= ch && ch <= '9') {
            res.push_back(ch);
        }else if(ch == '(') {
            s.push(ch);
        }else if(ch == ')') {
            while(s.top() != '(') {
                res.push_back(s.top());
                s.pop();
            }
            s.pop();
        }else {
            while(!s.empty() && priority[s.top()] >= priority[ch]) {
                res.push_back(s.top());
                s.pop();
            }
            s.push(ch);
        }
    }
    while(!s.empty()) {
        res.push_back(s.top());
        s.pop();
    }
    return res;
}

double calculate_suffix(const string& suffix) {
    Stack<double> s;
    for(auto ch: suffix) {
        if('0' <= ch && ch <= '9') {
            s.push(ch - '0');
        }else {
            double r = s.top(); s.pop();
            double l = s.top(); s.pop();
            if(ch == '+')  s.push(r + l);
            else if(ch == '-')  s.push(l - r);
            else if(ch == '*')  s.push(l * r);
            else if(ch == '/')  s.push(l / r);
        }
    }
    return s.top();
}

int main() {
    cout << "Please input the infix expression:\n";
    string expression, suffix;
    cin >> expression;
    suffix = infix2suffix(expression); 
    cout << suffix << endl;
    cout << calculate_suffix(suffix) << endl;

    return 0;
}
