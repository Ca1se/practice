#include<bits/stdc++.h>
#define PI 3.14
using namespace std;
class point {
    int x, y;
public:
    point(int = 0, int = 0);
    friend ostream& operator<< (ostream&, point&);
};

point::point(int x, int y): x(x), y(y) {}
ostream& operator<< (ostream& os, point& p) {
    os << '(' << p.x << ',' << p.y << ')';
    return os;
}

class circle {
    double radius;
    point center;
public:
    circle(double);
    circle(const circle&);
    double area();
    void move(point);
    friend ostream& operator<< (ostream&, circle&);
};

circle::circle(double r): radius(r) {
    center = point(0, 0);
}
circle::circle(const circle& p): radius(p.radius), center(p.center) {}
double circle::area() {
    return radius * radius * PI;
}
void circle::move(point p) {
    center = p;
}
ostream& operator<< (ostream& os, circle& cir) {
    os << "center point: " << cir.center << " radius: " << cir.radius;
    return os;
}

class cylinder: private circle {
    double height;
public:
    cylinder(double, int);
    double volume();
    void move(point);
    friend ostream& operator<< (ostream&, cylinder&);
};

cylinder::cylinder(double r, int h): circle(r), height(h) {}
double cylinder::volume() {
    return height * area();
}

void cylinder::move(point p) {
    circle::move(p);
}

ostream& operator<< (ostream& os, cylinder& cy) {
    circle t = cy;
    os << t << ' ';
    os << "cylinder height: " << cy.height;
    return os;
}

int main() {
    //---------------test class: point----------------------
    point p(1, 2);
    cout << p << endl;
    //---------------test class: circle---------------------
    circle cir(4);
    cout << "circle area: " << cir.area() << endl;
    cout << cir << endl;
    cir.move(p);
    cout << cir << endl;
    //---------------test class: cylinder-------------------
    cylinder cyl(4, 5);
    cout << "cylinder volume: " << cyl.volume() << endl;
    cout << cyl << endl;
    cyl.move(p);
    cout << cyl << endl;
}