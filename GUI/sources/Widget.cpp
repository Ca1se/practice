//
// Created by ca1se on 2020/12/14.
//

#include "Widget.h"
#include "explain.h"
#include "dealmaintain.h"
#include <cstring>
#include <iostream>

Widget::Widget(QWidget *parent, MaintainMachine* manager)
        :QWidget(parent)
        ,ui(new UI::MainWidget)
        ,buy_ui(new UI::PurchaseWidget)
        ,pay_ui(new UI::PayWidget)
        ,_pM(manager)
        ,_chooseNumber(0)
{
    ui->initUI(this);

    //init Goods info
    QString t;
    auto* ex = new explain(t.sprintf("%s/list/goods.json",\
                            QApplication::applicationDirPath().toStdString().c_str()).toStdString().c_str(), "name", "cost");
    for(size_t i = 0; i < 9; i++){
        auto it = ex->ExplainInTurn_pair();
        _vGInfo.push_back(Goods(std::move(it.first), strtod(it.second.c_str(), nullptr)));
    }
    delete ex;

    setIconText();

    auto pBtnList = ui->layoutWidget->findChildren<QPushButton*>();
    for(auto pBtn : pBtnList){
        connect(pBtn, SIGNAL(clicked()), this, SLOT(ShowPurchaseUI()));
    }

    //buy_ui
    buy_ui->initPurchaseUI();
    connect(buy_ui->pBtnConfirm, SIGNAL(clicked()), this, SLOT(ShowPayUI()));
    connect(buy_ui->pBtnCancel, SIGNAL(clicked()), this, SLOT(ClosePurchaseUI()));
    connect(buy_ui->pBtnMinus, SIGNAL(clicked()), this, SLOT(PBtnMinusClicked()));
    connect(buy_ui->pBtnPlus, SIGNAL(clicked()), this, SLOT(PBtnPlusClicked()));

    //pay_ui
    pay_ui->InitPayUI();
    connect(pay_ui->pBtnCancel, SIGNAL(clicked()), pay_ui, SLOT(close()));
}

Widget::~Widget() {
    delete ui;
}

void Widget::setIconText() {
    auto pBtnList = ui->layoutWidget->findChildren<QPushButton*>();
    auto pLbList = ui->layoutWidget->findChildren<QLabel*>();
    QString t;
    for(size_t i = 0; i < _vGInfo.size(); i++){
        auto* pBtn = pBtnList.at(i);
        auto* pLb = pLbList.at(i);
        auto& goods = _vGInfo[i];
        size_t remain = _pM->GetGoodsRemain(goods.name);

        //ButtonIcon
        pBtn->setObjectName(trUtf8(goods.name.c_str()));
        pBtn->setIcon(QIcon(t.sprintf("image/%s.png", goods.name.c_str())));
        pBtn->setIconSize(QSize(128, 128));
        pBtn->setEnabled(remain);
        _mGtoPos.insert(pBtn->objectName(), i);

        //LabelText
        pLb->setObjectName(pBtn->objectName());
        pLb->setText(t.sprintf("%s 价格:%.1f 剩余:%zu", goods.name.c_str(), goods.cost, remain));
    }
}

void Widget::UpdateDisplay() {
    auto* pBtn = ui->layoutWidget->findChild<QPushButton*>(_chooseGoods);

    size_t pos = _mGtoPos[pBtn->objectName()];
    size_t n = _pM->GetGoodsRemain(pBtn->objectName().toStdString());

    auto& goods = _vGInfo[pos];
    auto* plb = findChild<QLabel*>(pBtn->objectName());
    QString t;
    plb->setText(t.sprintf("%s 价格:%.1f 剩余:%zu", goods.name.c_str(), goods.cost, n));

    pBtn->setEnabled(n);
}

void Widget::ShowPurchaseUI() {
    auto* pBtnClicked = qobject_cast<QPushButton*>(sender());

    _chooseGoods = pBtnClicked->objectName();
    QString t;
    buy_ui->lbPictureGoods->setPixmap(QPixmap(t.sprintf("image/%s.png",\
                                                        pBtnClicked->objectName().toStdString().c_str())));
    this->setEnabled(false);
    buy_ui->show();
}

