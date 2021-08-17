#include <bits/stdc++.h>
#include <eigen3/Eigen/Eigen>
using namespace std;
int main() {
	Eigen::Vector3f a{1, 3, 4};
	auto [r, b, g] = a;
	cout << r << b << g << endl;
	return 0;
}
