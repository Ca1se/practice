//
// Created by ca1se on 2020/12/14.
//

#include "Widget.h"
#include "explain.h"
#include <cstring>

Widget::Widget(QWidget *parent, MaintainMachine* manager)
                :QWidget(parent)
                ,ui(new UI::MainWidget)
                ,_pM(manager)
{
    ui->initUI(this);

    explain* ex = new explain("/home/ca1se/CLionProjects/CourseDesign/list/goods.json", "name", "cost");
    for(size_t i = 0; i < 9; i++){
        auto it = ex->ExplainInTurn_pair();
        _vGInfo.push_back(Goods(std::move(it.first), strtod(it.second.c_str(), nullptr)));
    }

    setIconText();
}

Widget::~Widget() {
    delete ui;
}

void Widget::setIconText() {
    for(size_t i = 0; i < _vGInfo.size(); i++){
        //ButtonIcon
        char buf[3] = {0};
        sprintf(buf, "%zu", i);

        auto& goods = _vGInfo[i];

        QString t;

        auto pBtn = findChild<QPushButton*>(trUtf8(buf));
        pBtn->setObjectName(trUtf8(goods.name.c_str()));
        pBtn->setIcon(QIcon(t.sprintf("%s%s", goods.name.c_str(), ".png")));
        pBtn->setIconSize(QSize(128, 128));
        _mGtoPos.insert(pBtn->objectName(), i);

        //LabelText
        auto pLb = findChild<QLabel*>(trUtf8(buf));
        pLb->setText(t.sprintf("%s 价格:%f 剩余:%d", goods.name.c_str(), goods.cost, 0));
    }
}

void Widget::UpdateDisplay(QPushButton* pBtn) {
    size_t pos = _mGtoPos[pBtn->objectName()];
    size_t n = _pM->GetGoodsRemain(pBtn->objectName().toStdString());

    auto& goods = _vGInfo[pos];
    auto plb = findChild<QLabel*>(pBtn->objectName());
    QString t;
    plb->setText(t.sprintf("%s 价格:%f 剩余:%zu", goods.name.c_str(), goods.cost, n));

    pBtn->setEnabled(n);
}
