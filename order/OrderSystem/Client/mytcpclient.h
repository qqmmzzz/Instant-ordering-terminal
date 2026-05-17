#ifndef MYTCPCLIENT_H
#define MYTCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

/**
 * @brief TCP 客户端类
 * 负责连接服务器、发送请求、接收响应。
 * 
 * 请求类型：
 *   - get_menu:     请求菜单数据
 *   - submit_order: 提交订单
 */
class MyTcpClient : public QObject
{
    Q_OBJECT

public:
    explicit MyTcpClient(QObject *parent = nullptr);
    ~MyTcpClient();

    /// 连接服务器
    bool connectToServer(const QString &host, quint16 port);
    
    /// 获取最后一次连接错误信息
    QString lastErrorString() const;

    /// 断开连接
    void disconnectFromServer();

    /// 是否已连接
    bool isConnected() const;

    /// 请求菜单
    void requestMenu();

    /// 提交订单
    void submitOrder(const QJsonObject &orderObj);

signals:
    /// 连接成功
    void connected();

    /// 连接失败
    void connectFailed(const QString &error);

    /// 断开连接
    void disconnected();

    /// 收到菜单数据
    void menuReceived(const QJsonArray &menuData);

    /// 收到订单结果
    void orderResult(bool success, int orderId, const QString &msg);

private slots:
    void onConnected();
    void onReadyRead();
    void onDisconnected();

private:
    QTcpSocket *m_socket;
    QByteArray  m_buffer;  // 数据缓冲区
};

#endif // MYTCPCLIENT_H
