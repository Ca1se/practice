#include<bits/stdc++.h>
class Widget;
class Bitmap {
public:
    Bitmap(int x = 0, int y = 0, int v = 0): x(x), y(y), v(v) {}
    friend std::ostream& operator<< (std::ostream&, const Widget);
private:
    int x, y, v;

};
class Widget {
public:
    Widget(Bitmap* p): pb(p) {}
    Widget(const Widget&);
    Widget& operator= (const Widget& rhs);
    friend std::ostream& operator<< (std::ostream&, const Widget);
private:
    void swap(const Widget&);
    Bitmap* pb;

};
Widget::Widget(const Widget& rhs) {
    pb = rhs.pb;
}
void Widget::swap(const Widget& w) {
    //...
}
/*
Widget& Widget::operator= (const Widget& rhs) {
    Bitmap* t = pb;
    pb = new Bitmap(*rhs.pb);
    delete t;
    return *this;
}*/
Widget& Widget::operator= (const Widget& rhs) {
    Widget t(rhs);
    swap(t);
    return *this;
}
std::ostream& operator<< (std::ostream& os, const Widget rhs) {
    os << rhs.pb->x << ' ' << rhs.pb->y << ' ' << rhs.pb->v;
    return os;
}
int main() {
    Widget t = Widget(new Bitmap(1, 2, 1));
    Widget* tp = &t;
    t = *tp;
    std::cout << *tp << std::endl;
    return 0;
}