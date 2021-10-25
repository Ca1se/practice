#include <bits/stdc++.h>
using namespace std;
char arr[200];
int main() {
	scanf("%s", arr);
	int len = strlen(arr);
	if(len > 19) {
		printf("BigInteger\n");
	}else if(len > 10) {
		if(len == 19) {
			long long a;
			char tmp[20] = {};
			sscanf(arr, "%lld", &a);
			sprintf(tmp, "%lld", a);
			if(strcmp(arr, tmp)) printf("BigInteger\n");
			else printf("long\n");
		}else printf("long\n");
	}else if(len > 5) {
		int a;
		sscanf(arr, "%d", &a);
		if(a > 0) printf("int\n");
		else printf("long\n");
	}else if(len > 3) {
		short a;
		sscanf(arr, "%d", &a);
		if(a > 0) printf("short\n");
		else printf("int\n");
	}else {
		signed char a;
		sscanf(arr, "%d", &a);
		if(a > 0) printf("byte\n");
		else printf("short\n");
	}
	return 0;
}
