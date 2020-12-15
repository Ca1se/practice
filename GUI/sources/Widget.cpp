//
// Created by ca1se on 2020/12/14.
//

#include "Widget.h"

Widget::Widget(QWidget *parent)
                :QWidget(parent)
                ,ui(new UI::MainWidget)
{
    ui->initUI(this);


}

Widget::~Widget() {
    delete ui;
}
