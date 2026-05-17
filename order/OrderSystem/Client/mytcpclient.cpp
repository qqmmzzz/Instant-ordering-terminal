#include "mytcpclient.h"

// 构造函数：创建TCP套接字并绑定信号槽
MyTcpClient::MyTcpClient(QObject *parent)
    : QObject(parent)
    , m_socket(new QTcpSocket(this))  // 创建Qt TCP客户端套接字
{
    // 连接成功信号
    connect(m_socket, &QTcpSocket::connected,
            this, &MyTcpClient::onConnected);

    // 收到服务器数据信号
    connect(m_socket, &QTcpSocket::readyRead,
            this, &MyTcpClient::onReadyRead);

    // 断开连接信号
    connect(m_socket, &QTcpSocket::disconnected,
            this, &MyTcpClient::onDisconnected);

    // 错误处理：捕获套接字错误并发送失败信号
    connect(m_socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
            [this](QAbstractSocket::SocketError err)
    {
                Q_UNUSED(err);  // 不使用错误码，只取错误信息
                emit connectFailed(m_socket->errorString());
            });
}

// 析构函数：退出前断开服务器
MyTcpClient::~MyTcpClient()
{
    disconnectFromServer();
}

// ========== 连接服务器 ==========
// host：IP地址  port：端口
// 返回：true=连接成功 false=失败
bool MyTcpClient::connectToServer(const QString &host, quint16 port)
{
    // 如果已经连接，直接返回成功
    if (m_socket->state() == QAbstractSocket::ConnectedState) {
        return true;
    }

    // 发起连接
    m_socket->connectToHost(host, port);
    // 等待3秒连接结果
    bool success = m_socket->waitForConnected(3000);

    if (!success) {
        qWarning() << "连接失败:" << host << ":" << port << "错误:" << m_socket->errorString();
    }

    return success;
}

// ========== 获取最后一次的错误信息 ==========
QString MyTcpClient::lastErrorString() const
{
    return m_socket->errorString();
}

// ========== 主动断开与服务器的连接 ==========
void MyTcpClient::disconnectFromServer()
{
    if (m_socket->state() == QAbstractSocket::ConnectedState) {
        m_socket->disconnectFromHost();
    }
}

// ========== 判断当前是否已连接服务器 ==========
bool MyTcpClient::isConnected() const
{
    return m_socket->state() == QAbstractSocket::ConnectedState;
}

// ========== 向服务器发送请求：获取菜单 ==========
void MyTcpClient::requestMenu()
{
    if (!isConnected()) return;

    // 构建JSON请求包
    QJsonObject request;
    request["type"] = "get_menu";  // 类型：获取菜单

    // 转为JSON字符串发送
    QJsonDocument doc(request);
    m_socket->write(doc.toJson(QJsonDocument::Compact));
    m_socket->flush();  // 立即发送
}

// ========== 向服务器发送：提交订单 ==========
// orderObj：订单完整JSON数据
void MyTcpClient::submitOrder(const QJsonObject &orderObj)
{
    if (!isConnected()) return;

    QJsonObject request;
    request["type"]  = "submit_order";  // 类型：提交订单
    request["order"] = orderObj;        // 订单内容

    QJsonDocument doc(request);
    m_socket->write(doc.toJson(QJsonDocument::Compact));
    m_socket->flush();
}

// ========== 连接成功的槽函数 ==========
void MyTcpClient::onConnected()
{
    qDebug() << "已连接到服务器";
    emit connected();  // 向外发送连接成功信号
}

// ========== 读取服务器发来的数据 ==========
void MyTcpClient::onReadyRead()
{
    // 把收到的数据追加到缓冲区
    m_buffer.append(m_socket->readAll());

    // 尝试解析完整的JSON
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(m_buffer, &err);

    // 解析成功
    if (err.error == QJsonParseError::NoError) {
        m_buffer.clear();  // 清空缓冲区
        QJsonObject response = doc.object();
        QString type = response["type"].toString();

        // 根据类型处理不同消息
        if (type == "menu_data") {
            // 收到菜单数据
            QJsonArray menuData = response["data"].toArray();
            emit menuReceived(menuData);  // 发送菜单信号

        } else if (type == "order_result") {
            // 收到下单结果
            bool success = response["success"].toBool();
            int orderId  = response["order_id"].toInt();
            QString msg  = response["msg"].toString();
            emit orderResult(success, orderId, msg);  // 发送结果信号
        }
    }
    // 解析失败 = 数据不完整，继续等待下一包数据
}

// ========== 与服务器断开连接 ==========
void MyTcpClient::onDisconnected()
{
    qDebug() << "与服务器断开连接";
    emit disconnected();  // 向外发送断开信号
}
