#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    cv::Mat img(700, 700, CV_8UC3, cv::Scalar(0));
    std::cout << img.size << std::endl;
    return 0;
}
