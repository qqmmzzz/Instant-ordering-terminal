#include "mytcpserver.h"

// 构造函数：创建TCP服务器对象，绑定新连接信号
MyTcpServer::MyTcpServer(QObject *parent)
    : QObject(parent)
    , m_tcpServer(new QTcpServer(this))  // 创建Qt官方TCP服务器
{
    // 当有新客户端连接时，触发 onNewConnection
    connect(m_tcpServer, &QTcpServer::newConnection,
            this, &MyTcpServer::onNewConnection);
}

// 析构函数：关闭服务器
MyTcpServer::~MyTcpServer()
{
    stop();
}

// ========== 启动服务器，开始监听端口 ==========
// port：要监听的端口号（例如 8888）
bool MyTcpServer::start(quint16 port)
{
    // 如果正在监听，先关闭
    if (m_tcpServer->isListening()) {
        m_tcpServer->close();
    }

    // 监听所有网卡IP + 指定端口
    if (!m_tcpServer->listen(QHostAddress::Any, port))
    {
        qCritical() << "服务器启动失败:" << m_tcpServer->errorString();
        return false;
    }

    qDebug() << "服务器启动成功，监听端口:" << port;
    return true;
}

// ========== 判断服务器是否正在运行 ==========
bool MyTcpServer::isListening() const
{
    return m_tcpServer->isListening();
}

// ========== 获取当前所有连接的客户端列表 ==========
QList<QTcpSocket*> MyTcpServer::getClientList() const
{
    return m_clients;
}

// ========== 停止服务器：断开所有客户端 + 关闭监听 ==========
void MyTcpServer::stop()
{
    // 断开所有已连接的客户端
    for (QTcpSocket *client : m_clients)
    {
        client->disconnectFromHost();
    }
    m_clients.clear();

    // 关闭服务器监听
    if (m_tcpServer->isListening())
    {
        m_tcpServer->close();
    }
    qDebug() << "服务器已停止";
}

// ========== 新客户端接入处理 ==========
void MyTcpServer::onNewConnection()
{
    // 获取新连接的客户端Socket
    QTcpSocket *client = m_tcpServer->nextPendingConnection();

    // 记录客户端IP和端口，用于日志显示
    QString clientInfo = QString("%1:%2")
                             .arg(client->peerAddress().toString())
                             .arg(client->peerPort());

    // 添加到客户端管理列表
    m_clients.append(client);
    emit clientConnected(clientInfo);  // 发送信号：有客户端上线

    // 绑定客户端信号：收到数据、断开连接
    connect(client, &QTcpSocket::readyRead, this, &MyTcpServer::onReadyRead);
    connect(client, &QTcpSocket::disconnected, this, &MyTcpServer::onClientDisconnected);

    qDebug() << "客户端已连接:" << clientInfo;
}

// ========== 读取客户端发来的数据 ==========
void MyTcpServer::onReadyRead()
{
    // 获取发送数据的客户端对象
    QTcpSocket *client = qobject_cast<QTcpSocket*>(sender());
    if (!client) return;

    // 读取所有数据
    QByteArray data = client->readAll();
    qDebug() << "收到数据:" << data;

    // 解析JSON
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(data, &err);

    // JSON格式错误，直接返回
    if (err.error != QJsonParseError::NoError) {
        qWarning() << "JSON解析失败:" << err.errorString();
        return;
    }

    // 交给业务逻辑处理请求（菜单/订单）
    QJsonObject request = doc.object();
    handleRequest(client, request);
}

// ========== 核心：处理客户端业务请求 ==========
void MyTcpServer::handleRequest(QTcpSocket *socket, const QJsonObject &request)
{
    QString type = request["type"].toString();

    if (type == "get_menu") {
        // 客户端请求【菜单】
        // 发出信号，让界面层从数据库获取菜单并发送给客户端
        emit menuRequested();

    } else if (type == "submit_order") {
        // 客户端请求【提交订单】
        QJsonObject orderObj = request["order"].toObject();
        emit orderReceived(orderObj);  // 交给界面层保存订单到数据库

        // 把当前客户端提到列表前面，方便后续返回订单结果
        m_clients.removeOne(socket);
        m_clients.prepend(socket);

    } else {
        qWarning() << "未知请求类型:" << type;
    }
}

// ========== 客户端断开连接处理 ==========
void MyTcpServer::onClientDisconnected()
{
    QTcpSocket *client = qobject_cast<QTcpSocket*>(sender());
    if (!client) return;

    QString clientInfo = QString("%1:%2")
                             .arg(client->peerAddress().toString())
                             .arg(client->peerPort());

    // 从列表移除并释放资源
    m_clients.removeOne(client);
    client->deleteLater();

    emit clientDisconnected(clientInfo);
    qDebug() << "客户端已断开:" << clientInfo;
}

// ========== 设置菜单数据（从数据库获取后传入） ==========
void MyTcpServer::setMenuData(const QJsonArray &menuData)
{
    m_menuData = menuData;
}

// ========== 向客户端发送订单处理结果（成功/失败）==========
void MyTcpServer::sendOrderResult(QTcpSocket *socket, bool success, int orderId, const QString &msg)
{
    QJsonObject response;
    response["type"]      = "order_result";   // 消息类型：订单结果
    response["success"]   = success;         // 是否成功
    response["order_id"]  = orderId;         // 订单号
    response["msg"]       = msg;             // 提示信息

    QJsonDocument doc(response);
    // 如果客户端还在线，发送数据
    if (socket && socket->state() == QAbstractSocket::ConnectedState) {
        socket->write(doc.toJson(QJsonDocument::Compact));
        socket->flush();
    }
}
