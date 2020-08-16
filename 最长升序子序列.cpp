/**
 *	给定数列,找出数列中最长的升序数列的长度
 *  如: 168523 -> 3(123)
 * 
 */
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
int n, nums[maxn], p[10];
int dp() {
	for(int i = 0; i < n; i++){
		int t = nums[i];
		for(int j = t; j >= 0; j--){
			p[t] = max(p[t], p[j] + 1);
		}
	}
	return *max_element(p, p + 10);
}
int main() {
	memset(p, 0, sizeof(p));
	cin >> n;
	for(int i = 0; i < n; i++){
		cin >> nums[i];
	}
	cout << dp() << endl;
}