#include <bits/stdc++.h>
using namespace std;
const int maxl = 330 * 735;
int col[maxl], row[maxl];
int L[maxl], R[maxl], U[maxl], D[maxl];
int first[maxl], siz[maxl], idx, cnt;
int ans[10][10], stk[maxl];

void build(int r, int c) {
	for(int i = 0; i <= c; i++) {
		L[i] = i - 1, R[i] = i + 1;
		U[i] = D[i] = i;
	}
	L[0] = c, R[c] = 0, idx = c;
	memset(first, 0, sizeof first);
	memset(siz, 0, sizeof siz);
}

void remove(int c) {
	L[R[c]] = L[c], R[L[c]] = R[c];
	for(int i = D[c]; i != c; i = D[i]) {
		for(int j = R[i]; j != i; j = R[j]) {
			U[D[j]] = U[j], D[U[j]] = D[j], siz[col[j]]--;
		}
	}
}

void recover(int c) {
	for(int i = U[c]; i != c; i = U[i]) {
		for(int j = L[i]; j != i; j = L[j]) {
			U[D[j]] = D[U[j]] = j, siz[col[j]]++;
		}
	}
	L[R[c]] = R[L[c]] = c;
}

void insert(int r, int c) {
	col[++idx] = c, row[idx] = r, siz[c]++;
	U[idx] = c, D[idx] = D[c], U[D[c]] = idx, D[c] = idx;
	if(first[r] == 0) {
		first[r] = L[idx] = R[idx] = idx;
	}else {
		L[idx] = first[r], R[idx] = R[first[r]];
		L[R[first[r]]] = idx, R[first[r]] = idx;
	}
}

bool dance(int dep) {
	if(R[0] == 0) {
		for(int i = 0; i < dep; i++) {
			int v = stk[i];
			int rr = (v - 1) / 81;
			int cc = (v - rr * 81 - 1) / 9;
			int w = v - rr * 81 - cc * 9;
			ans[rr][cc] = w;	
		}
		return true;
	}
	int c = R[0];
	for(int i = R[c]; i != 0; i = R[i]) if(siz[c] > siz[i]) c = i;
	remove(c);
	for(int i = D[c]; i != c; i = D[i]) {
		stk[dep] = row[i];
		for(int j = R[i]; j != i; j = R[j]) remove(col[j]);
		if(dance(dep + 1)) return true;
		for(int j = L[i]; j != i; j = L[j]) recover(col[j]);
	}
	recover(c);
	return false;
}

int GetId(int row, int col, int num) {
  return (row - 1) * 9 * 9 + (col - 1) * 9 + num;
}

void insert(int row, int col, int num) {
	int v = (row - 1) * 81 + (col - 1) * 9 + num;
	int c1 = (row - 1) * 9 + num;
	int c2 = 81 + (col - 1) * 9 + num;
	int c3 = 81 * 2 + ((row - 1) / 3 * 3 + (col - 1) / 3) * 9 + num;
	int c4 = 81 * 3 + (row - 1) * 9 + col;
	insert(v, c1);
	insert(v, c2);
	insert(v, c3);
	insert(v, c4);
}

int main() {
	int ch;
	build(729, 324);
	for(int i = 1; i <= 9; i++) {
		for(int j = 1; j <= 9; j++) {
			scanf("%d", &ch);
			for(int k = 1; k <= 9; k++) {
				if(ch && ch != k) continue;
				insert(i, j, k);
			}
		}
	}
	dance(0);
	for(int i = 0; i < 9; i++) {
		printf("%d", ans[i][0]);
		for(int j = 1; j < 9; j++) {
			printf(" %d", ans[i][j]);
		}
		printf("\n");
	}
	return 0;
}
