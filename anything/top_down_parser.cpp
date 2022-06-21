#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <map>


std::map<std::string, std::int32_t> g_symbol_list;
std::vector<std::pair<int, std::string>> g_syn_list;
int syn, flag = 0;
std::string token;

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
            // printf("(11, %s)\n", sub.c_str());
            g_syn_list.emplace_back(11, sub);
        }else {
            if(sub == "begin" || sub == "if" || sub == "then" ||
                    sub == "while" || sub == "do" || sub == "end") {
                // printf("(%d, %s)\n", g_symbol_list[sub], sub.c_str());
                g_syn_list.emplace_back(g_symbol_list[sub], sub);
            }else {
                // printf("(10, %s)\n", sub.c_str());
                g_syn_list.emplace_back(10, sub);
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
                    std::string tmp(1, in[now]);
                    // printf("(%d, %s)\n", g_symbol_list[tmp], tmp.c_str());
                    g_syn_list.emplace_back(g_symbol_list[tmp], tmp);
                }
                pre = now + 1;
                break;
            case ':':
                auxAnalysis(pre, now, in);
                if(in.size() - now > 1 && in[now + 1] == '=') {
                    // printf("(18, :=)\n");
                    g_syn_list.emplace_back(18, ":=");
                    now++;
                }else {
                    // printf("(17, :)\n");
                    g_syn_list.emplace_back(17, ":");
                }
                pre = now + 1;
                break;
            case '<':
                auxAnalysis(pre, now, in);
                if(in.size() - now > 1 && in[now + 1] == '>') {
                    // printf("(21, <>)\n");
                    g_syn_list.emplace_back(21, "<>");
                    now++;
                }else if(in.size() - now > 1 && in[now + 1] == '=') {
                    // printf("(22, <=)\n");
                    g_syn_list.emplace_back(22, "<=");
                    now++;
                }else {
                    // printf("(20, <)\n");
                    g_syn_list.emplace_back(20, "<");
                }
                pre = now + 1;
                break;
            case '>':
                auxAnalysis(pre, now, in);
                if(in.size() - now > 1 && in[now + 1] == '=') {
                    // printf("(24, >=)\n");
                    g_syn_list.emplace_back(24, ">=");
                    now++;
                }else {
                    // printf("(23, >)\n");
                    g_syn_list.emplace_back(23, ">");
                }
                pre = now + 1;
                break;
            default:
                break;
        }
    }
}

void scanner() noexcept {
    static int pos = 0;
    syn = -1;
    if(pos < g_syn_list.size()) {
        const auto& it = g_syn_list[pos];
        syn = it.first;
        token = it.second;
    }
    pos++;
}

void E();
void T();
void E1();
void T1();
void F();

int main() {
    initSymbolList();

    std::string input = getInput();

    lexicalAnalysis(input);

    scanner();
    E();
}

void E() {
	if (syn == 1) {
		scanner();
		T();
		while (syn == 26) {
			scanner();
			T();
		}
		if (syn == 6) {
			scanner();
			if (syn == 0 && flag == 0) {
				printf("success!\n");
			}
		}
		else {
			printf("语法错误，缺少end!\n");
		}
	}
	else {
		printf("error!\n");
		flag = 1;
	}
	return;

}

void T() {
	if (syn == 10) {
		scanner();
		if (syn == 18) {
			scanner();
			E1();
		}
		else {
			printf("语法有误！错误为：%s\n", token.c_str());
			flag = 1;
		}
	}
	else {
		if (flag != 1) {
			printf("语法有误，错误为：%s\n", token.c_str());
			flag = 1;
		}

	}
}

void E1() {
	T1();
	while (syn == 13 || syn == 14) {
		scanner();
		T1();
	}
	return;
}

void T1() {
	F();
	while (syn == 15 || syn == 16) {
		scanner();
		F();
	}
	return;
}
void F() {
	if (syn == 10 || syn == 11) {
		scanner();
	}
	else if (syn == 27) {
		scanner();
		E1();
		if (syn == 28)
			scanner();
		else {
			printf("没有')',语法有误！\n");
			flag = 1;
		}
	}
	else {
		printf("表达式语法有误！错误为：%s\n", token.c_str());
		flag = 1;
	}
	return;
}
