#include<iostream>
#include<cstdlib>
#include<ctime>
#include<string>
#define MAXN 1000
using namespace std;
class cat {
public:
    cat();
    
    string getFurColor() const;
    string getEyeColor() const;
    int getFurLength() const;

    static int cnt;
private:
    void setFurColor(const string& color);
    void setEyeColor(const string& color);
    void setFurLength(int length);

    string furColor;
    string eyeColor;
    int furLength;
    
};
int cat::cnt = 0;
cat::cat() {
    cnt++;
    const char* furColorSet[] = {"green", "red", "yellow", "blue"};
    const char* eyeColorSet[] = {"black", "blue", "brown", "red"};
    setFurColor(furColorSet[rand() % 4]);
    setEyeColor(eyeColorSet[rand() % 4]);
    setFurLength(rand() % 6 + 5);
}

void cat::setEyeColor(const string& color) {
    eyeColor = color;
}

void cat::setFurColor(const string& color) {
    furColor = color;
}

void cat::setFurLength(int length) {
    furLength = length;
}

string cat::getEyeColor() const {
    return eyeColor;
}

string cat::getFurColor() const {
    return furColor;
}

int cat::getFurLength() const {
    return furLength;
}

int main() {
    srand(time(NULL));
    cat* cage[MAXN];
    while(true){
        char ch;
        ch = getchar();
        if(ch != '\n')  break;
        cage[cat::cnt - 1] = new cat;
    }
    for(int i = 0;i < cat::cnt; i++) {
        cout << "No." << i + 1 << '\n';
        cout << "eyecolor: " << cage[i]->getEyeColor() << '\n';
        cout << "furcolor: " << cage[i]->getFurColor() << '\n';
        cout << "furlength: " << cage[i]->getFurLength() << '\n';
    }
    cout << "cats count: " << cat::cnt << '\n';
    return 0;
}