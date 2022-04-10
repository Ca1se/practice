#include<iostream>
#include<thread>

void PassByReference(std::string& data) {
    //do something
}

void PassByValue(const std::string s, int i) {
    //do something
}

void foo(int param) {
    char buf[1024];
    sprintf(buf, "%d", param);
    //std::thread th(foo1, buf, param); 新线程开始时, buf与param将被拷贝到新线程的内存空间中,
    //但buf为一个指针类型, 以下使用了th.detach(), 主线程不会等待新线程结束。则buf指向的内存空间可能在
    //其中的内容被转换成一个std::string类型前就被释放掉了, 导致未定义行为
    std::thread th(PassByValue, std::string(buf), param);
    th.detach();
}

void foo(std::string& rs) {
    //如果传入的函数期望函数参数以引用方式传递, 使用std::ref()
    std::thread th(PassByReference, std::ref(rs));
    th.join();
}


int main() {
    foo(3);
    return 0;
}