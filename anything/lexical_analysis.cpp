#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <map>


std::map<std::string, std::int32_t> g_symbol_list;

void initSymbolList() noexcept {
    g_symbol_list["begin"] = 1;
    g_symbol_list["if"] = 2;
    g_symbol_list["then"] = 3;
    g_symbol_list["while"] = 4;
    g_symbol_list["do"] = 5;
    g_symbol_list["end"] = 6;
    g_symbol_list["+"] = 13;
    g_symbol_list["-"] = 14;
    g_symbol_list["*"] = 15;
    g_symbol_list["/"] = 16;
    g_symbol_list[":"] = 17;
    g_symbol_list[":="] = 18;
    g_symbol_list["<"] = 20;
    g_symbol_list["<>"] = 21;
    g_symbol_list["<="] = 22;
    g_symbol_list[">"] = 23;
    g_symbol_list[">="] = 24;
    g_symbol_list["="] = 25;
    g_symbol_list[";"] = 26;
    g_symbol_list["("] = 27;
    g_symbol_list[")"] = 28;
    g_symbol_list["#"] = 0;
}

std::string getInput() noexcept {
    std::string ret;
    std::string tmp;
    while(std::getline(std::cin, tmp)) {
        ret += ' ' + tmp;
    }

    return ret;
}

void auxAnalysis(int pre, int now, const std::string& str) noexcept {
    if(now - pre >= 1) {
        bool is_number = 1;
        std::string sub = str.substr(pre, now - pre);
        for(char ch: sub) {
            if(ch < '0' || ch > '9') {
                is_number = 0;
                break;
            }
        }
        
        if(is_number) {
            printf("(11, %s)\n", sub.c_str());
        }else {
            if(sub == "begin" || sub == "if" || sub == "then" ||
                    sub == "while" || sub == "do" || sub == "end") {
                printf("(%d, %s)\n", g_symbol_list[sub], sub.c_str());
            }else {
                printf("(10, %s)\n", sub.c_str());
            }
        }
    }
}

void lexicalAnalysis(const std::string& in) noexcept {
    int pre = 0;

    for(int now = 0; now < in.size(); now++) {
        switch (in[now]) {
            case ' ':
            case '+':
            case '-':
            case '*':
            case '/':
            case '=':
            case ';':
            case '(':
            case ')':
            case '#':
                auxAnalysis(pre, now, in);
                if(in[now] != ' ') {
                    printf("(%d, %c)\n", g_symbol_list[(std::string{} + in[now])], in[now]);
                }
                pre = now + 1;
                break;
            case ':':
                auxAnalysis(pre, now, in);
                if(in.size() - now > 1 && in[now + 1] == '=') {
                    printf("(18, :=)\n");
                    now++;
                }else {
                    printf("(17, :)\n");
                }
                pre = now + 1;
                break;
            case '<':
                auxAnalysis(pre, now, in);
                if(in.size() - now > 1 && in[now + 1] == '>') {
                    printf("(21, <>)\n");
                    now++;
                }else if(in.size() - now > 1 && in[now + 1] == '=') {
                    printf("(22, <=)\n");
                    now++;
                }else {
                    printf("(20, <)\n");
                }
                pre = now + 1;
                break;
            case '>':
                auxAnalysis(pre, now, in);
                if(in.size() - now > 1 && in[now + 1] == '=') {
                    printf("(24, >=)\n");
                    now++;
                }else {
                    printf("(23, >)\n");
                }
                pre = now + 1;
                break;
            default:
                break;
        }
    }
}

int main() {
    initSymbolList();

    std::string input = getInput();

    lexicalAnalysis(input);
}
