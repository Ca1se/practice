#include <cstdio>
#include <vector>
#include <cmath>
#include <cstring>
using namespace std;
const int maxl = 10000;
int mp[15][15], siz[maxl], col[maxl], row[maxl], first[maxl];
int L[maxl], R[maxl], U[maxl], D[maxl], idx, minn;
int ms[] = {1, 5, 14, 30, 55};
int t, n, m, rt;
bool vis[maxl], visc[500], visr[500];
vector<int> vec[5][60];
vector<int> p;

void init() {
	for(int k = 1; k <= 5; k++) {
		int cnt = 0;
		for(int i = 0; i < 2 * k + 1; i++) {
			int ad = (i & 1) ^ 1;
			for(int j = ad, r = 0; r < k + (ad ^ 1); j += 2, r++) {
				mp[i][j] = cnt++;
			}
		}
		cnt = 0;
		for(int r = 1; r <= k; r++) {
			for(int i = 1, ri = 0; ri < k - r + 1; i += 2, ri++) {
				for(int j = 1, rj = 0; rj < k - r + 1; j += 2, rj++) {
					cnt++;
					for(int di = 0; di <= (r - 1) * 2; di += 2) {
						for(int dj = 0; dj <= (r - 1) * 2; dj += 2) {
							if(di == 0) vec[k - 1][mp[i + di - 1][j + dj]].push_back(cnt);
							if(di == (r - 1) * 2) vec[k - 1][mp[i + di + 1][j + dj]].push_back(cnt);
							if(dj == 0) vec[k - 1][mp[i + di][j + dj - 1]].push_back(cnt);
							if(dj == (r - 1) * 2) vec[k - 1][mp[i + di][j + dj + 1]].push_back(cnt);
						}
					}
				}
			}
		}
	}
}

void build(int r, int c) {
	for(int i = 0; i <= c; i++) {
		L[i] = i - 1, R[i] = i + 1;
		U[i] = D[i] = i;
	}
	L[0] = c, R[c] = 0, idx = c;
	for(int i = 0; i <= r; i++) first[i] = 0;
	minn = 1000;
}

inline void remove(int c) {
	for(int i = D[c]; i != c; i = D[i]) {
		L[R[i]] = L[i], R[L[i]] = R[i];
	}
}

inline void recover(int c) {
	for(int i = U[c]; i != c; i = U[i]) {
		L[R[i]] = R[L[i]] = i;
	}
}

inline void insert(int r, int c) {
	col[++idx] = c, row[idx] = r, siz[c]++;
	U[idx] = c, D[idx] = D[c], U[D[c]] = idx, D[c] = idx;
	if(!first[r]) first[r] = L[idx] = R[idx] = idx;
	else {
		L[idx] = first[r], R[idx] = R[first[r]];
		L[R[first[r]]] = idx, R[first[r]] = idx;
	}
}

int predict() {
	int ret = 0;
	for(int i = R[0]; i; i = R[i]) vis[i] = true;
	for(int k = R[0]; k; k = R[k]) {
		if(vis[k]) {
			ret++;
			vis[k] = false;
			for(int i = D[k]; i != k; i = D[i]) {
				for(int j = R[i]; j != i; j = R[j]) {
					vis[col[j]] = false;
				}
			}
		}
	}
	return ret;
}

void dance(int cnt) {
	if(cnt + predict() >= minn) return;
	if(!R[0]) {
		minn = min(minn, cnt);
		return;
	}
	int c = R[0];
	for(int i = R[c]; i; i = R[i]) if(siz[c] > siz[i]) c = i;
	for(int i = D[c]; i != c; i = D[i]) {
		remove(i);
		for(int j = R[i]; j != i; j = R[j]) remove(j);
		dance(cnt + 1);
		for(int j = L[i]; j != i; j = L[j]) recover(j);
		recover(i);
	}
}

void del(int r) {
	remove(first[r]);
	for(int i = R[first[r]]; i != first[r]; i = R[i]) remove(i);
}

void pre() {
	for(int i = 0; i < p.size(); i++) {
		const vector<int>& it = vec[n - 1][p[i] - 1];
		for(int j = 0; j < it.size(); j++) {
			if(!visc[it[j]]) {
				visc[it[j]] = true;
				R[L[it[j]]] = R[it[j]], L[R[it[j]]] = L[it[j]];
			}
		}
	}
	for(int i = 0; i < 2 * n * (n + 1); i++) {
		if(visr[i + 1]) continue;
		const vector<int>& it = vec[n - 1][i];
		for(int j = 0; j < it.size(); j++) {
			if(!visc[it[j]]) insert(i + 1, it[j]);
		}
	}
}

int main() {
	init();
	scanf("%d", &t);
	while(t--) {
		p.clear();
		memset(visr, 0, sizeof visr);
		memset(visc, 0, sizeof visc);
		scanf("%d%d", &n, &m);
		build(2 * n * (n + 1), ms[n - 1]);
		while(m--) {
			scanf("%d", &rt);
			p.push_back(rt);
			visr[rt] = true;
		}
		pre();
		dance(0);
		printf("%d\n", minn);
	}
	return 0;
}
