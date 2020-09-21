#include<iostream>
#include<string>

using namespace std;

const int maxSize = 200;

struct stuinfo {
    string no;
    string name;
};

struct eduinfo {
    string school;
    string className;
    stuinfo stu[maxSize];
    int stuNum = 0;
};

void Input(eduinfo& edu) {
    string s[4];
    char choose;

    cout << "Please input school name:";
    cin >> s[0];
    cout << "Please input class name:";
    cin >> s[1];
    edu.school = s[0];
    edu.className = s[1];

    do {
        cout << "Please input student no:";
        cin >> s[2];
        cout << "Please input student name:";
        cin >> s[3];
        edu.stu[edu.stuNum].no = s[2];
        edu.stu[edu.stuNum++].name = s[3];
        cout << "Do you wanna input again?[y/n]\n";
    }while(cin >> choose && (choose == 'y' || choose == 'Y'));
}

void Output(const eduinfo& edu) {
    cout << edu.school << '\n';
    cout << '\t' << edu.className << '\n';
}

void Output(const stuinfo& stu) {
    cout << "\t\tno." << stu.no;
    cout << ' ' << stu.name << '\n';
}

int main() {
    eduinfo edu;
    Input(edu);
    Output(edu);
    for(int i = 0; i < edu.stuNum; i++){
        Output(edu.stu[i]);
    }
    return 0;
}