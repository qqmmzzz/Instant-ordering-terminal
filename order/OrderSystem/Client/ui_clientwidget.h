/********************************************************************************
** Form generated from reading UI file 'clientwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENTWIDGET_H
#define UI_CLIENTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
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
            ClientWidget->setObjectName(QStringLiteral("ClientWidget"));
        ClientWidget->resize(800, 480);
        gridLayout_2 = new QGridLayout(ClientWidget);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        cartLayout = new QVBoxLayout();
        cartLayout->setObjectName(QStringLiteral("cartLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        label = new QLabel(ClientWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\232\266\344\271\246"));
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);

        hboxLayout->addWidget(label);

        spacerItem = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        btnClearCart = new QPushButton(ClientWidget);
        btnClearCart->setObjectName(QStringLiteral("btnClearCart"));

        hboxLayout->addWidget(btnClearCart);


        cartLayout->addLayout(hboxLayout);

        listCart = new QListWidget(ClientWidget);
        listCart->setObjectName(QStringLiteral("listCart"));
        QFont font1;
        font1.setPointSize(10);
        listCart->setFont(font1);

        cartLayout->addWidget(listCart);


        gridLayout_2->addLayout(cartLayout, 1, 1, 2, 1);

        bottomLayout = new QHBoxLayout();
        bottomLayout->setObjectName(QStringLiteral("bottomLayout"));
        label1 = new QLabel(ClientWidget);
        label1->setObjectName(QStringLiteral("label1"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\215\216\346\226\207\351\232\266\344\271\246"));
        label1->setFont(font2);

        bottomLayout->addWidget(label1);

        editTableNo = new QLineEdit(ClientWidget);
        editTableNo->setObjectName(QStringLiteral("editTableNo"));

        bottomLayout->addWidget(editTableNo);

        label2 = new QLabel(ClientWidget);
        label2->setObjectName(QStringLiteral("label2"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\351\232\266\344\271\246"));
        label2->setFont(font3);

        bottomLayout->addWidget(label2);

        spinPeople = new QSpinBox(ClientWidget);
        spinPeople->setObjectName(QStringLiteral("spinPeople"));
        spinPeople->setMinimum(1);
        spinPeople->setMaximum(20);
        spinPeople->setValue(1);

        bottomLayout->addWidget(spinPeople);

        spacer2 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        bottomLayout->addItem(spacer2);

        lblTotalPrice = new QLabel(ClientWidget);
        lblTotalPrice->setObjectName(QStringLiteral("lblTotalPrice"));
        lblTotalPrice->setFont(font);

        bottomLayout->addWidget(lblTotalPrice);

        btnSubmitOrder = new QPushButton(ClientWidget);
        btnSubmitOrder->setObjectName(QStringLiteral("btnSubmitOrder"));
        QFont font4;
        font4.setFamily(QString::fromUtf8("\345\215\216\346\226\207\351\232\266\344\271\246"));
        font4.setBold(true);
        font4.setWeight(75);
        btnSubmitOrder->setFont(font4);

        bottomLayout->addWidget(btnSubmitOrder);


        gridLayout_2->addLayout(bottomLayout, 3, 0, 1, 2);

        topLayout = new QHBoxLayout();
        topLayout->setObjectName(QStringLiteral("topLayout"));
        lblTime = new QLabel(ClientWidget);
        lblTime->setObjectName(QStringLiteral("lblTime"));

        topLayout->addWidget(lblTime);

        spacer1 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        topLayout->addItem(spacer1);

        btnSelectTheme = new QPushButton(ClientWidget);
        btnSelectTheme->setObjectName(QStringLiteral("btnSelectTheme"));
        btnSelectTheme->setFont(font3);

        topLayout->addWidget(btnSelectTheme);

        btnSetBackground = new QPushButton(ClientWidget);
        btnSetBackground->setObjectName(QStringLiteral("btnSetBackground"));
        btnSetBackground->setFont(font2);

        topLayout->addWidget(btnSetBackground);

        btnClearBackground = new QPushButton(ClientWidget);
        btnClearBackground->setObjectName(QStringLiteral("btnClearBackground"));
        btnClearBackground->setFont(font2);

        topLayout->addWidget(btnClearBackground);

        lblConnStatus = new QLabel(ClientWidget);
        lblConnStatus->setObjectName(QStringLiteral("lblConnStatus"));

        topLayout->addWidget(lblConnStatus);

        editHost = new QLineEdit(ClientWidget);
        editHost->setObjectName(QStringLiteral("editHost"));

        topLayout->addWidget(editHost);

        spinPort = new QSpinBox(ClientWidget);
        spinPort->setObjectName(QStringLiteral("spinPort"));
        spinPort->setMinimum(1024);
        spinPort->setMaximum(65535);
        spinPort->setValue(8888);

        topLayout->addWidget(spinPort);

        btnConnect = new QPushButton(ClientWidget);
        btnConnect->setObjectName(QStringLiteral("btnConnect"));
        btnConnect->setFont(font2);

        topLayout->addWidget(btnConnect);

        btnGetMenu = new QPushButton(ClientWidget);
        btnGetMenu->setObjectName(QStringLiteral("btnGetMenu"));
        btnGetMenu->setFont(font2);

        topLayout->addWidget(btnGetMenu);


        gridLayout_2->addLayout(topLayout, 0, 0, 1, 2);

        listMenu = new QListWidget(ClientWidget);
        listMenu->setObjectName(QStringLiteral("listMenu"));
        listMenu->setFont(font1);

        gridLayout_2->addWidget(listMenu, 2, 0, 1, 1);

        label3 = new QLabel(ClientWidget);
        label3->setObjectName(QStringLiteral("label3"));
        label3->setFont(font4);

        gridLayout_2->addWidget(label3, 1, 0, 1, 1);


        retranslateUi(ClientWidget);

        QMetaObject::connectSlotsByName(ClientWidget);
    } // setupUi

    void retranslateUi(QWidget *ClientWidget)
    {
        ClientWidget->setWindowTitle(QApplication::translate("ClientWidget", "\347\202\271\351\244\220\347\273\210\347\253\257 - \345\256\242\346\210\267\347\253\257", 0));
        label->setStyleSheet(QApplication::translate("ClientWidget", "font-size: 13px; font-weight: bold;", 0));
        label->setText(QApplication::translate("ClientWidget", "\350\264\255\347\211\251\350\275\246", 0));
        btnClearCart->setText(QApplication::translate("ClientWidget", "\346\270\205\347\251\272", 0));
        label1->setText(QApplication::translate("ClientWidget", "\346\241\214\345\217\267\357\274\232", 0));
        editTableNo->setPlaceholderText(QApplication::translate("ClientWidget", "A01", 0));
        label2->setText(QApplication::translate("ClientWidget", "\344\272\272\346\225\260\357\274\232", 0));
        lblTotalPrice->setStyleSheet(QApplication::translate("ClientWidget", "font-size: 14px; font-weight: bold; color: #e74c3c;", 0));
        lblTotalPrice->setText(QApplication::translate("ClientWidget", "\346\200\273\344\273\267\357\274\232\357\277\2450.00", 0));
        btnSubmitOrder->setStyleSheet(QApplication::translate("ClientWidget", "background-color: #f39c12; color: white; padding: 5px 16px; font-size: 13px; font-weight: bold; border-radius: 4px;", 0));
        btnSubmitOrder->setText(QApplication::translate("ClientWidget", "\346\217\220\344\272\244\350\256\242\345\215\225", 0));
        lblTime->setStyleSheet(QApplication::translate("ClientWidget", "font-size: 12px; font-weight: bold;", 0));
        lblTime->setText(QApplication::translate("ClientWidget", "--", 0));
        btnSelectTheme->setText(QApplication::translate("ClientWidget", "\344\270\273\351\242\230", 0));
        btnSetBackground->setText(QApplication::translate("ClientWidget", "\350\203\214\346\231\257", 0));
        btnClearBackground->setText(QApplication::translate("ClientWidget", "\346\270\205\351\231\244", 0));
        lblConnStatus->setStyleSheet(QApplication::translate("ClientWidget", "color: red; font-size: 11px; font-weight: bold;", 0));
        lblConnStatus->setText(QApplication::translate("ClientWidget", "\346\234\252\350\277\236\346\216\245", 0));
        editHost->setText(QApplication::translate("ClientWidget", "192.168.5.183", 0));
        btnConnect->setText(QApplication::translate("ClientWidget", "\350\277\236\346\216\245", 0));
        btnGetMenu->setText(QApplication::translate("ClientWidget", "\350\216\267\345\217\226\350\217\234\345\215\225", 0));
        label3->setStyleSheet(QApplication::translate("ClientWidget", "font-size: 13px; font-weight: bold;", 0));
        label3->setText(QApplication::translate("ClientWidget", "\350\217\234\345\215\225", 0));
    } // retranslateUi

};

namespace Ui {
    class ClientWidget: public Ui_ClientWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTWIDGET_H
