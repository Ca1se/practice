#include <cstdio>
#include <cstring>
using namespace std;
char mp[9][9], ans[9][9];
const int maxr = 729 + 5;
const int maxc = 324 + 5;
const int maxl = maxr * maxc;

int col[maxl], row[maxl], siz[maxc], first[maxr];
int L[maxl], R[maxl], U[maxl], D[maxl], idx;

void build(int c) {
	for(int i = 0; i <= c; i++) {
		L[i] = i - 1, R[i] = i + 1;
		U[i] = D[i] = i;
	}
	L[0] = c, R[c] = 0, idx = c;
	memset(siz, 0, sizeof siz);
	memset(first, 0, sizeof first);
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
	L[R[c]] = R[L[c]] = c;
	for(int i = U[c]; i != c; i = U[i]) {
		for(int j = L[i]; j != i; j = L[j]) {
			U[D[j]] = D[U[j]] = j, siz[col[j]]++;
		}
	}
}

void insert(int r, int c) {
	col[++idx] = c, row[idx] = r, siz[c]++;
	U[idx] = c, D[idx] = D[c], U[D[c]] = idx, D[c] = idx;
	if(!first[r]) first[r] = L[idx] = R[idx] = idx;
	else {
		L[idx] = first[r], R[idx] = R[first[r]];
		L[R[first[r]]] = idx, R[first[r]] = idx;
	}
}

bool dance() {
	if(!R[0]) return true;
	int c = R[0];
	for(int i = R[0]; i; i = R[i]) if(siz[i] < siz[c]) c = i;
	remove(c);
	for(int i = D[c]; i != c; i = D[i]) {
		int r = row[i];
		int y = (r - 1) / 81;
		int x = (r - 1 - y * 81) / 9;
		int ch = r - y * 81 - x * 9;
		ans[y][x] = ch + '0';
		for(int j = R[i]; j != i; j = R[j]) remove(col[j]);
		if(dance())	return true;
		for(int j = L[i]; j != i; j = L[j]) recover(col[j]);
	}
	recover(c);
	return false;
}

void insert(int y, int x, int ch) {
	int r = y * 81 + x * 9 + ch;
	insert(r, y * 9 + ch);
	insert(r, 81 + x * 9 + ch);
	insert(r, 81 * 2 + (y / 3 * 3 + x / 3) * 9 + ch);
	insert(r, 81 * 3 + y * 9 + x + 1);
}

int main() {
	while(scanf("%s", (char*) mp) && mp[0][0] != 'e') {
		build(324);
		for(int i = 0; i < 9; i++) {
			for(int j = 0; j < 9; j++) {
				if(mp[i][j] != '.') {
					insert(i, j, mp[i][j] - '0');
				}else {
					for(int k = 1; k <= 9; k++) {
						insert(i, j, k);
					}
				}
			}
		}
		dance();
		for(int i = 0; i < 9; i++) {
			for(int j = 0; j < 9; j++) {
				printf("%c", ans[i][j]);
			}
		}
		printf("\n");
	}
	return 0;
}
