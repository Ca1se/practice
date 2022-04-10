///////////////////////////////////////////////////
// 程序名称：科赫雪花
// 编译环境：Mictosoft Visual Studio 2010, EasyX_20200315(beta)
// 作　　者：Lixiang
// 最后修改：2020-4-13
//
#include <graphics.h>//需要easyx库
#include <conio.h>
#include <math.h>

const double PI = 3.1415926536;
const double p = 0.3333333333;//三分之一
const double q = 0.6666666666;//三分之二

// 定义一个结构体 Point，存储点的坐标
struct Point
{
	double x;
	double y;
	POINT to_POINT();
};
POINT Point::to_POINT()
{
	double tx = this->x;
	double ty = this->y;
	POINT temp = { tx,ty };
	return temp;
}

// 直线的旋转（p1 是定点）
Point Rotate(Point p1, Point p2, double angle)
{
	Point r;
	r.x = p1.x + (p2.x - p1.x) * cos(angle) + (p2.y - p1.y) * sin(angle);
	r.y = p1.y + (p2.y - p1.y) * cos(angle) - (p2.x - p1.x) * sin(angle);
	return r;
}

void Draw(Point p1, Point p2)
{
	Point p3 = { q * p1.x + p * p2.x,q * p1.y + p * p2.y };
	Point p4 = { p * p1.x + q * p2.x,p * p1.y + q * p2.y };//找到三等分点
	Point p5 = Rotate(p3, p4, 60 * PI / 180);//找到等边三角形的顶点
	Point temp = Rotate(p2, p1, 60 * PI / 180);
	POINT full[] = { p1.to_POINT(),p3.to_POINT(),p5.to_POINT(),p4.to_POINT(),p2.to_POINT(),temp.to_POINT() };
	fillpolygon(full, 6);

	if (((p4.x - p3.x) * (p4.x - p3.x) + (p4.y - p3.y) * (p4.y - p3.y)) > 3)	// 三角形的边长 >3 时递归
	{
		double a = 60 * PI / 180;					// 60 度形式
		Point p = Rotate(p3, p4, a);
		line(p1.x, p1.y, p3.x, p3.y);
		line(p3.x, p3.y, p.x, p.y);
		line(p.x, p.y, p4.x, p4.y);
		line(p4.x, p4.y, p2.x, p2.y);
		Draw(p1, p3);
		Draw(p3, p);
		Draw(p, p4);
		Draw(p4, p2);
	}
}

// 主函数
int main()
{
	initgraph(886,886);				// 初始化窗口
	setbkcolor(0xfecaeb);				// 设置背景颜色
	cleardevice();

	Point p1 = { 200, 200 };
	Point p2 = { 686, 200 };
	Point p3 = { 443, 621 };
	Draw(p1, p2);
	Draw(p3, p1);
	Draw(p2, p3);

	_getch();
	closegraph();						// 关闭窗口
	return 0;
}