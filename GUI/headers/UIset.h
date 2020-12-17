//
// Created by ca1se on 2020/12/14.
//

#ifndef UNTITLED2_UI_WIDGET_H
#define UNTITLED2_UI_WIDGET_H

#include <QtWidgets/QPushButton>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSplashScreen>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QComboBox>
#include <QApplication>

//  Main Widget description class
//  Realize the part of selecting goods
class surf_widget {
public:
    QWidget* layoutWidget;
    QGridLayout* mainGridLyt;
    QPushButton* pBtnSelect0;
    QPushButton* pBtnSelect1;
    QPushButton* pBtnSelect2;
    QPushButton* pBtnSelect3;
    QPushButton* pBtnSelect4;
    QPushButton* pBtnSelect5;
    QPushButton* pBtnSelect6;
    QPushButton* pBtnSelect7;
    QPushButton* pBtnSelect8;
    QPushButton* pBtnAdminG;
    QPushButton* pBtnAdminC;
    QLabel* lGoods0;
    QLabel* lGoods1;
    QLabel* lGoods2;
    QLabel* lGoods3;
    QLabel* lGoods4;
    QLabel* lGoods5;
    QLabel* lGoods6;
    QLabel* lGoods7;
    QLabel* lGoods8;


    void initUI(QWidget* widget) {
        widget->setMinimumSize(720, 960);
        widget->setMaximumSize(720, 960);
        widget->setWindowTitle(QApplication::trUtf8("自动售货机"));
        widget->setStyleSheet("background-color: rgba(255, 227, 132, 1)");


        layoutWidget = new QWidget(widget);
        layoutWidget->setGeometry(QRect(90, 180, 540, 600));

        mainGridLyt = new QGridLayout(layoutWidget);
        mainGridLyt->setContentsMargins(20, 20, 20, 20);
        mainGridLyt->setHorizontalSpacing(10);
        mainGridLyt->setVerticalSpacing(10);

        lGoods0 = new QLabel(layoutWidget);
        setUpLabel(lGoods0, "0");
        mainGridLyt->addWidget(lGoods0, 1, 0, 1, 1);
        lGoods1 = new QLabel(layoutWidget);
        setUpLabel(lGoods1, "1");
        mainGridLyt->addWidget(lGoods1, 1, 1, 1, 1);
        lGoods2 = new QLabel(layoutWidget);
        setUpLabel(lGoods2, "2");
        mainGridLyt->addWidget(lGoods2, 1, 2, 1, 1);
        lGoods3 = new QLabel(layoutWidget);
        setUpLabel(lGoods3, "3");
        mainGridLyt->addWidget(lGoods3, 3, 0, 1, 1);
        lGoods4 = new QLabel(layoutWidget);
        setUpLabel(lGoods4, "4");
        mainGridLyt->addWidget(lGoods4, 3, 1, 1, 1);
        lGoods5 = new QLabel(layoutWidget);
        setUpLabel(lGoods5, "5");
        mainGridLyt->addWidget(lGoods5, 3, 2, 1, 1);
        lGoods6 = new QLabel(layoutWidget);
        setUpLabel(lGoods6, "6");
        mainGridLyt->addWidget(lGoods6, 5, 0, 1, 1);
        lGoods7 = new QLabel(layoutWidget);
        setUpLabel(lGoods7, "7");
        mainGridLyt->addWidget(lGoods7, 5, 1, 1, 1);
        lGoods8 = new QLabel(layoutWidget);
        setUpLabel(lGoods8, "8");
        mainGridLyt->addWidget(lGoods8, 5, 2, 1, 1);

        pBtnAdminG = new QPushButton(widget);
        pBtnAdminG->setGeometry(QRect(30, 900, 85, 35));
        pBtnAdminG->setText(QApplication::trUtf8("补货"));

        pBtnAdminC = new QPushButton(widget);
        pBtnAdminC->setGeometry(QRect(30, 840, 85, 35));
        pBtnAdminC->setText(QApplication::trUtf8("补硬币"));

        pBtnSelect0 = new QPushButton(widget);
        setUpButton(pBtnSelect0, "background-color: rgba(40, 20, 10, 1)", "0");
        mainGridLyt->addWidget(pBtnSelect0, 0, 0, 1, 1);
        pBtnSelect1 = new QPushButton(widget);
        setUpButton(pBtnSelect1, "background-color: rgba(80, 20, 10, 1)", "1");
        mainGridLyt->addWidget(pBtnSelect1, 0, 1, 1, 1);
        pBtnSelect2 = new QPushButton(widget);
        setUpButton(pBtnSelect2, "background-color: rgba(40, 90, 10, 1)", "2");
        mainGridLyt->addWidget(pBtnSelect2, 0, 2, 1, 1);
        pBtnSelect3 = new QPushButton(widget);
        setUpButton(pBtnSelect3, "background-color: rgba(20, 50, 10, 1)", "3");
        mainGridLyt->addWidget(pBtnSelect3, 2, 0, 1, 1);
        pBtnSelect4 = new QPushButton(widget);
        setUpButton(pBtnSelect4, "background-color: rgba(70, 80, 10, 1)", "4");
        mainGridLyt->addWidget(pBtnSelect4, 2, 1, 1, 1);
        pBtnSelect5 = new QPushButton(widget);
        setUpButton(pBtnSelect5, "background-color: rgba(40, 50, 30, 1)", "5");
        mainGridLyt->addWidget(pBtnSelect5, 2, 2, 1, 1);
        pBtnSelect6 = new QPushButton(widget);
        setUpButton(pBtnSelect6, "background-color: rgba(70, 90, 10, 1)", "6");
        mainGridLyt->addWidget(pBtnSelect6, 4, 0, 1, 1);
        pBtnSelect7 = new QPushButton(widget);
        setUpButton(pBtnSelect7, "background-color: rgba(40, 60, 10, 1)", "7");
        mainGridLyt->addWidget(pBtnSelect7, 4, 1, 1, 1);
        pBtnSelect8 = new QPushButton(widget);
        setUpButton(pBtnSelect8, "background-color: rgba(40, 70, 70, 1)", "8");
        mainGridLyt->addWidget(pBtnSelect8, 4, 2, 1, 1);

    }

private:

