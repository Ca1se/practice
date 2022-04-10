// 前缀和, 将问题化为求和为0区间的个数
#include<iostream>
#include<map>
#include<cstring>
#define ll long long
using namespace std;

const int maxn = 1e5 + 5;
int n;
char s[maxn], *p;
int main() {
	ios::sync_with_stdio(false);
	map<int, int> mp;
	int test;
	cin >> test;
	while(test--){
		mp.clear();
		ll ans = 0, sum = 0;
		int len; p = s;
		cin >> n >> s;
		len = strlen(s);
		mp[0]++;
		while(p != s + len){
			sum += *p - '1';
			ans += mp[sum]++;
			p++;
		}
		cout << ans << endl;
	}
	return 0;
}