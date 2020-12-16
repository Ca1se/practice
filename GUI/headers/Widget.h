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
    Q_OBJECT

private slots:
    void ShowPurchaseUI();
    void ClosePurchaseUI();
    void Purchase();
    void ClosePayUI();
    void PayOnline();
    void PayOffline();
    void PBtnMinusClicked();
    void PBtnPlusClicked();

private:
    UI::MainWidget* ui;
    UI::SubWidget* sub_ui;
    QWidget* temp_ui;
    MaintainMachine* _pM;
    QVector<Goods> _vGInfo;
    QMap<QString, size_t> _mGtoPos;
    QString _chooseGoods;
    size_t _chooseNumber;

    void UpdateDisplay();
    void setIconText();
    void ShowPayUI(const char* pixaddr = nullptr);


public:
    Widget(QWidget* parent, MaintainMachine* manager);
    ~Widget();
};


#endif //UNTITLED2_WIDGET_H
