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
                ,sub_ui(new UI::SubWidget)
                ,_pM(manager)
                ,temp_ui(nullptr)
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

    //sub_ui
    sub_ui->initSubUI();
    connect(sub_ui->pBtnConfirm, SIGNAL(clicked()), this, SLOT(Purchase()));
    connect(sub_ui->pBtnCancel, SIGNAL(clicked()), this, SLOT(ClosePurchaseUI()));
    connect(sub_ui->pBtnMinus, SIGNAL(clicked()), this, SLOT(PBtnMinusClicked()));
    connect(sub_ui->pBtnPlus, SIGNAL(clicked()), this, SLOT(PBtnPlusClicked()));
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
    sub_ui->lbPictureGoods->setPixmap(QPixmap(t.sprintf("image/%s.png",\
                                                        pBtnClicked->objectName().toStdString().c_str())));
    this->setEnabled(false);
    sub_ui->show();
}

void Widget::ClosePurchaseUI() {
    _chooseNumber = 0;
    sub_ui->lbNumber->setText(trUtf8("0"));
    sub_ui->rBtnWechat->setChecked(true);
    sub_ui->pBtnMinus->setEnabled(false);
    sub_ui->pBtnPlus->setEnabled(true);
    _chooseGoods.clear();
    this->setEnabled(true);
    sub_ui->close();
}

void Widget::Purchase() {
    sub_ui->setEnabled(false);
    temp_ui = new QWidget();
    temp_ui->setGeometry(QRect(720, 400, 480, 480));
    temp_ui->setWindowFlag(Qt::FramelessWindowHint);
    if(sub_ui->rBtnAlipay->isChecked()){
        ShowPayUI("image/QRalipay.png");
    }else if(sub_ui->rBtnWechat->isChecked()){
        ShowPayUI("image/QRwechat.png");
    }else{
        ShowPayUI();
    }
    temp_ui->show();
}

void Widget::ShowPayUI(const char* pixaddr) {
    if(sub_ui->rBtnWechat->isChecked() || sub_ui->rBtnAlipay->isChecked()) {
        auto *lb = new QLabel(temp_ui);
        lb->setGeometry(QRect(84, 50, 312, 312));
        lb->setPixmap(QPixmap(trUtf8(pixaddr)));

        auto *tPBtnConfirm = new QPushButton(temp_ui);
        tPBtnConfirm->setGeometry(QRect(105, 400, 100, 35));
        tPBtnConfirm->setText(trUtf8("支付"));
        connect(tPBtnConfirm, SIGNAL(clicked()), this, SLOT(PayOnline()));

        auto *tPBtnCancel = new QPushButton(temp_ui);
        tPBtnCancel->setGeometry(QRect(275, 400, 100, 35));
        tPBtnCancel->setText(trUtf8("取消"));
        connect(tPBtnCancel, SIGNAL(clicked()), this, SLOT(ClosePayUI()));
    }else{
        auto *tLbNumber = new QLabel(temp_ui);
        tLbNumber->setGeometry(QRect(200, 200, 90, 30));
        tLbNumber->setFont(QFont(trUtf8("JetBrains Mono NL"), 20));
        tLbNumber->setText(trUtf8("请投币"));

        auto *tPBtnConfirm = new QPushButton(temp_ui);
        tPBtnConfirm->setGeometry(QRect(105, 400, 100, 35));
        tPBtnConfirm->setText(trUtf8("支付"));
        connect(tPBtnConfirm, SIGNAL(clicked()), this, SLOT(PayOffline()));

        auto *tPBtnCancel = new QPushButton(temp_ui);
        tPBtnCancel->setGeometry(QRect(275, 400, 100, 35));
        tPBtnCancel->setText(trUtf8("取消"));
        connect(tPBtnCancel, SIGNAL(clicked()), this, SLOT(ClosePayUI()));
    }
}

void Widget::ClosePayUI() {
    sub_ui->setEnabled(true);
    temp_ui->close();
    if(temp_ui){
        delete temp_ui;
        temp_ui = nullptr;
    }
}

void Widget::PayOnline() {
    std::string payway;
    if(sub_ui->rBtnWechat->isChecked()){
        payway = "Wechat-Pay";
    }else{
        payway = "Alipay";
    }
    Pay pay(&Machine::Get());
    pay.PaymentOnline(_chooseGoods.toStdString(), _chooseNumber, payway);
    UpdateDisplay();
    ClosePayUI();
    ClosePurchaseUI();
}

void Widget::PayOffline() {

    //这里无法做出真正的投币效果, 默认按整数成一元, 0.5成五角投币
    size_t pos = _mGtoPos[_chooseGoods];
    double cost = _vGInfo[pos].cost;
    std::list<std::pair<coin, size_t> > lCoins;
    lCoins.emplace_back(std::make_pair(coin::yuan_one, int(cost * 10) / 10));
    lCoins.emplace_back(std::make_pair(coin::dime_five, (int(cost * 10) % 10) /5));
    Pay pay(&Machine::Get());
    pay.PaymentOffline(_chooseGoods.toStdString(), _chooseNumber, lCoins);
    UpdateDisplay();
    ClosePayUI();
    ClosePurchaseUI();

}

void Widget::PBtnMinusClicked() {
    _chooseNumber--;
    sub_ui->pBtnMinus->setEnabled(_chooseNumber);
    sub_ui->pBtnPlus->setEnabled(true);
    sub_ui->pBtnConfirm->setEnabled(_chooseNumber);
    sub_ui->lbNumber->setText(QString::number(_chooseNumber));
}

void Widget::PBtnPlusClicked() {
    size_t remain = _pM->GetGoodsRemain(_chooseGoods.toStdString());
    _chooseNumber++;
    if(remain == _chooseNumber){
        sub_ui->pBtnPlus->setEnabled(false);
    }
    sub_ui->pBtnMinus->setEnabled(true);
    sub_ui->pBtnConfirm->setEnabled(_chooseNumber);
    sub_ui->lbNumber->setText(QString::number(_chooseNumber));
}