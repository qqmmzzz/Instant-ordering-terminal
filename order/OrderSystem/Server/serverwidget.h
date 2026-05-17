#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QDateTime>
#include <QPainter>
#include <QPaintEvent>
#include <QCloseEvent>
#include "dbmanager.h"
#include "mytcpserver.h"
#include "adddishdialog.h"
#include "thememanager.h"
#include "themecolordialog.h"
#include "qrcodedialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ServerWidget; }
QT_END_NAMESPACE

class ServerWidget : public QWidget
{
    Q_OBJECT

public:
    ServerWidget(const QString &currentUser, QApplication &app, QWidget *parent = nullptr);
    ~ServerWidget();

protected:
    void paintEvent(QPaintEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

private slots:
    void onBtnStartServer();
    void onBtnRefreshMenu();
    void onBtnRefreshOrders();
    void onBtnAddDish();
    void onBtnDeleteDish();
    void onBtnEditDish();
    void onBtnSearch();
    void onBtnSelectTheme();
    void onBtnSetBackground();
    void onBtnClearBackground();
    void onTimeout();
    void onMenuRequested();
    void onOrderReceived(const QJsonObject &orderObj);
    void onClientConnected(const QString &info);
    void onClientDisconnected(const QString &info);

private:
    Ui::ServerWidget *ui;

    DbManager    *m_dbManager;
    MyTcpServer  *m_tcpServer;
    QTimer       *m_timer;
    ThemeManager *m_themeManager;
    QString       m_currentUser;
    QString       m_qrCodePath;  // 二维码图片路径

    void initUI();
    void refreshMenuTable();
    void refreshOrderTable();
};

#endif // SERVERWIDGET_H
