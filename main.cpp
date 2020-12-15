#include "Widget.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    MaintainMachine m(&Machine::Get());
    m.InitMachine("/home/ca1se/CLionProjects/CourseDesign/list/goods.json");

    QApplication a(argc, argv);
    Widget w(nullptr, m);
    w.show();
    return a.exec();
}
