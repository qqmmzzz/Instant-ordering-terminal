#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QDateTime>
#include <QMessageBox>
#include <QFileDialog>
#include <QPainter>
#include <QPaintEvent>
#include <QCloseEvent>
#include "mytcpclient.h"
#include "cartmanager.h"
#include "dishitemwidget.h"
#include "cartitemwidget.h"
#include "thememanager.h"
#include "themecolordialog.h"
#include "qrcodedialog.h"
#include "numpadwidget.h"
#include "alphakeyboardwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ClientWidget; }
QT_END_NAMESPACE

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    ClientWidget(QApplication &app, QWidget *parent = nullptr);
    ~ClientWidget();

protected:
    void paintEvent(QPaintEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void onBtnConnect();
    void onBtnGetMenu();
    void onBtnSubmitOrder();
    void onBtnClearCart();
    void onBtnSelectTheme();
    void onBtnSetBackground();
    void onBtnClearBackground();
    void onBtnExit();
    void onTimeout();
    void onMenuReceived(const QJsonArray &menuData);
    void onOrderResult(bool success, int orderId, const QString &msg);
    void onCartChanged();
    void onTotalPriceChanged(double total);
    void onAddToCart(int dishId, const QString &dishName, double price, int count);
    void onCartCountChanged(int dishId, int newCount);
    void onCartRemoveRequested(int dishId);

private:
    Ui::ClientWidget *ui;

    MyTcpClient *m_tcpClient;
    CartManager *m_cartManager;
    QTimer      *m_timer;
    ThemeManager *m_themeManager;
    QString      m_qrCodePath;
    NumpadWidget *m_numpad;
    AlphaKeyboardWidget *m_alphaKeyboard;

    void initUI();
    void refreshCartUI();
};

#endif // CLIENTWIDGET_H
