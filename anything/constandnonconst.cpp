#include<iostream>
#include<string>
#include<cstring>

class cString {
public:
    cString(std::string s);
    cString(const char* ps);
    cString(std::string s, int pos, size_t _size);
    cString(const char* start, const char* end);
    ~cString();
    const char& operator[] (size_t pos) const {
        if(str == NULL){
            std::cerr << "This variable has not been initalized" << std::endl;
            exit(-1);
        }else if(pos < 0 || pos >= strlen(str)){
            std::cerr << "cString: out of range" << std::endl;
            exit(-1);
        }
        return str[pos];
    }
    char& operator[] (size_t pos) {
        return
            const_cast<char&>(
                static_cast<const cString&>(*this)
                    [pos]
            );
    }
private:
    char* str = NULL;
};

cString::cString(std::string s) {
    size_t len = s.size();
    str = new char[len + 1];
    strcpy(str, s.c_str());
}

cString::cString(const char* ps) {
    size_t len = strlen(ps);
    str = new char[len + 1];
    strcpy(str, ps);
}

cString::cString(std::string s, int pos, size_t _size) {
    str = new char[_size + 1];
    strcpy(str, s.substr(pos, _size).c_str());
}

cString::cString(const char* start, const char* end) {
    size_t len = end - start; 
    str = new char[len + 1];
    strncpy(str, start, len);
}

cString::~cString() {
    if(str != NULL) delete[] str;
}

int main() {
    cString s("hello world");
    for(int i = 0; i < 11; i++){
        std::cout << s[i];
    }
}