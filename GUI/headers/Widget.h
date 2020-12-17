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
    class PurchaseWidget;
    class PayWidget;
}

class Widget: public QWidget {
Q_OBJECT

private slots:
    void ShowPurchaseUI();
    void ClosePurchaseUI();
    void ShowPayUI();
    void ClosePayUI();
    void PayOnline();
    void PayOffline();
    void PBtnMinusClicked();
    void PBtnPlusClicked();
    void UpdateSpainBoxGoods(const QString& objectName);
    void UpdateSpainBoxCoins(int index);
    void SpainBoxGoodsChanged(int value);
    void SpainBoxCoinsChanged(int value);
    void CloseAddGoodsUI();
    void CloseAddCoinsUI();
    void AddGoods();
    void AddCoins();

private:
    UI::MainWidget* ui;
    UI::PurchaseWidget* buy_ui;
    UI::PayWidget* pay_ui;
    UI::MaintainWidget* mt_ui;
    MaintainMachine* _pM;
    QVector<Goods> _vGInfo;
    QMap<QString, size_t> _mGtoPos;
    QString _chooseGoods;
    size_t _chooseNumber;

    void UpdateDisplay();
    void setIconText();

public:
    Widget(QWidget* parent, MaintainMachine* manager);
    ~Widget();
};


#endif //UNTITLED2_WIDGET_H
