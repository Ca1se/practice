#include "Widget.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MaintainMachine m(&Machine::Get());
    QString t;
    m.InitMachine(t.sprintf("%s/list/goods.json",\
                            QApplication::applicationDirPath().toStdString().c_str()).toStdString().c_str());

    Widget w(nullptr, &m);
    w.show();
    return app.exec();
}
