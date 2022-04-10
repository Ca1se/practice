#include<bits/stdc++.h>
using namespace std;
int main() {
	int t, n, ma, mi, av;
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d%d%d", &n, &ma, &mi, &av);
		if(ma < mi) {
			printf("no\n");
			continue;
		}
		if(n == 1) {
			if(ma == av && ma == mi) {
				printf("yes\n");
			}else {
				printf("no\n");
			}
		}else {
			int up = ma + mi + (n - 2) * ma;
			int bl = ma + mi + (n - 2) * mi;
			int ta = av * n;
			if(bl <= ta && ta <= up) {
				printf("yes\n");
			}else {
				printf("no\n");
			}
		}
	}
	return 0;
}
