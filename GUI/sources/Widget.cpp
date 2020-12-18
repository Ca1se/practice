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
        ,mt_ui(new UI::MaintainWidget)
        ,_pM(manager)
        ,_chooseNumber(0)
{
    //init Goods info
    QString t;
    auto* ex = new explain(t.sprintf("%s/list/goods.json",\
                            QApplication::applicationDirPath().toStdString().c_str()).toStdString(), "name", "cost");
    for(size_t i = 0; i < 9; i++){
        auto it = ex->ExplainInTurn_pair();
        _vGInfo.push_back(Goods(std::move(it.first), strtod(it.second.c_str(), nullptr)));
    }
    delete ex;

    //ui
    ui->initUI(this);
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

    //maintain
    mt_ui->InitMaintainUI();

    QStringList goodsNameList;
    goodsNameList << trUtf8("选择货物");
    for(auto* itBtn: pBtnList){
        goodsNameList << itBtn->objectName();
    }
    mt_ui->cbBoxGoods->addItems(goodsNameList);

    connect(ui->pBtnAdminC, SIGNAL(clicked()), mt_ui->addCoins_widget, SLOT(show()));
    connect(ui->pBtnAdminG, SIGNAL(clicked()), mt_ui->addGoods_widget, SLOT(show()));
    connect(ui->pBtnAdminC, SIGNAL(clicked(bool)), this, SLOT(setEnabled(bool)));
    connect(ui->pBtnAdminG, SIGNAL(clicked(bool)), this, SLOT(setEnabled(bool)));
    connect(mt_ui->cbBoxGoods, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(UpdateSpainBoxGoods(const QString &)));
    connect(mt_ui->cbBoxCoins, SIGNAL(currentIndexChanged(int)), this, SLOT(UpdateSpainBoxCoins(int)));
    connect(mt_ui->spBoxNumberGoods, SIGNAL(valueChanged(int)), this, SLOT(SpainBoxGoodsChanged(int)));
    connect(mt_ui->spBoxNumberCoins, SIGNAL(valueChanged(int)), this, SLOT(SpainBoxCoinsChanged(int)));
    connect(mt_ui->pBtnCancelGoods, SIGNAL(clicked()), this, SLOT(CloseAddGoodsUI()));
    connect(mt_ui->pBtnCancelCoins, SIGNAL(clicked()), this, SLOT(CloseAddCoinsUI()));
    connect(mt_ui->pBtnConfirmGoods, SIGNAL(clicked()), this, SLOT(AddGoods()));
    connect(mt_ui->pBtnConfirmCoins, SIGNAL(clicked()), this, SLOT(AddCoins()));
}

Widget::~Widget() {
    delete ui;
    delete buy_ui;
    delete pay_ui;
    delete mt_ui;
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

void Widget::UpdateSpainBoxGoods(const QString &objectName) {
    size_t index = mt_ui->cbBoxGoods->currentIndex();
    if(index) {
        size_t n = _pM->GetGoodsRemain(objectName.toStdString());
        mt_ui->spBoxNumberGoods->setMaximum(20 - n);
    }
    mt_ui->spBoxNumberGoods->setValue(0);
    mt_ui->pBtnConfirmGoods->setEnabled(false);
}

void Widget::UpdateSpainBoxCoins(int index) {
    mt_ui->spBoxNumberCoins->setValue(0);
    mt_ui->pBtnConfirmCoins->setEnabled(false);
}

void Widget::SpainBoxGoodsChanged(int value) {
    mt_ui->pBtnConfirmGoods->setEnabled(value && mt_ui->cbBoxGoods->currentIndex());
}

void Widget::SpainBoxCoinsChanged(int value) {
    mt_ui->pBtnConfirmCoins->setEnabled(value && mt_ui->cbBoxCoins->currentIndex());
}

void Widget::CloseAddGoodsUI() {
    _chooseGoods.clear();
    mt_ui->spBoxNumberGoods->setValue(0);
    mt_ui->pBtnConfirmGoods->setEnabled(false);
    mt_ui->cbBoxGoods->setCurrentIndex(0);
    mt_ui->addGoods_widget->close();
    this->setEnabled(true);
}

void Widget::CloseAddCoinsUI() {
    mt_ui->spBoxNumberCoins->setValue(0);
    mt_ui->pBtnConfirmCoins->setEnabled(false);
    mt_ui->cbBoxCoins->setCurrentIndex(0);
    mt_ui->addCoins_widget->close();
    this->setEnabled(true);
}

void Widget::AddGoods() {
    QString goodsName = mt_ui->cbBoxGoods->currentText();
    size_t n = mt_ui->spBoxNumberGoods->value();
    ContainUpdate c(&Machine::Get());
    c.ReplenishGoods(goodsName.toStdString(), n);
    _chooseGoods = goodsName;
    UpdateDisplay();
    CloseAddGoodsUI();
    mt_ui->lsSubText->setText(trUtf8("补货成功!"));
    mt_ui->lsMTPrompt->show();
}

void Widget::AddCoins() {
    QString coinName = mt_ui->cbBoxCoins->currentText();
    size_t n = mt_ui->spBoxNumberCoins->value();
    ContainUpdate c(&Machine::Get());
    if(coinName == trUtf8("1元")){
        c.ReplenishCoin(coin::yuan_one, n);
    }else{
        c.ReplenishCoin(coin::dime_five, n);
    }
    CloseAddCoinsUI();
    mt_ui->lsSubText->setText(trUtf8("补硬币成功!"));
    mt_ui->lsMTPrompt->show();
}