    static void setUpButton(QPushButton* pBtn, const char* styleSheet, const char* pos) {
        pBtn->setObjectName(QApplication::trUtf8(pos));
        pBtn->setMaximumSize(140, 140);
        pBtn->setMinimumSize(140, 140);
        pBtn->setStyleSheet(styleSheet);
    }

    static void setUpLabel(QLabel* lb, const char* pos) {
        lb->setObjectName(QApplication::trUtf8(pos));
        lb->setMinimumSize(140, 30);
        lb->setMaximumSize(140, 30);
        lb->setWordWrap(true);
    }
};

class CustomSplash: public QSplashScreen {
    void mousePressEvent(QMouseEvent*) override {}//cancel base class's "press to close the SplashScreen" action
};

// Purchase Widget class description class
// Realize the part of purchasing goods
class purchase_widget: public CustomSplash {
public:
    QWidget* layout;
    QHBoxLayout* hBoxLyt;
    QLabel* lbPictureGoods;
    QLabel* lbNumber;
    QLabel* lbPictureWechat;
    QLabel* lbPictureAlipay;
    QLabel* lbTextCoin;
    QPushButton* pBtnPlus;
    QPushButton* pBtnMinus;
    QPushButton* pBtnConfirm;
    QPushButton* pBtnCancel;
    QRadioButton* rBtnWechat;
    QRadioButton* rBtnAlipay;
    QRadioButton* rBtnCoin;

