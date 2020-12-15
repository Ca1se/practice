//
// Created by ca1se on 2020/12/14.
//

#ifndef UNTITLED2_WIDGET_H
#define UNTITLED2_WIDGET_H

#include "UIset.h"

namespace UI {  class MainWidget; }

class Widget: public QWidget {
public:
    Widget(QWidget* parent = nullptr);
    ~Widget();


private:
    UI::MainWidget* ui;

    void setPushButtonIcon();
};


#endif //UNTITLED2_WIDGET_H
