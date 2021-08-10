#include <iostream>
#include <eigen3/Eigen/Eigen>
int main() {
	Eigen::Vector3f m1{1, 2, 0}, m2{3, 4, 0};
	std::cout << (m1 * m2).z() << std::endl;
	return 0;
}
