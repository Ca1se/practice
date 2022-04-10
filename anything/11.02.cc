#include<bits/stdc++.h>
using namespace std;
class Account {
public:
    Account(double, double, string);
    double GetBalance() const;
    int GetAccNumber() const;
    virtual void deposit(double);
    virtual void withdraw(double);
    virtual string toString() const = 0;
private:
    string createDate;
    int accountNum;
    double balance;
    double rate;
    static int count;
};
int Account::count = 0;
Account::Account(double s, double r, string date): balance(s), 
                                                    rate(r),
                                                    accountNum(Account::count++),
                                                    createDate(move(date)) {}
double Account::GetBalance() const {
    return balance;
}
int Account::GetAccNumber() const {
    return accountNum;
}
void Account::deposit(double n) {
    balance += n;
}
void Account::withdraw(double n) {
    balance -= n;
}

class CheckingAccount: public Account {
public:
    CheckingAccount(double, double, double, string);
    void deposit(double) override;
    void withdraw(double) override;
    string toString() const override;
private:
    double credit;
};
CheckingAccount::CheckingAccount(double s, double r, double c, string date): Account(s, r, date), credit(c) {}
void CheckingAccount::deposit(double n) {
    Account::deposit(n);
    cout << "存款成功， 余额为：" << GetBalance() << endl;
}
void CheckingAccount::withdraw(double n) {
    if(GetBalance() + credit < n){
        cout << "取款失败！ 透支额度不足!\n";
    }else{
        Account::withdraw(n);
        cout << "取款成功， 余额为：" << GetBalance() << endl;
    }
}
string CheckingAccount::toString() const {
    char str[200] = {0};
    sprintf(str, "account number: %d, account balance: %lf", GetAccNumber(), GetBalance());
    return str;
}
class SavingAccount: public Account {
public:
    SavingAccount(double, double, string);
    void deposit(double) override;
    void withdraw(double) override;
    string toString() const override;
};
SavingAccount::SavingAccount(double s, double r, string date): Account(s, r, date) {}
void SavingAccount::deposit(double n) {
    Account::deposit(n);
    cout << "存款成功， 余额为：" << GetBalance() << endl;
}
void SavingAccount::withdraw(double n) {
    if(GetBalance() < n){
        cout << "取款失败！ 余额不足！\n";
    }else{
        Account::withdraw(n);
        cout << "取款成功！ 余额为：" << GetBalance() << endl;
    }
}
string SavingAccount::toString() const {
    char str[200] = {0};
    sprintf(str, "account number: %d, account balance: %lf", GetAccNumber(), GetBalance());
    return str;
}
int main() {
    //-------------------test class: CheckingAccount----------------------
    CheckingAccount check(50, 1.33, 500, "2020.3.4");
    check.withdraw(400);
    check.withdraw(400);
    check.deposit(400);
    check.withdraw(400);
    cout << check.toString() << endl;
    //--------------------test class: SavingAccount-----------------------
    SavingAccount sav(50, 3.44, "2020.3.4");
    sav.withdraw(400);
    sav.deposit(400);
    sav.withdraw(400);
    cout << sav.toString() << endl;
}