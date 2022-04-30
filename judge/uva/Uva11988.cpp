#include<bits/stdc++.h>
using namespace std;
int main() {
    list<string> l;
    char buf[100000 + 5];
    while(scanf("%s", buf) == 1) {
        l.clear();
        int len = strlen(buf), sgl = 0, sech = 0;
        char* pre = buf;
        while(1) {
            if(!sech) {
                char* pos = find_if(pre, buf + len, [](char ch) {
                    return ch == '[' || ch == ']';
                });
                if(pos != buf + len) {
                    if(sgl) l.emplace_front(pre, pos);
                    else    l.emplace_back(pre, pos);
                    pre = pos;
                }else{
                    if(sgl) l.emplace_front(pre, buf + len);
                    else    l.emplace_back(pre, buf + len);
                    break;
                }
                sech = 1;
            }else {
                char* pos = find_if(pre, buf + len, [](char ch) {
                    return ch != '[' && ch != ']';
                });
                if(pos != buf + len) {
                    if(*(pos - 1) == '[')   sgl = 1;
                    else   sgl = 0;
                    pre = pos;
                }else {
                    break;
                }
                sech = 0;
            }
        }
        for(auto& it: l) {
            printf("%s", it.c_str());
        }
        printf("\n");
    } 
    return 0;
}