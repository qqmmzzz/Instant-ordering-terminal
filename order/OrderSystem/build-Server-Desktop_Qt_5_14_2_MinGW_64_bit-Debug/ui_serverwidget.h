/********************************************************************************
** Form generated from reading UI file 'serverwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVERWIDGET_H
#define UI_SERVERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ServerWidget
{
public:
    QVBoxLayout *mainLayout;
    QHBoxLayout *themeLayout;
    QLabel *lblTime;
    QSpacerItem *spacerTheme;
    QPushButton *btnSelectTheme;
    QPushButton *btnSetBackground;
    QPushButton *btnClearBackground;
    QHBoxLayout *serverLayout;
    QLabel *lblStatus;
    QSpacerItem *spacer1;
    QLabel *label;
    QSpinBox *spinPort;
    QPushButton *btnStartServer;
    QTabWidget *tabWidget;
    QWidget *tabMenu;
    QVBoxLayout *menuTabLayout;
    QHBoxLayout *hboxLayout;
    QPushButton *btnAddDish;
    QPushButton *btnDeleteDish;
    QPushButton *btnEditDish;
    QSpacerItem *spacer2;
    QLineEdit *editSearch;
    QPushButton *btnSearch;
    QPushButton *btnRefreshMenu;
    QTableWidget *tableMenu;
    QWidget *tabOrders;
    QVBoxLayout *orderTabLayout;
    QHBoxLayout *hboxLayout1;
    QSpacerItem *spacer3;
    QPushButton *btnRefreshOrders;
    QTableWidget *tableOrders;
    QLabel *lblLog;
    QTextEdit *txtLog;

    void setupUi(QWidget *ServerWidget)
    {
        if (ServerWidget->objectName().isEmpty())
            ServerWidget->setObjectName(QString::fromUtf8("ServerWidget"));
        ServerWidget->resize(1000, 720);
        mainLayout = new QVBoxLayout(ServerWidget);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        themeLayout = new QHBoxLayout();
        themeLayout->setObjectName(QString::fromUtf8("themeLayout"));
        lblTime = new QLabel(ServerWidget);
        lblTime->setObjectName(QString::fromUtf8("lblTime"));
        QFont font;
        font.setFamily(QString::fromUtf8("\344\273\277\345\256\213"));
        font.setBold(true);
        font.setWeight(75);
        lblTime->setFont(font);

        themeLayout->addWidget(lblTime);

        spacerTheme = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        themeLayout->addItem(spacerTheme);

        btnSelectTheme = new QPushButton(ServerWidget);
        btnSelectTheme->setObjectName(QString::fromUtf8("btnSelectTheme"));

        themeLayout->addWidget(btnSelectTheme);

        btnSetBackground = new QPushButton(ServerWidget);
        btnSetBackground->setObjectName(QString::fromUtf8("btnSetBackground"));

        themeLayout->addWidget(btnSetBackground);

        btnClearBackground = new QPushButton(ServerWidget);
        btnClearBackground->setObjectName(QString::fromUtf8("btnClearBackground"));

        themeLayout->addWidget(btnClearBackground);


        mainLayout->addLayout(themeLayout);

        serverLayout = new QHBoxLayout();
        serverLayout->setObjectName(QString::fromUtf8("serverLayout"));
        lblStatus = new QLabel(ServerWidget);
        lblStatus->setObjectName(QString::fromUtf8("lblStatus"));

        serverLayout->addWidget(lblStatus);

        spacer1 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        serverLayout->addItem(spacer1);

        label = new QLabel(ServerWidget);
        label->setObjectName(QString::fromUtf8("label"));

        serverLayout->addWidget(label);

        spinPort = new QSpinBox(ServerWidget);
        spinPort->setObjectName(QString::fromUtf8("spinPort"));
        spinPort->setMinimum(1024);
        spinPort->setMaximum(65535);
        spinPort->setValue(8888);

        serverLayout->addWidget(spinPort);

        btnStartServer = new QPushButton(ServerWidget);
        btnStartServer->setObjectName(QString::fromUtf8("btnStartServer"));

        serverLayout->addWidget(btnStartServer);


        mainLayout->addLayout(serverLayout);

        tabWidget = new QTabWidget(ServerWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabMenu = new QWidget();
        tabMenu->setObjectName(QString::fromUtf8("tabMenu"));
        menuTabLayout = new QVBoxLayout(tabMenu);
        menuTabLayout->setObjectName(QString::fromUtf8("menuTabLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        btnAddDish = new QPushButton(tabMenu);
        btnAddDish->setObjectName(QString::fromUtf8("btnAddDish"));

        hboxLayout->addWidget(btnAddDish);

        btnDeleteDish = new QPushButton(tabMenu);
        btnDeleteDish->setObjectName(QString::fromUtf8("btnDeleteDish"));

        hboxLayout->addWidget(btnDeleteDish);

        btnEditDish = new QPushButton(tabMenu);
        btnEditDish->setObjectName(QString::fromUtf8("btnEditDish"));

        hboxLayout->addWidget(btnEditDish);

        spacer2 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacer2);

        editSearch = new QLineEdit(tabMenu);
        editSearch->setObjectName(QString::fromUtf8("editSearch"));

        hboxLayout->addWidget(editSearch);

        btnSearch = new QPushButton(tabMenu);
        btnSearch->setObjectName(QString::fromUtf8("btnSearch"));

        hboxLayout->addWidget(btnSearch);

        btnRefreshMenu = new QPushButton(tabMenu);
        btnRefreshMenu->setObjectName(QString::fromUtf8("btnRefreshMenu"));

        hboxLayout->addWidget(btnRefreshMenu);


        menuTabLayout->addLayout(hboxLayout);

        tableMenu = new QTableWidget(tabMenu);
        tableMenu->setObjectName(QString::fromUtf8("tableMenu"));
        tableMenu->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableMenu->setAlternatingRowColors(true);
        tableMenu->setSelectionBehavior(QAbstractItemView::SelectRows);

        menuTabLayout->addWidget(tableMenu);

        tabWidget->addTab(tabMenu, QString());
        tabOrders = new QWidget();
        tabOrders->setObjectName(QString::fromUtf8("tabOrders"));
        orderTabLayout = new QVBoxLayout(tabOrders);
        orderTabLayout->setObjectName(QString::fromUtf8("orderTabLayout"));
        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        spacer3 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacer3);

        btnRefreshOrders = new QPushButton(tabOrders);
        btnRefreshOrders->setObjectName(QString::fromUtf8("btnRefreshOrders"));

        hboxLayout1->addWidget(btnRefreshOrders);


        orderTabLayout->addLayout(hboxLayout1);

        tableOrders = new QTableWidget(tabOrders);
        tableOrders->setObjectName(QString::fromUtf8("tableOrders"));
        tableOrders->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableOrders->setAlternatingRowColors(true);
        tableOrders->setSelectionBehavior(QAbstractItemView::SelectRows);

        orderTabLayout->addWidget(tableOrders);

        tabWidget->addTab(tabOrders, QString());

        mainLayout->addWidget(tabWidget);

        lblLog = new QLabel(ServerWidget);
        lblLog->setObjectName(QString::fromUtf8("lblLog"));

        mainLayout->addWidget(lblLog);

        txtLog = new QTextEdit(ServerWidget);
        txtLog->setObjectName(QString::fromUtf8("txtLog"));
        txtLog->setMaximumSize(QSize(16777215, 120));
        txtLog->setReadOnly(true);

        mainLayout->addWidget(txtLog);


        retranslateUi(ServerWidget);

        QMetaObject::connectSlotsByName(ServerWidget);
    } // setupUi

    void retranslateUi(QWidget *ServerWidget)
    {
        ServerWidget->setWindowTitle(QCoreApplication::translate("ServerWidget", "\347\202\271\351\244\220\347\273\210\347\253\257 - \346\234\215\345\212\241\345\231\250\347\253\257", nullptr));
        lblTime->setStyleSheet(QCoreApplication::translate("ServerWidget", "font-size: 14px; font-weight: bold;", nullptr));
        lblTime->setText(QCoreApplication::translate("ServerWidget", "\345\275\223\345\211\215\346\227\266\351\227\264\357\274\232--", nullptr));
        btnSelectTheme->setText(QCoreApplication::translate("ServerWidget", "\351\200\211\346\213\251\344\270\273\351\242\230", nullptr));
        btnSetBackground->setText(QCoreApplication::translate("ServerWidget", "\350\256\276\347\275\256\350\203\214\346\231\257", nullptr));
        btnClearBackground->setText(QCoreApplication::translate("ServerWidget", "\346\270\205\351\231\244\350\203\214\346\231\257", nullptr));
        lblStatus->setStyleSheet(QCoreApplication::translate("ServerWidget", "color: red; font-weight: bold;", nullptr));
        lblStatus->setText(QCoreApplication::translate("ServerWidget", "\346\234\215\345\212\241\345\231\250\347\212\266\346\200\201\357\274\232\345\267\262\345\201\234\346\255\242", nullptr));
        label->setText(QCoreApplication::translate("ServerWidget", "\347\253\257\345\217\243\357\274\232", nullptr));
        btnStartServer->setText(QCoreApplication::translate("ServerWidget", "\345\220\257\345\212\250\346\234\215\345\212\241\345\231\250", nullptr));
        btnAddDish->setStyleSheet(QCoreApplication::translate("ServerWidget", "QPushButton{background-color:rgba(230,126,34,0.7);color:white;font-weight:bold;padding:6px 20px;font-size:20px;border-radius:4px;}\n"
"QPushButton:hover{background-color:rgba(230,126,34,0.9);}", nullptr));
        btnAddDish->setText(QCoreApplication::translate("ServerWidget", "+", nullptr));
        btnDeleteDish->setStyleSheet(QCoreApplication::translate("ServerWidget", "QPushButton{background-color:rgba(231,76,60,0.7);color:white;font-weight:bold;padding:6px 20px;font-size:20px;border-radius:4px;}\n"
"QPushButton:hover{background-color:rgba(231,76,60,0.9);}", nullptr));
        btnDeleteDish->setText(QCoreApplication::translate("ServerWidget", "-", nullptr));
        btnEditDish->setStyleSheet(QCoreApplication::translate("ServerWidget", "QPushButton{background-color:rgba(52,152,219,0.7);color:white;font-weight:bold;padding:6px 14px;border-radius:4px;}\n"
"QPushButton:hover{background-color:rgba(52,152,219,0.9);}", nullptr));
        btnEditDish->setText(QCoreApplication::translate("ServerWidget", "\347\274\226\350\276\221", nullptr));
        editSearch->setPlaceholderText(QCoreApplication::translate("ServerWidget", "\346\220\234\347\264\242\350\217\234\345\223\201...", nullptr));
        btnSearch->setStyleSheet(QCoreApplication::translate("ServerWidget", "QPushButton{background-color:rgba(46,204,113,0.7);color:white;font-weight:bold;padding:6px 14px;border-radius:4px;}\n"
"QPushButton:hover{background-color:rgba(46,204,113,0.9);}", nullptr));
        btnSearch->setText(QCoreApplication::translate("ServerWidget", "\347\255\233\351\200\211", nullptr));
        btnRefreshMenu->setText(QCoreApplication::translate("ServerWidget", "\345\210\267\346\226\260\350\217\234\345\215\225", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabMenu), QCoreApplication::translate("ServerWidget", "\350\217\234\345\215\225\347\256\241\347\220\206", nullptr));
        btnRefreshOrders->setText(QCoreApplication::translate("ServerWidget", "\345\210\267\346\226\260\350\256\242\345\215\225", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabOrders), QCoreApplication::translate("ServerWidget", "\350\256\242\345\215\225\345\210\227\350\241\250", nullptr));
        lblLog->setText(QCoreApplication::translate("ServerWidget", "\351\200\232\344\277\241\346\227\245\345\277\227\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ServerWidget: public Ui_ServerWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVERWIDGET_H