    void initPurchaseUI() {
        this->setGeometry(QRect(720, 400, 480, 540));
        this->setStyleSheet("background-color: rgba(255, 227, 132, 1)");
        lbPictureGoods = new QLabel(this);
        lbPictureWechat = new QLabel(this);
        lbPictureAlipay = new QLabel(this);
        lbTextCoin = new QLabel(this);
        lbNumber = new QLabel(this);
        pBtnMinus = new QPushButton(this);
        pBtnPlus = new QPushButton(this);
        pBtnConfirm = new QPushButton(this);
        pBtnCancel = new QPushButton(this);
        rBtnAlipay = new QRadioButton(this);
        rBtnWechat = new QRadioButton(this);
        rBtnCoin = new QRadioButton(this);
        layout = new QWidget(this);
        hBoxLyt = new QHBoxLayout(layout);

        lbNumber->setGeometry(QRect(205, 250, 70, 50));
        lbPictureGoods->setGeometry(QRect(170, 50, 140, 140));
        pBtnPlus->setGeometry(QRect(275, 250, 70, 50));
        pBtnMinus->setGeometry(QRect(135, 250, 70, 50));
        pBtnConfirm->setGeometry(QRect(105, 450, 100, 35));
        pBtnCancel->setGeometry(QRect(275, 450, 100, 35));
        layout->setGeometry((QRect(130, 350, 280, 35)));

        lbPictureAlipay->setPixmap(QPixmap("image/alipay.png"));
        lbPictureWechat->setPixmap(QPixmap("image/wechat.png"));
        lbTextCoin->setText(trUtf8("硬币支付"));
        rBtnAlipay->setMaximumSize(20, 20);
        rBtnWechat->setMaximumSize(20, 20);
        rBtnCoin->setMaximumSize(20, 20);
        lbPictureAlipay->setMaximumSize(40, 40);
        lbPictureWechat->setMaximumSize(40, 40);
        lbPictureAlipay->setMinimumSize(40, 40);
        lbPictureWechat->setMinimumSize(40, 40);

        rBtnWechat->setChecked(true);
        hBoxLyt->setContentsMargins(QMargins(0, 0, 0, 0));
        hBoxLyt->addWidget(rBtnWechat, 0);
        hBoxLyt->addWidget(lbPictureWechat, 1);
        hBoxLyt->addWidget(rBtnAlipay, 2);
        hBoxLyt->addWidget(lbPictureAlipay, 3);
        hBoxLyt->addWidget(rBtnCoin, 4);
        hBoxLyt->addWidget(lbTextCoin, 5);

        QFont tFont;
        tFont.setPointSize(30);
        pBtnPlus->setFont(tFont);
        pBtnPlus->setText(trUtf8("+"));
        pBtnMinus->setFont(tFont);
        pBtnMinus->setText(trUtf8("-"));
        pBtnMinus->setEnabled(false);
        lbNumber->setText(trUtf8("0"));
        lbNumber->setAlignment(Qt::AlignCenter);
        pBtnConfirm->setText(trUtf8("确定"));
        pBtnCancel->setText(trUtf8("取消"));
        pBtnConfirm->setEnabled(false);

    }
};

//pay UI
class pay_widget: public CustomSplash {
public:
    QPushButton* pBtnConfirm;
    QPushButton* pBtnCancel;
    QSplashScreen* lsPayPrompt;
    QLabel* lbDisplay;
    QLabel* lsSubText;

    void InitPayUI() {
        this->setGeometry(QRect(720, 400, 480, 480));
        pBtnConfirm = new QPushButton(this);
        pBtnConfirm->setGeometry(QRect(105, 400, 100, 35));
        pBtnConfirm->setText(trUtf8("支付"));

        pBtnCancel = new QPushButton(this);
        pBtnCancel->setGeometry(QRect(275, 400, 100, 35));
        pBtnCancel->setText(trUtf8("取消"));

        lbDisplay = new QLabel(this);

        QFont f;
        f.setPointSize(15);
        lsPayPrompt = new QSplashScreen();
        lsPayPrompt->setGeometry(QRect(720, 400, 360, 240));
        lsSubText = new QLabel(lsPayPrompt);
        lsSubText->setGeometry(QRect(70, 90, 200, 60));
        lsSubText->setObjectName(trUtf8("promptText"));
        lsSubText->setAlignment(Qt::AlignCenter);
        lsSubText->setWordWrap(true);
        lsSubText->setFont(f);
    }
};

//Maintain UI
class maintain_widget {
public:
    CustomSplash* addGoods_widget;
    QLabel* lbTextGoods;
    QLabel* lbTextGoodsNumber;
    QComboBox* cbBoxGoods;
    QSpinBox* spBoxNumberGoods;
    QPushButton* pBtnConfirmGoods;
    QPushButton* pBtnCancelGoods;

