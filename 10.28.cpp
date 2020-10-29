#include <bits/stdc++.h>
using namespace std;
class Rational {
	double numerator,denominator;
public:
	Rational(double a = 0, double b = 1): numerator(a), denominator(b) {}
	Rational operator- () {
		return Rational(-numerator, denominator);
	}
	Rational operator+ (int t) const {
		return Rational(numerator + denominator * t, denominator);
	}
	Rational operator+ (const Rational& t) const {
		return Rational(numerator * t.denominator + t.numerator * denominator, denominator * t.denominator);
	}
	Rational& operator+= (const Rational& t) {
		*this = *this + t;
		return *this;
	}
	Rational& operator++ (int) {
		numerator += denominator;
		return *this;
	}
	operator double() const {
		return (double)numerator / denominator;
	}
	friend Rational operator+ (int t, const Rational& r);
	friend ostream& operator<< (ostream& os, const Rational& t);
};
ostream& operator<< (ostream& os, const Rational& t) {
	os << t.numerator << '/' << t.denominator;
	return os;
}
Rational operator+ (int t, const Rational& r) {
	return Rational(r.numerator + t * r.denominator, r.denominator);
}
int main()
{
	Rational rat0;
	cout << rat0 << endl;
	Rational rat1 = -rat0;
	cout << rat1 << endl;
	Rational rat2 = rat1 + 34;
	cout << rat2 << endl;
	Rational rat3;
	rat3 = 12 + rat2;
	rat3++;
	cout << rat3 << endl;
	cout << (double)rat3 << endl;

	//---------------------------------------------------
	Rational r(1, 2);
	for(int i = 2; i < 50; i++){
		r += Rational(i, i + 1);
	}
	cout << (double)r << endl;
	return 0;
}