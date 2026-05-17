#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

/**
 * @brief TCP 服务器类
 * 监听客户端连接，接收请求并返回相应数据。
 * 
 * 通信协议（JSON格式）：
 *   客户端请求：{ "type": "get_menu" }
 *   服务器响应：{ "type": "menu_data", "data": [...] }
 * 
 *   客户端请求：{ "type": "submit_order", "order": { ... } }
 *   服务器响应：{ "type": "order_result", "success": true/false, "order_id": int, "msg": "..." }
 */
class MyTcpServer : public QObject
{
    Q_OBJECT

public:
    explicit MyTcpServer(QObject *parent = nullptr);
    ~MyTcpServer();

    /// 启动服务器监听
    bool start(quint16 port = 8888);

    /// 停止服务器
    void stop();

    /// 服务器是否正在监听
    bool isListening() const;

    /// 获取已连接的客户端列表
    QList<QTcpSocket*> getClientList() const;

signals:
    /// 收到菜单请求信号
    void menuRequested();

    /// 收到订单提交信号，携带订单JSON对象
    void orderReceived(const QJsonObject &orderObj);

    /// 新客户端连接信号
    void clientConnected(const QString &clientInfo);

    /// 客户端断开信号
    void clientDisconnected(const QString &clientInfo);

public slots:
    /// 设置菜单数据（由 DbManager 提供后发送给客户端）
    void setMenuData(const QJsonArray &menuData);

    /// 设置订单处理结果（由 DbManager 处理后反馈）
    void sendOrderResult(QTcpSocket *socket, bool success, int orderId, const QString &msg);

private slots:
    void onNewConnection();
    void onReadyRead();
    void onClientDisconnected();

private:
    QTcpServer *m_tcpServer;
    QJsonArray  m_menuData;       // 缓存的菜单数据
    QList<QTcpSocket*> m_clients; // 已连接的客户端列表

    void handleRequest(QTcpSocket *socket, const QJsonObject &request);
};

#endif // MYTCPSERVER_H
