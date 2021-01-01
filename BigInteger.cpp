#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct BigInteger {
    static const int BASE = 100000000;
    static const int WIDTH = 8;
    vector<int> s;

    BigInteger(long long num = 0) {
        *this = num;
    }

    BigInteger(const string& num) {
        *this = num;
    }

    BigInteger& operator= (long long num) {
        s.clear();
        do {
            s.push_back(num % BASE);
            num /= BASE;
        }while(num > 0);
        return *this;
    }

    BigInteger& operator= (const string& num) {
        s.clear();
        for(int i = num.size(); i > 0; i -= WIDTH) {
            int start = max(0, i - WIDTH);
            int val = atoi(num.substr(start, min(i - start, 8)).c_str());
            s.push_back(val);
        }
        return *this;
    }

    BigInteger operator+ (const BigInteger& integer) const {
        BigInteger t;
        t.s.clear();
        int pre = 0, mlen = min(this->s.size(), integer.s.size()),
                     dlen = abs(int(this->s.size()) - int(integer.s.size()));
        const vector<int>& it = (int(this->s.size()) > int(integer.s.size())) ? this->s : integer.s;
        for(int i = 0; i < mlen; i++) {
            pre = this->s[i] + integer.s[i] + pre;
            t.s.push_back(pre % BASE);
            pre /= BASE;
        }
        for(int i = 0; i < dlen; i++) {
            if(pre) {
                pre = it[i + mlen] + pre;
                t.s.push_back(pre % BASE);
                pre /= BASE;
            }else{
                t.s.push_back(it[i + mlen]);
            }
        }
        if(pre) t.s.push_back(pre);
        return t;
    }

    BigInteger operator+ (long long num) const {
        return *this + BigInteger(num);
    }

    BigInteger operator+ (const string& num) const {
        return *this + BigInteger(num);
    }

    BigInteger& operator+= (const BigInteger& integer) {
        *this = *this + integer;
        return *this;
    }

    BigInteger& operator+= (long long num) {
        *this = *this + BigInteger(num);
        return *this;
    }

    BigInteger& operator+= (const string& num) {
        *this = *this + BigInteger(num);
        return *this;
    }

    friend ostream& operator<< (ostream& os, const BigInteger& integer) {
        char buf[20] = {0};
        os << integer.s.back();
        for(int i = integer.s.size() - 2; i >= 0; i--) {
            sprintf(buf, "%08d", integer.s[i]);
            os << buf;
        }
        return os;
    }

    friend istream& operator>> (istream& is, BigInteger& integer) {
        string num;
        if(!(is >> num))    return is;
        integer = num;
        return is;
    }
};