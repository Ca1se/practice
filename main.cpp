#include "widget.h"
#include "maintainmachine.h"
#include <QApplication>
#include <queue>

int main(int argc, char *argv[])
{
    MaintainMachine m(&Machine::Get());
    m.InitMachine("/home/ca1se/CLionProjects/CourseDesign/list/goods.json");

    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
