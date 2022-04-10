#include <bits/stdc++.h>
using namespace std;
const int FAC[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
const int maxn = 500000;
bool vis[maxn];
char ans[9][maxn];
int pre[9][maxn];
int cnt = 0;
int Cantor(const char* arr, int n) {
    int res = 0;
    for(int i = 0; i < n; i++) {
        int small = 0;
        for(int j = i + 1; j < n; j++) {
            if(arr[i] > arr[j]) small++;
        }
        res += small * FAC[n - i - 1];
    }
    return res;
}

struct S {
	S(int p, char pre, const string& mp):
		p(p), pre(pre), mp(mp) {}
	S(int p, const string& mp): p(p), pre('w'), mp(mp) {}
	int p;
	char pre;
	string mp;
};

void bfs(const string& s, int p) {
	memset(vis, 0, sizeof vis);
	queue<S> q;
	q.emplace(p, s);
	int hash = Cantor(s.c_str(), 9);
	vis[hash] = true;
	ans[p][hash] = 'w';
	while(!q.empty()) {
		auto& it = q.front();
		auto& mp = it.mp;
		int pre_hash = Cantor(mp.c_str(), 9);
		
		if(it.p < 6 && it.pre != 'u') {
			swap(mp[it.p], mp[it.p + 3]);
			hash = Cantor(mp.c_str(), 9);
			if(!vis[hash]) {
				vis[hash] = true;
				pre[p][hash] = pre_hash;
				ans[p][hash] = 'd';
				q.emplace(it.p + 3, 'd', mp);
			}
			swap(mp[it.p], mp[it.p + 3]);
		}

		if(it.p % 3 != 0 && it.pre != 'r') {
			swap(mp[it.p], mp[it.p - 1]);
			hash = Cantor(mp.c_str(), 9);
			if(!vis[hash]) {
				vis[hash] = true;
				pre[p][hash] = pre_hash;
				ans[p][hash] = 'l';
				q.emplace(it.p - 1, 'l', mp);
			}
			swap(mp[it.p], mp[it.p - 1]);
		}

		if(it.p % 3 != 2 && it.pre != 'l') {
			swap(mp[it.p], mp[it.p + 1]);
			hash = Cantor(mp.c_str(), 9);
			if(!vis[hash]) {
				vis[hash] = true;
				pre[p][hash] = pre_hash;
				ans[p][hash] = 'r';
				q.emplace(it.p + 1, 'r', mp);
			}
			swap(mp[it.p], mp[it.p + 1]);
		}

		if(it.p > 2 && it.pre != 'd') {
			swap(mp[it.p], mp[it.p - 3]);
			hash = Cantor(mp.c_str(), 9);
			if(!vis[hash]) {
				vis[hash] = true;
				pre[p][hash] = pre_hash;
				ans[p][hash] = 'u';
				q.emplace(it.p - 3, 'u', mp);
			}
		}

		q.pop();
	}
}

int main() {
	int t;
	char str1[10], str2[10];
	map<char, char> y;
	scanf("%d", &t);
	string s = "12345678";
	for(int i = 0; i < s.size(); i++) {
		s.insert(i, "X");
		bfs(s, i);
		s.erase(s.begin() + i);
	}
	s.push_back('X');
	bfs(s, 8);
	int p;
	while(t--) {
		scanf("%s%s", str1, str2);
		int c = 1;
		for(int i = 0; i < 9; i++) {
			if(str1[i] == 'X') {
				p = i;
			}else {
				y[str1[i]] = '0' + c++;
			}
		}
		for(int i = 0; i < 9; i++) {
			if(str2[i] != 'X') {
				str2[i] = y[str2[i]];
			}
		}
		stack<char> st;
		int hash = Cantor(str2, 9);
		while(ans[p][hash] != 'w') {
			st.push(ans[p][hash]);
			hash = pre[p][hash];
		}
		printf("Case %d: %d\n", ++cnt, st.size());
		while(!st.empty()) {
			printf("%c", st.top());
			st.pop();
		}
		printf("\n");
	}
	return 0;
}
