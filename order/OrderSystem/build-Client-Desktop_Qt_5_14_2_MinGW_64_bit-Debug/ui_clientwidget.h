/********************************************************************************
** Form generated from reading UI file 'clientwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENTWIDGET_H
#define UI_CLIENTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClientWidget
{
public:
    QGridLayout *gridLayout_2;
    QVBoxLayout *cartLayout;
    QHBoxLayout *hboxLayout;
    QLabel *label;
    QSpacerItem *spacerItem;
    QPushButton *btnClearCart;
    QListWidget *listCart;
    QHBoxLayout *bottomLayout;
    QLabel *label1;
    QLineEdit *editTableNo;
    QLabel *label2;
    QSpinBox *spinPeople;
    QSpacerItem *spacer2;
    QLabel *lblTotalPrice;
    QPushButton *btnSubmitOrder;
    QHBoxLayout *topLayout;
    QLabel *lblTime;
    QSpacerItem *spacer1;
    QPushButton *btnSelectTheme;
    QPushButton *btnSetBackground;
    QPushButton *btnClearBackground;
    QLabel *lblConnStatus;
    QLineEdit *editHost;
    QSpinBox *spinPort;
    QPushButton *btnConnect;
    QPushButton *btnGetMenu;
    QListWidget *listMenu;
    QLabel *label3;

    void setupUi(QWidget *ClientWidget)
    {
        if (ClientWidget->objectName().isEmpty())
            ClientWidget->setObjectName(QString::fromUtf8("ClientWidget"));
        ClientWidget->resize(800, 480);
        gridLayout_2 = new QGridLayout(ClientWidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        cartLayout = new QVBoxLayout();
        cartLayout->setObjectName(QString::fromUtf8("cartLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        label = new QLabel(ClientWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\232\266\344\271\246"));
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);

        hboxLayout->addWidget(label);

        spacerItem = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        btnClearCart = new QPushButton(ClientWidget);
        btnClearCart->setObjectName(QString::fromUtf8("btnClearCart"));

        hboxLayout->addWidget(btnClearCart);


        cartLayout->addLayout(hboxLayout);

        listCart = new QListWidget(ClientWidget);
        listCart->setObjectName(QString::fromUtf8("listCart"));
        QFont font1;
        font1.setPointSize(10);
        listCart->setFont(font1);

        cartLayout->addWidget(listCart);


        gridLayout_2->addLayout(cartLayout, 1, 1, 2, 1);

        bottomLayout = new QHBoxLayout();
        bottomLayout->setObjectName(QString::fromUtf8("bottomLayout"));
        label1 = new QLabel(ClientWidget);
        label1->setObjectName(QString::fromUtf8("label1"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\215\216\346\226\207\351\232\266\344\271\246"));
        label1->setFont(font2);

        bottomLayout->addWidget(label1);

        editTableNo = new QLineEdit(ClientWidget);
        editTableNo->setObjectName(QString::fromUtf8("editTableNo"));

        bottomLayout->addWidget(editTableNo);

        label2 = new QLabel(ClientWidget);
        label2->setObjectName(QString::fromUtf8("label2"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\351\232\266\344\271\246"));
        label2->setFont(font3);

        bottomLayout->addWidget(label2);

        spinPeople = new QSpinBox(ClientWidget);
        spinPeople->setObjectName(QString::fromUtf8("spinPeople"));
        spinPeople->setMinimum(1);
        spinPeople->setMaximum(20);
        spinPeople->setValue(1);

        bottomLayout->addWidget(spinPeople);

        spacer2 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        bottomLayout->addItem(spacer2);

        lblTotalPrice = new QLabel(ClientWidget);
        lblTotalPrice->setObjectName(QString::fromUtf8("lblTotalPrice"));
        lblTotalPrice->setFont(font);

        bottomLayout->addWidget(lblTotalPrice);

        btnSubmitOrder = new QPushButton(ClientWidget);
        btnSubmitOrder->setObjectName(QString::fromUtf8("btnSubmitOrder"));
        QFont font4;
        font4.setFamily(QString::fromUtf8("\345\215\216\346\226\207\351\232\266\344\271\246"));
        font4.setBold(true);
        font4.setWeight(75);
        btnSubmitOrder->setFont(font4);

        bottomLayout->addWidget(btnSubmitOrder);


        gridLayout_2->addLayout(bottomLayout, 3, 0, 1, 2);

        topLayout = new QHBoxLayout();
        topLayout->setObjectName(QString::fromUtf8("topLayout"));
        lblTime = new QLabel(ClientWidget);
        lblTime->setObjectName(QString::fromUtf8("lblTime"));

        topLayout->addWidget(lblTime);

        spacer1 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        topLayout->addItem(spacer1);

        btnSelectTheme = new QPushButton(ClientWidget);
        btnSelectTheme->setObjectName(QString::fromUtf8("btnSelectTheme"));
        btnSelectTheme->setFont(font3);

        topLayout->addWidget(btnSelectTheme);

        btnSetBackground = new QPushButton(ClientWidget);
        btnSetBackground->setObjectName(QString::fromUtf8("btnSetBackground"));
        btnSetBackground->setFont(font2);

        topLayout->addWidget(btnSetBackground);

        btnClearBackground = new QPushButton(ClientWidget);
        btnClearBackground->setObjectName(QString::fromUtf8("btnClearBackground"));
        btnClearBackground->setFont(font2);

        topLayout->addWidget(btnClearBackground);

        lblConnStatus = new QLabel(ClientWidget);
        lblConnStatus->setObjectName(QString::fromUtf8("lblConnStatus"));

        topLayout->addWidget(lblConnStatus);

        editHost = new QLineEdit(ClientWidget);
        editHost->setObjectName(QString::fromUtf8("editHost"));

        topLayout->addWidget(editHost);

        spinPort = new QSpinBox(ClientWidget);
        spinPort->setObjectName(QString::fromUtf8("spinPort"));
        spinPort->setMinimum(1024);
        spinPort->setMaximum(65535);
        spinPort->setValue(8888);

        topLayout->addWidget(spinPort);

        btnConnect = new QPushButton(ClientWidget);
        btnConnect->setObjectName(QString::fromUtf8("btnConnect"));
        btnConnect->setFont(font2);

        topLayout->addWidget(btnConnect);

        btnGetMenu = new QPushButton(ClientWidget);
        btnGetMenu->setObjectName(QString::fromUtf8("btnGetMenu"));
        btnGetMenu->setFont(font2);

        topLayout->addWidget(btnGetMenu);


        gridLayout_2->addLayout(topLayout, 0, 0, 1, 2);

        listMenu = new QListWidget(ClientWidget);
        listMenu->setObjectName(QString::fromUtf8("listMenu"));
        listMenu->setFont(font1);

        gridLayout_2->addWidget(listMenu, 2, 0, 1, 1);

        label3 = new QLabel(ClientWidget);
        label3->setObjectName(QString::fromUtf8("label3"));
        label3->setFont(font4);

        gridLayout_2->addWidget(label3, 1, 0, 1, 1);


        retranslateUi(ClientWidget);

        QMetaObject::connectSlotsByName(ClientWidget);
    } // setupUi

    void retranslateUi(QWidget *ClientWidget)
    {
        ClientWidget->setWindowTitle(QCoreApplication::translate("ClientWidget", "\347\202\271\351\244\220\347\273\210\347\253\257 - \345\256\242\346\210\267\347\253\257", nullptr));
        label->setStyleSheet(QCoreApplication::translate("ClientWidget", "font-size: 13px; font-weight: bold;", nullptr));
        label->setText(QCoreApplication::translate("ClientWidget", "\350\264\255\347\211\251\350\275\246", nullptr));
        btnClearCart->setText(QCoreApplication::translate("ClientWidget", "\346\270\205\347\251\272", nullptr));
        label1->setText(QCoreApplication::translate("ClientWidget", "\346\241\214\345\217\267\357\274\232", nullptr));
        editTableNo->setPlaceholderText(QCoreApplication::translate("ClientWidget", "A01", nullptr));
        label2->setText(QCoreApplication::translate("ClientWidget", "\344\272\272\346\225\260\357\274\232", nullptr));
        lblTotalPrice->setStyleSheet(QCoreApplication::translate("ClientWidget", "font-size: 14px; font-weight: bold; color: #e74c3c;", nullptr));
        lblTotalPrice->setText(QCoreApplication::translate("ClientWidget", "\346\200\273\344\273\267\357\274\232\357\277\2450.00", nullptr));
        btnSubmitOrder->setStyleSheet(QCoreApplication::translate("ClientWidget", "background-color: #f39c12; color: white; padding: 5px 16px; font-size: 13px; font-weight: bold; border-radius: 4px;", nullptr));
        btnSubmitOrder->setText(QCoreApplication::translate("ClientWidget", "\346\217\220\344\272\244\350\256\242\345\215\225", nullptr));
        lblTime->setStyleSheet(QCoreApplication::translate("ClientWidget", "font-size: 12px; font-weight: bold;", nullptr));
        lblTime->setText(QCoreApplication::translate("ClientWidget", "--", nullptr));
        btnSelectTheme->setText(QCoreApplication::translate("ClientWidget", "\344\270\273\351\242\230", nullptr));
        btnSetBackground->setText(QCoreApplication::translate("ClientWidget", "\350\203\214\346\231\257", nullptr));
        btnClearBackground->setText(QCoreApplication::translate("ClientWidget", "\346\270\205\351\231\244", nullptr));
        lblConnStatus->setStyleSheet(QCoreApplication::translate("ClientWidget", "color: red; font-size: 11px; font-weight: bold;", nullptr));
        lblConnStatus->setText(QCoreApplication::translate("ClientWidget", "\346\234\252\350\277\236\346\216\245", nullptr));
        editHost->setText(QCoreApplication::translate("ClientWidget", "192.168.5.183", nullptr));
        btnConnect->setText(QCoreApplication::translate("ClientWidget", "\350\277\236\346\216\245", nullptr));
        btnGetMenu->setText(QCoreApplication::translate("ClientWidget", "\350\216\267\345\217\226\350\217\234\345\215\225", nullptr));
        label3->setStyleSheet(QCoreApplication::translate("ClientWidget", "font-size: 13px; font-weight: bold;", nullptr));
        label3->setText(QCoreApplication::translate("ClientWidget", "\350\217\234\345\215\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ClientWidget: public Ui_ClientWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTWIDGET_H
