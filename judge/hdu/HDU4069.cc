#include <bits/stdc++.h>
using namespace std;
const int maxc = 324 + 5;
const int maxr = 729 + 5;
const int maxl = maxc * maxr;

const int dxy[4][2] = {0, -1, 1, 0, 0, 1, -1, 0};

bool cons[9][9][4];
bool vis[9][9];
int mp[9][9], mark[9][9], ans[9][9];
int cnt, resCount;

int col[maxl], row[maxl], siz[maxc], first[maxr];
int L[maxl], R[maxl], U[maxl], D[maxl], idx;

void build(int c) {
	for(int i = 0; i <= c; i++) {
		L[i] = i - 1, R[i] = i + 1;
		D[i] = U[i] = i;
	}
	L[0] = c, R[c] = 0, idx = c;
	memset(siz, 0, sizeof siz);
	memset(first, 0, sizeof first);
}

void remove(int c) {
	L[R[c]] = L[c], R[L[c]] = R[c];
	for(int i = D[c]; i != c; i = D[i]) {
		for(int j = R[i]; j != i; j = R[j]) {
			D[U[j]] = D[j], U[D[j]] = U[j], siz[col[j]]--;
		}
	}
}

void recover(int c) {
	L[R[c]] = R[L[c]] = c;
	for(int i = U[c]; i != c; i = U[i]) {
		for(int j = L[i]; j != i; j = L[j]) {
			D[U[j]] = U[D[j]] = j, siz[col[j]]++;
		}
	}
}

void insert(int r, int c) {
	col[++idx] = c, row[idx] = r, siz[c]++;
	U[idx] = c, D[idx] = D[c], U[D[c]] = idx, D[c] = idx;
	if(!first[r]) first[r] = R[idx] = L[idx] = idx;
	else {
		L[idx] = first[r], R[idx] = R[first[r]];
		L[R[first[r]]] = idx, R[first[r]] = idx;
	}
}

void dance() {
	if(!R[0]) {
		resCount++;
		return;
	}
	int c = R[0];
	for(int i = R[c]; i; i = R[i]) if(siz[c] > siz[i]) c = i;
	remove(c);
	for(int i = D[c]; i != c; i = D[i]) {
		int r = row[i];
		int y = (r - 1) / 81;
		int x = (r - y * 81 - 1) / 9;
		int ch = r - y * 81 - x * 9;
		ans[y][x] = ch;
		for(int j = R[i]; j != i; j = R[j]) remove(col[j]);
		dance();
		if(resCount > 1) return;
		for(int j = L[i]; j != i; j = L[j]) recover(col[j]);
	}
	recover(c);
}

void dfs(int x, int y) {
	mark[y][x] = cnt;

	for(int i = 0; i < 4; i++) {
		int xx = x + dxy[i][0], yy = y + dxy[i][1];
		if(cons[y][x][i] || xx < 0 || xx > 8 || yy < 0 || yy > 8 || vis[yy][xx]) continue;
		vis[yy][xx] = true;
		dfs(xx, yy);
	}
}

void insert(int x, int y, int ch) {
	int r = y * 81 + x * 9 + ch;
	insert(r, y * 9 + ch);
	insert(r, 81 + x * 9 + ch);
	insert(r, 81 * 2 + mark[y][x] * 9 + ch);
	insert(r, 81 * 3 + y * 9 + x + 1);
}

int main() {
	int t, r;
	scanf("%d", &t);
	for(int rr = 0; rr < t; rr++) {
		memset(cons, 0, sizeof cons);
		memset(vis, 0, sizeof vis);
		memset(mp, 0, sizeof mp);
		memset(mark, 0, sizeof mark);
		cnt = 0, resCount = 0;
		for(int i = 0; i < 9; i++) {
			for(int j = 0; j < 9; j++) {
				scanf("%d", &r);
				if(r >= 128) {
					cons[i][j][3] = true;
					r -= 128;
				}
				if(r >= 64) {
					cons[i][j][2] = true;
					r -= 64;
				}
				if(r >= 32) {
					cons[i][j][1] = true;
					r -= 32;
				}
				if(r >= 16) {
					cons[i][j][0] = true;
					r -= 16;
				}
				mp[i][j] = r;
			}
		}
		for(int i = 0; i < 9; i++) {
			for(int j = 0; j < 9; j++) {
				if(!vis[i][j]) {
					vis[i][j] = true;
					dfs(j, i);
					cnt++;
				}
			}
		}
		build(maxc - 5);
		for(int i = 0; i < 9; i++) {
			for(int j = 0; j < 9; j++) {
				if(mp[i][j] != 0) insert(j, i, mp[i][j]);
				else {
					for(int k = 1; k <= 9; k++) insert(j, i, k);
				}
			}
		}
		dance();
		printf("Case %d:\n", rr + 1);
		if(!resCount) printf("No solution\n");
		else if(resCount > 1) printf("Multiple Solutions\n");
		else {
			for(int i = 0; i < 9; i++) {
				for(int j = 0; j < 9; j++) {
					printf("%d", ans[i][j]);
				}
				printf("\n");
			}
		}
	}
	return 0;
}