void Widget::ClosePurchaseUI() {
    _chooseNumber = 0;
    buy_ui->lbNumber->setText(trUtf8("0"));
    buy_ui->rBtnWechat->setChecked(true);
    buy_ui->pBtnMinus->setEnabled(false);
    buy_ui->pBtnPlus->setEnabled(true);
    buy_ui->pBtnConfirm->setEnabled(false);
    _chooseGoods.clear();
    this->setEnabled(true);
    buy_ui->close();
}

void Widget::ShowPayUI() {
    if(buy_ui->rBtnWechat->isChecked() || buy_ui->rBtnAlipay->isChecked()) {
        pay_ui->lbDisplay->setGeometry(QRect(84, 50, 312, 312));
        if(buy_ui->rBtnWechat->isChecked()) {
            pay_ui->lbDisplay->setPixmap(QPixmap(trUtf8("image/QRwechat.png")));
        }else{
            pay_ui->lbDisplay->setPixmap(QPixmap(trUtf8("image/QRalipay.png")));
        }
        connect(pay_ui->pBtnConfirm, SIGNAL(clicked()), this, SLOT(PayOnline()));
    }else{
        QFont f;
        f.setPointSize(20);
        pay_ui->lbDisplay->setGeometry(QRect(200, 200, 90, 30));
        pay_ui->lbDisplay->setFont(f);
        pay_ui->lbDisplay->setText(trUtf8("请投币"));

        connect(pay_ui->pBtnConfirm, SIGNAL(clicked()), this, SLOT(PayOffline()));
    }
    pay_ui->show();
}

void Widget::ClosePayUI() {
    buy_ui->setEnabled(true);
    pay_ui->close();
    pay_ui->pBtnConfirm->disconnect();
}

void Widget::PayOnline() {
    std::string payway;
    if(buy_ui->rBtnWechat->isChecked()){
        payway = "Wechat-Pay";
    }else{
        payway = "Alipay";
    }
    Pay pay(&Machine::Get());
    pay.PaymentOnline(_chooseGoods.toStdString(), _chooseNumber, payway);
    UpdateDisplay();
    ClosePayUI();
    ClosePurchaseUI();
    pay_ui->lsSubText->setText(trUtf8("支付成功!请及时取走您的货物"));
    pay_ui->lsPayPrompt->show();
}

void Widget::PayOffline() {

    //这里无法做出真正的投币效果, 默认按整数成一元, 0.5成五角投币
    size_t pos = _mGtoPos[_chooseGoods];
    double cost = _vGInfo[pos].cost;
    std::list<std::pair<coin, size_t> > lCoins;
    lCoins.emplace_back(std::make_pair(coin::yuan_one, int(_chooseNumber * cost * 10) / 10));
    lCoins.emplace_back(std::make_pair(coin::dime_five, (int(_chooseNumber * cost * 10) % 10) /5));
    Pay pay(&Machine::Get());
    pay.PaymentOffline(_chooseGoods.toStdString(), _chooseNumber, lCoins);
    UpdateDisplay();
    ClosePayUI();
    ClosePurchaseUI();
    pay_ui->lsSubText->setText(trUtf8("支付成功!请及时取走您的货物"));
    pay_ui->lsPayPrompt->show();
}

void Widget::PBtnMinusClicked() {
    _chooseNumber--;
    buy_ui->pBtnMinus->setEnabled(_chooseNumber);
    buy_ui->pBtnPlus->setEnabled(true);
    buy_ui->pBtnConfirm->setEnabled(_chooseNumber);
    buy_ui->lbNumber->setText(QString::number(_chooseNumber));
}

void Widget::PBtnPlusClicked() {
    size_t remain = _pM->GetGoodsRemain(_chooseGoods.toStdString());
    _chooseNumber++;
    if(remain == _chooseNumber){
        buy_ui->pBtnPlus->setEnabled(false);
    }
    buy_ui->pBtnMinus->setEnabled(true);
    buy_ui->pBtnConfirm->setEnabled(_chooseNumber);
    buy_ui->lbNumber->setText(QString::number(_chooseNumber));
}