#include<iostream>
#include<string>
#include<cstring>
using namespace std;

const int maxn = 26;
int G[maxn][maxn], in[maxn], out[maxn], nw, into;

void dfs(int inn){
    for(int i = 0; i < maxn; i++){
        if(G[inn][i]){
            G[inn][i]--;G[i][inn]--;
            dfs(i);
        }
    }
}

bool judge() {
    int c = 0;
    for(int i = 0; i < maxn; i++){
        if(in[i] != out[i]){
            if(c == 2 || abs(in[i] - out[i]) > 1){
                return false;
            }
            c++;
        }
    }
    dfs(into);
    for(int i = 0; i < maxn; i++){
        for(int j = 0; j < maxn; j++){
            if(G[i][j]) return false;
        }
    }
    return true;
}

int main() {
    //freopen("test.in", "r", stdin);
    //freopen("test.out", "w", stdout);
    int test;
    string s;
    cin >> test;
    while (test--){
        memset(G, 0, sizeof(G));
        memset(in, 0, sizeof(in));
        memset(out, 0, sizeof(out));
        cin >> nw;
        for(int i = 0; i < nw; i++){
            cin >> s;
            char f = s.front(), b = s.back();
            G[f - 'a'][b - 'a']++;G[b - 'a'][f - 'a']++;
            in[b - 'a']++;
            out[f - 'a']++;
            into = f - 'a';
        }
        if(judge()){
            cout << "Ordering is possible." << endl;
        }else{
            cout << "The door cannot be opened." << endl;
        }
    }
    return 0;
}