//好闲
#include<bits/stdc++.h>
using namespace std;

using fp = void (*) ();
using ffp = fp (*) ();
using fffp = ffp (*) ();
using ffffp = fffp (*) ();

void interestring() {
    cout << " interestring" << endl;
}

fp so() {
    cout << " so";
    return interestring;
}

ffp is() {
    cout << " is";
    return so;
} 

fffp it() {
    cout << "It";
    return is;
}

ffffp say_something() {
    return it;
}

int main() {
    say_something()()()()();
}