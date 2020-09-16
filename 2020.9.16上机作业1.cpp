#include<iostream>
#include<list>
#include<map>
#include<string>
using namespace std;

struct StudentsInformation {
    StudentsInformation(int no, string name): no(no), name(move(name)) {}
    int no;
    string name;
};

class Solution {
public:
    Solution() = default;
    ~Solution() = default;

    void ReceiveStudentsInfo();
    void OutputSchoolsClasses();

private:
    void OutputStudentsInfo(const string& _school, const string& _class);

    map<string, map<string, list<StudentsInformation> > > infoTable;
};

void Solution::ReceiveStudentsInfo() {
    string name, sch, cla;
    int no;
    char choose;

    do {
        cout << "Please input:\n";
        cin >> no >> name >> sch >> cla;
        infoTable[sch][cla].emplace_back(no, name);
        cout << "Do you wanna input again?[y/n]\n";
    }while (cin >> choose && choose == 'y');
}

void Solution::OutputSchoolsClasses() {
    for(auto& i: infoTable){
        cout << i.first << endl;
        for(auto& j: i.second){
            cout << '\t' << j.first << endl;
            OutputStudentsInfo(i.first, j.first);
        }
    }
}

void Solution::OutputStudentsInfo(const string &_school, const string &_class) {
    for(auto& i: infoTable[_school][_class]){
        cout << "\t\t" << i.no << ' ' << i.name << endl;
    }
}

int main() {
    Solution solve;

    solve.ReceiveStudentsInfo();
    solve.OutputSchoolsClasses();

    return 0;
}