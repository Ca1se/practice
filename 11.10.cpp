#include<bits/stdc++.h>
using namespace std;
class employee {
public:
    employee(string name, int age): name(name), age(age) {}
    virtual void print() const;
    virtual double calculation() const = 0;
protected:
    int age;
    string name;
};
void employee::print() const {
    cout << "name:" << name << endl;
    cout << "age:" << age << endl;
}
class waiter: employee {
public:
    waiter(string name, int age, double bs, double bu): employee(name, age), basicSalary(bs), bonus(bu) {}
    virtual void print() const override;
    virtual double calculation() const override;
protected:
    double basicSalary;
    double bonus;
};
void waiter::print() const {
    employee::print();
    cout << "Basic Salary:" << basicSalary << endl;
    cout << "Bonus:" << bonus << endl;
}
double waiter::calculation() const {
    return basicSalary + bonus;
}
class singer: employee {
public:
    singer(string name, int age, int h): employee(name, age), hours(h) {}
    virtual void print() const override;
    virtual double calculation() const override;
protected:
    static const int salaryPerHour;
    int hours;
};
const int singer::salaryPerHour = 200;
void singer::print() const {
    employee::print();
    cout << "Work hours per week:" << hours << endl;
}
double singer::calculation() const {
    return hours * salaryPerHour;
}
class singer_and_waiter: virtual waiter, virtual singer {
public:
    singer_and_waiter(string name, int age, double bs, double bu): waiter(name, age, bs, bu), singer(name, age, 10){}
    void print() const override;
    double calculation() const override;
};
void singer_and_waiter::print() const {
    waiter::print();
    cout << "Work as a singer hours per week:" << hours << endl;
}
double singer_and_waiter::calculation() const {
    return waiter::calculation() + singer::calculation() * 4;
}
int main() {
//---------------------------test class: waiter------------------------
    waiter w("小红", 18, 2000, 500);
    w.print();
    cout << "每月薪水:" << w.calculation() << endl;
//---------------------------test class: singer------------------------
    singer s("小蓝", 20, 40);
    s.print();
    cout << "每周薪水:" << s.calculation() << endl;
//---------------------------test class: waiter and singer-------------
    singer_and_waiter wns("小黑", 22, 3000, 800);
    wns.print();
    cout << "每月薪水:" << wns.calculation() << endl;
}