    CustomSplash* addCoins_widget;
    QLabel* lbTextCoins;
    QLabel* lbTextCoinsNumber;
    QComboBox* cbBoxCoins;
    QSpinBox* spBoxNumberCoins;
    QPushButton* pBtnConfirmCoins;
    QPushButton* pBtnCancelCoins;

    QSplashScreen* lsMTPrompt;
    QLabel* lsSubText;

    void InitMaintainUI() {
        //Add Goods
        addGoods_widget = new CustomSplash();
        addGoods_widget->setGeometry(QRect(720, 400, 300, 150));
        lbTextGoods = new QLabel(addGoods_widget);
        lbTextGoods->setGeometry(QRect(50, 20, 60, 20));
        lbTextGoods->setText(QApplication::trUtf8("选择货物:"));
        cbBoxGoods = new QComboBox(addGoods_widget);
        cbBoxGoods->setGeometry(QRect(140, 20, 110, 20));
        lbTextGoodsNumber = new QLabel(addGoods_widget);
        lbTextGoodsNumber->setGeometry(QRect(50, 60, 60, 20));
        lbTextGoodsNumber->setText(QApplication::trUtf8("补货个数"));
        spBoxNumberGoods = new QSpinBox(addGoods_widget);
        spBoxNumberGoods->setGeometry(QRect(140, 60, 110, 20));
        pBtnConfirmGoods = new QPushButton(addGoods_widget);
        pBtnConfirmGoods->setGeometry(QRect(60, 100, 70, 25));
        pBtnConfirmGoods->setText(QApplication::trUtf8("确定"));
        pBtnConfirmGoods->setEnabled(false);
        pBtnCancelGoods = new QPushButton(addGoods_widget);
        pBtnCancelGoods->setGeometry(QRect(170, 100, 70, 25));
        pBtnCancelGoods->setText(QApplication::trUtf8("取消"));

        //Add Coins
        addCoins_widget = new CustomSplash();
        addCoins_widget->setGeometry(QRect(720, 400, 300, 150));
        lbTextCoins = new QLabel(addCoins_widget);
        lbTextCoins->setGeometry(QRect(50, 20, 60, 20));
        lbTextCoins->setText(QApplication::trUtf8("选择硬币:"));
        cbBoxCoins = new QComboBox(addCoins_widget);
        cbBoxCoins->setGeometry(QRect(140, 20, 110, 20));
        QStringList coinsNameList;
        coinsNameList << QApplication::trUtf8("选择硬币") << QApplication::trUtf8("1元") << QApplication::trUtf8("5角");
        cbBoxCoins->addItems(coinsNameList);
        lbTextCoinsNumber = new QLabel(addCoins_widget);
        lbTextCoinsNumber->setGeometry(QRect(50, 60, 60, 20));
        lbTextCoinsNumber->setText(QApplication::trUtf8("补充个数:"));
        spBoxNumberCoins = new QSpinBox(addCoins_widget);
        spBoxNumberCoins->setGeometry(QRect(140, 60, 110, 20));
        pBtnConfirmCoins = new QPushButton(addCoins_widget);
        pBtnConfirmCoins->setGeometry(QRect(60, 100, 70, 25));
        pBtnConfirmCoins->setText(QApplication::trUtf8("确定"));
        pBtnConfirmCoins->setEnabled(false);
        pBtnCancelCoins = new QPushButton(addCoins_widget);
        pBtnCancelCoins->setGeometry(QRect(170, 100, 70, 25));
        pBtnCancelCoins->setText(QApplication::trUtf8("取消"));

        QFont f;
        f.setPointSize(15);
        lsMTPrompt = new QSplashScreen();
        lsMTPrompt->setGeometry(QRect(720, 400, 360, 240));
        lsSubText = new QLabel(lsMTPrompt);
        lsSubText->setGeometry(QRect(70, 90, 200, 60));
        lsSubText->setObjectName(QApplication::trUtf8("promptText"));
        lsSubText->setAlignment(Qt::AlignCenter);
        lsSubText->setWordWrap(true);
        lsSubText->setFont(f);
    }
};

namespace UI {
    class MainWidget: public surf_widget {};
    class PurchaseWidget: public purchase_widget {};
    class PayWidget: public pay_widget {};
    class MaintainWidget: public maintain_widget {};
}


#endif //UNTITLED2_UI_WIDGET_H