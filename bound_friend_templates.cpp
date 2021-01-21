#include <iostream>
using namespace std;

class alloc {};

template <class T, class Alloc = alloc, size_t BufSiz = 0>
class deque {
public:
    deque() {
        cout << "deque" << endl;
    }
};

template<class T, class Sequence>
class stack;

template <class T, class Sequence>
bool operator== (const stack<T, Sequence>& x, const stack<T, Sequence>& y);
template <class T, class Sequence>
bool operator< (const stack<T, Sequence>& x, const stack<T, Sequence>& y);

template <class T, class Sequence = deque<T> >
class stack {
    friend bool operator== <> (const stack<T>& x, const stack<T>& y);
    friend bool operator< <> (const stack<T>& x, const stack<T>& y);
};

template<class T, class Sequence>
bool operator== (const stack<T, Sequence>& x, const stack<T, Sequence>& y) {
    return bool(cout << "operator==" << endl);
}

template<class T, class Sequence>
bool operator< (const stack<T, Sequence>& x, const stack<T, Sequence>& y) {
    return bool(cout << "operaotr<" << endl);
}

int main() {
    stack<int> t;
    cout << (t == t) << endl;
    stack<double> t1;
    cout << (t1 < t1) << endl;
}