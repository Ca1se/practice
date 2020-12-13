/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPlainTextEdit *txtEdit;
    QPushButton *pBtnConfirm;
    QPushButton *pBtnCancel;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QCheckBox *chkBoxUnderline;
    QCheckBox *chkBoxItalic;
    QCheckBox *chkBoxBold;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QRadioButton *rBtnBlack;
    QRadioButton *rBtnRed;
    QRadioButton *rBtnBlue;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(800, 600);
        txtEdit = new QPlainTextEdit(Widget);
        txtEdit->setObjectName(QString::fromUtf8("txtEdit"));
        txtEdit->setGeometry(QRect(230, 310, 301, 151));
        txtEdit->setTabChangesFocus(false);
        pBtnConfirm = new QPushButton(Widget);
        pBtnConfirm->setObjectName(QString::fromUtf8("pBtnConfirm"));
        pBtnConfirm->setGeometry(QRect(250, 500, 86, 26));
        pBtnCancel = new QPushButton(Widget);
        pBtnCancel->setObjectName(QString::fromUtf8("pBtnCancel"));
        pBtnCancel->setGeometry(QRect(410, 500, 86, 26));
        layoutWidget = new QWidget(Widget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(330, 150, 98, 86));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        chkBoxUnderline = new QCheckBox(layoutWidget);
        chkBoxUnderline->setObjectName(QString::fromUtf8("chkBoxUnderline"));

        verticalLayout->addWidget(chkBoxUnderline);

        chkBoxItalic = new QCheckBox(layoutWidget);
        chkBoxItalic->setObjectName(QString::fromUtf8("chkBoxItalic"));

        verticalLayout->addWidget(chkBoxItalic);

        chkBoxBold = new QCheckBox(layoutWidget);
        chkBoxBold->setObjectName(QString::fromUtf8("chkBoxBold"));

        verticalLayout->addWidget(chkBoxBold);

        layoutWidget1 = new QWidget(Widget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(230, 270, 301, 26));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        rBtnBlack = new QRadioButton(layoutWidget1);
        rBtnBlack->setObjectName(QString::fromUtf8("rBtnBlack"));

        horizontalLayout->addWidget(rBtnBlack);

        rBtnRed = new QRadioButton(layoutWidget1);
        rBtnRed->setObjectName(QString::fromUtf8("rBtnRed"));

        horizontalLayout->addWidget(rBtnRed);

        rBtnBlue = new QRadioButton(layoutWidget1);
        rBtnBlue->setObjectName(QString::fromUtf8("rBtnBlue"));

        horizontalLayout->addWidget(rBtnBlue);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        txtEdit->setPlainText(QApplication::translate("Widget", "This is a Qt Demo.", nullptr));
        pBtnConfirm->setText(QApplication::translate("Widget", "\347\241\256\345\256\232", nullptr));
        pBtnCancel->setText(QApplication::translate("Widget", "\345\217\226\346\266\210", nullptr));
        chkBoxUnderline->setText(QApplication::translate("Widget", "Underline", nullptr));
        chkBoxItalic->setText(QApplication::translate("Widget", "Italic", nullptr));
        chkBoxBold->setText(QApplication::translate("Widget", "Bold", nullptr));
        rBtnBlack->setText(QApplication::translate("Widget", "Black", nullptr));
        rBtnRed->setText(QApplication::translate("Widget", "Red", nullptr));
        rBtnBlue->setText(QApplication::translate("Widget", "Blue", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
