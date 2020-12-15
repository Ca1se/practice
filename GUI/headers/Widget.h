//
// Created by ca1se on 2020/12/14.
//

#ifndef UNTITLED2_WIDGET_H
#define UNTITLED2_WIDGET_H

#include "UIset.h"
#include "maintainmachine.h"
#include <QVector>

namespace UI {
    class MainWidget;
    class SubWidget;
}

class Widget: public QWidget {
public:
    Widget(QWidget* parent, MaintainMachine* manager);
    ~Widget();


private:
    UI::MainWidget* ui;
    MaintainMachine* _pM;
    QVector<Goods> _vGInfo;
    QMap<QString, size_t> _mGtoPos;

    void UpdateDisplay(QPushButton* pBtn);
    void setIconText();
};


#endif //UNTITLED2_WIDGET_H
