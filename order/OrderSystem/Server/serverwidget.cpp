#include "serverwidget.h"
#include "ui_serverwidget.h"
#include <QMessageBox>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QDir>
#include <QFile>
#include <QBuffer>

// 服务端主窗口构造函数
// currentUser: 当前登录的管理员账号
ServerWidget::ServerWidget(const QString &currentUser, QApplication &app, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServerWidget)          // 加载UI界面
    , m_dbManager(nullptr)              // 数据库管理对象
    , m_tcpServer(nullptr)              // TCP服务器对象
    , m_timer(nullptr)                  // 定时器（刷新时间）
    , m_themeManager(nullptr)           // 主题管理器
    , m_currentUser(currentUser)       // 保存当前登录用户
{
    ui->setupUi(this);                  // 初始化界面
    setObjectName("ServerWidget");

    // 固定的收款二维码路径（可自行修改）
    m_qrCodePath = "C:/Users/24282/Desktop/img/屏幕截图 2026-04-14 180322.png";

    // 初始化主题管理器，支持换肤、背景图
    m_themeManager = new ThemeManager(app, this);
    m_themeManager->setTargetWidget(this);
    m_themeManager->loadSettings();

    // 初始化所有功能：数据库、服务器、按钮、表格
    initUI();
}

ServerWidget::~ServerWidget()
{
    delete ui;
}

// 绘制窗口背景图片
void ServerWidget::paintEvent(QPaintEvent *event)
{
    QPixmap bg = m_themeManager->backgroundPixmap();
    if (!bg.isNull()) {
        QPainter painter(this);
        painter.setRenderHint(QPainter::SmoothPixmapTransform);
        painter.drawPixmap(0, 0, width(), height(), bg);
    }
    QWidget::paintEvent(event);
}

// 关闭窗口时保存主题设置
void ServerWidget::closeEvent(QCloseEvent *event)
{
    m_themeManager->saveSettings();
    event->accept();
}

// 初始化界面、数据库、服务器、信号槽
void ServerWidget::initUI()
{
    // 设置窗口标题和大小
    setWindowTitle(QString("点餐终端 - 服务器端  [当前用户：%1]").arg(m_currentUser));
    resize(1000, 720);

    // 初始化数据库
    m_dbManager = new DbManager("order_system.db", this);
    if (!m_dbManager->initDatabase()) {
        QMessageBox::critical(this, "错误", "数据库初始化失败！");
    }

    // 初始化TCP服务器
    m_tcpServer = new MyTcpServer(this);
    // 绑定服务器信号：菜单请求、订单请求、客户端上下线
    connect(m_tcpServer, &MyTcpServer::menuRequested, this, &ServerWidget::onMenuRequested);
    connect(m_tcpServer, &MyTcpServer::orderReceived, this, &ServerWidget::onOrderReceived);
    connect(m_tcpServer, &MyTcpServer::clientConnected, this, &ServerWidget::onClientConnected);
    connect(m_tcpServer, &MyTcpServer::clientDisconnected, this, &ServerWidget::onClientDisconnected);

    // 定时器：每秒刷新当前时间
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &ServerWidget::onTimeout);
    m_timer->start(1000);
    onTimeout();

    // ===================== 按钮绑定点击事件 =====================
    connect(ui->btnStartServer,   &QPushButton::clicked, this, &ServerWidget::onBtnStartServer);    // 启动/停止服务
    connect(ui->btnRefreshMenu,   &QPushButton::clicked, this, &ServerWidget::onBtnRefreshMenu);    // 刷新菜单
    connect(ui->btnRefreshOrders, &QPushButton::clicked, this, &ServerWidget::onBtnRefreshOrders);  // 刷新订单
    connect(ui->btnAddDish,       &QPushButton::clicked, this, &ServerWidget::onBtnAddDish);        // 添加菜品
    connect(ui->btnDeleteDish,    &QPushButton::clicked, this, &ServerWidget::onBtnDeleteDish);     // 删除菜品
    connect(ui->btnEditDish,      &QPushButton::clicked, this, &ServerWidget::onBtnEditDish);       // 编辑菜品
    connect(ui->btnSearch,        &QPushButton::clicked, this, &ServerWidget::onBtnSearch);         // 搜索菜品
    connect(ui->btnSelectTheme,   &QPushButton::clicked, this, &ServerWidget::onBtnSelectTheme);    // 选择主题
    connect(ui->btnSetBackground,&QPushButton::clicked, this, &ServerWidget::onBtnSetBackground);  // 设置背景
    connect(ui->btnClearBackground,&QPushButton::clicked,this,&ServerWidget::onBtnClearBackground);//清除背景

    // 启动时加载菜单和订单表格
    refreshMenuTable();
    refreshOrderTable();
}

// ===================== 每秒刷新当前时间 =====================
void ServerWidget::onTimeout()
{
    ui->lblTime->setText("当前时间：" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
}

// ===================== 启动 / 停止服务器 =====================
void ServerWidget::onBtnStartServer()
{
    if (m_tcpServer->isListening()) {
        // 停止服务器
        m_tcpServer->stop();
        ui->lblStatus->setText("服务器状态：已停止");
        ui->lblStatus->setStyleSheet("color: red; font-weight: bold;");
        ui->btnStartServer->setText("启动服务器");
    } else {
        // 启动服务器，使用界面设置的端口
        quint16 port = ui->spinPort->value();
        if (m_tcpServer->start(port)) {
            ui->lblStatus->setText(QString("服务器状态：运行中（端口%1）").arg(port));
            ui->lblStatus->setStyleSheet("color: green; font-weight: bold;");
            ui->btnStartServer->setText("停止服务器");
            ui->txtLog->append(QString("[%1] 服务器启动，端口：%2")
                               .arg(QDateTime::currentDateTime().toString("hh:mm:ss")).arg(port));
        } else {
            QMessageBox::critical(this, "错误", "服务器启动失败！");
        }
    }
}

// ===================== 客户端请求菜单：下发菜单数据 =====================
void ServerWidget::onMenuRequested()
{
    // 从数据库获取菜单
    QJsonArray menuData = m_dbManager->getMenuJson();
    m_tcpServer->setMenuData(menuData);

    // 发送给所有已连接的客户端
    QList<QTcpSocket*> clients = m_tcpServer->getClientList();
    for (QTcpSocket *client : clients) {
        QJsonObject response;
        response["type"] = "menu_data";
        response["data"] = menuData;
        QJsonDocument doc(response);
        if (client->state() == QAbstractSocket::ConnectedState) {
            client->write(doc.toJson(QJsonDocument::Compact));
            client->flush();
        }
    }

    ui->txtLog->append(QString("[%1] 菜单已下发给 %2 个客户端")
                       .arg(QDateTime::currentDateTime().toString("hh:mm:ss")).arg(clients.size()));
}

// ===================== 收到客户端订单：保存到数据库 =====================
void ServerWidget::onOrderReceived(const QJsonObject &orderObj)
{
    // 保存订单，返回订单号
    int orderId = m_dbManager->saveOrder(orderObj);
    bool success = (orderId > 0);

    // 给客户端返回结果
    QList<QTcpSocket*> clients = m_tcpServer->getClientList();
    if (!clients.isEmpty()) {
        m_tcpServer->sendOrderResult(clients.first(), success, orderId,
            success ? QString("订单保存成功，订单号：%1").arg(orderId) : "订单保存失败");
    }

    // 刷新界面
    refreshMenuTable();
    refreshOrderTable();

    // 日志记录
    ui->txtLog->append(QString("[%1] 收到订单：%2，餐桌：%3，总价：￥%4")
                       .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
                       .arg(success ? "成功" : "失败")
                       .arg(orderObj["table_no"].toString())
                       .arg(orderObj["total_price"].toDouble(), 0, 'f', 2));
}

// 客户端上线日志
void ServerWidget::onClientConnected(const QString &info)
{
    ui->txtLog->append(QString("[%1] 客户端连接：%2")
                       .arg(QDateTime::currentDateTime().toString("hh:mm:ss")).arg(info));
}

// 客户端下线日志
void ServerWidget::onClientDisconnected(const QString &info)
{
    ui->txtLog->append(QString("[%1] 客户端断开：%2")
                       .arg(QDateTime::currentDateTime().toString("hh:mm:ss")).arg(info));
}

// ===================== 添加菜品 =====================
void ServerWidget::onBtnAddDish()
{
    AddDishDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString name     = dialog.getDishName();
        double  price    = dialog.getPrice();
        int     stock    = dialog.getStock();
        QString desc     = dialog.getDescription();
        QString imgPath  = dialog.getImagePath();
        int     status   = dialog.getStatus();

        if (m_dbManager->addDish(name, price, stock, desc, imgPath, status)) {
            QMessageBox::information(this, "成功",
                QString("菜品\"%1\"添加成功！\n单价：￥%2\n库存：%3\n图片：%4")
                    .arg(name).arg(price, 0, 'f', 2).arg(stock)
                    .arg(imgPath.isEmpty() ? "无" : imgPath));
            refreshMenuTable();
        } else {
            QMessageBox::critical(this, "失败", "菜品添加失败，请检查输入信息！");
        }
    }
}

// ===================== 删除菜品 =====================
void ServerWidget::onBtnDeleteDish()
{
    QModelIndexList selected = ui->tableMenu->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "提示", "请先选中要删除的菜品！");
        return;
    }

    int row = selected.first().row();
    int dishId = ui->tableMenu->item(row, 0)->text().toInt();
    QString dishName = ui->tableMenu->item(row, 2)->text();

    if (QMessageBox::question(this, "确认删除",
            QString("确定要删除菜品 \"%1\" 吗？").arg(dishName),
            QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        if (m_dbManager->deleteDish(dishId)) {
            QMessageBox::information(this, "成功", "菜品删除成功！");
            refreshMenuTable();
            ui->txtLog->append(QString("[%1] 删除菜品：%2").arg(QDateTime::currentDateTime().toString("hh:mm:ss")).arg(dishName));
        } else {
            QMessageBox::critical(this, "失败", "菜品删除失败！");
        }
    }
}

// ===================== 编辑菜品 =====================
void ServerWidget::onBtnEditDish()
{
    QModelIndexList selected = ui->tableMenu->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "提示", "请先选中要编辑的菜品！");
        return;
    }

    int row = selected.first().row();
    int dishId = ui->tableMenu->item(row, 0)->text().toInt();

    // 从数据库获取该菜品信息
    QJsonArray dishes = m_dbManager->getAllDishesJson();
    QJsonObject dishObj;
    for (const QJsonValue &val : dishes) {
        QJsonObject d = val.toObject();
        if (d["dish_id"].toInt() == dishId) {
            dishObj = d;
            break;
        }
    }

    if (dishObj.isEmpty()) {
        QMessageBox::warning(this, "提示", "未找到该菜品信息！");
        return;
    }

    // 打开编辑对话框
    AddDishDialog dialog(this);
    QMetaObject::invokeMethod(&dialog, "setDishInfo",
        Q_ARG(int, dishId),
        Q_ARG(QString, dishObj["dish_name"].toString()),
        Q_ARG(double, dishObj["price"].toDouble()),
        Q_ARG(int, dishObj["stock"].toInt()),
        Q_ARG(QString, dishObj["description"].toString()),
        Q_ARG(QString, dishObj["image_path"].toString()),
        Q_ARG(int, dishObj["status"].toInt()));

    if (dialog.exec() == QDialog::Accepted) {
        QString name     = dialog.getDishName();
        double  price    = dialog.getPrice();
        int     stock    = dialog.getStock();
        QString desc     = dialog.getDescription();
        QString imgPath  = dialog.getImagePath();
        int     status   = dialog.getStatus();

        if (m_dbManager->updateDish(dishId, name, price, stock, desc, imgPath, status)) {
            QMessageBox::information(this, "成功", "菜品信息更新成功！");
            refreshMenuTable();
            ui->txtLog->append(QString("[%1] 修改菜品：%2").arg(QDateTime::currentDateTime().toString("hh:mm:ss")).arg(name));
        } else {
            QMessageBox::critical(this, "失败", "菜品信息更新失败！");
        }
    }
}

// ===================== 搜索菜品 =====================
void ServerWidget::onBtnSearch()
{
    QString keyword = ui->editSearch->text().trimmed();
    if (keyword.isEmpty()) {
        refreshMenuTable();
        return;
    }

    QJsonArray dishes = m_dbManager->getAllDishesJson();
    QJsonArray filtered;

    // 按菜名、描述模糊搜索
    for (const QJsonValue &val : dishes) {
        QJsonObject d = val.toObject();
        QString name = d["dish_name"].toString();
        QString desc = d["description"].toString();

        if (name.contains(keyword, Qt::CaseInsensitive) ||
            desc.contains(keyword, Qt::CaseInsensitive)) {
            filtered.append(d);
        }
    }

    // 显示搜索结果
    ui->tableMenu->setRowCount(filtered.size());
    ui->tableMenu->setColumnCount(7);
    ui->tableMenu->setHorizontalHeaderLabels(
        QStringList() << "编号" << "图片" << "菜名" << "单价" << "库存" << "描述" << "状态");

    for (int i = 0; i < filtered.size(); ++i) {
        QJsonObject d = filtered[i].toObject();
        ui->tableMenu->setItem(i, 0, new QTableWidgetItem(QString::number(d["dish_id"].toInt())));
        ui->tableMenu->setItem(i, 2, new QTableWidgetItem(d["dish_name"].toString()));
        ui->tableMenu->setItem(i, 3, new QTableWidgetItem(QString("￥%1").arg(d["price"].toDouble(), 0, 'f', 2)));
        ui->tableMenu->setItem(i, 4, new QTableWidgetItem(QString::number(d["stock"].toInt())));
        ui->tableMenu->setItem(i, 5, new QTableWidgetItem(d["description"].toString()));
        ui->tableMenu->setItem(i, 6, new QTableWidgetItem(d["status"].toInt() == 1 ? "上架" : "下架"));

        // 显示菜品图片
        QLabel *imgLabel = new QLabel();
        imgLabel->setAlignment(Qt::AlignCenter);
        QString imgPath = d["image_path"].toString();
        if (!imgPath.isEmpty() && QFile::exists(imgPath)) {
            QPixmap pix(imgPath);
            if (!pix.isNull()) {
                imgLabel->setPixmap(pix.scaled(48, 48, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            } else {
                imgLabel->setText("无图");
            }
        } else {
            imgLabel->setText("无图");
            imgLabel->setStyleSheet("color: #aaa; font-size: 11px;");
        }
        ui->tableMenu->setCellWidget(i, 1, imgLabel);
    }

    ui->tableMenu->setColumnWidth(0, 45);
    ui->tableMenu->setColumnWidth(1, 55);
    ui->tableMenu->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->tableMenu->setColumnWidth(3, 65);
    ui->tableMenu->setColumnWidth(4, 45);
    ui->tableMenu->setColumnWidth(6, 45);
}

// ===================== 选择主题颜色 =====================
void ServerWidget::onBtnSelectTheme()
{
    // 主题名称
    QStringList names = m_themeManager->getThemeNames();
    // 12种主题预览色
    QList<QColor> colors;
    colors << QColor("#ffffff") << QColor("#1e1e2e") << QColor("#1a3a5c")
           << QColor("#1a3c2a") << QColor("#fff0f5") << QColor("#3c2a1a")
           << QColor("#2a1a3c") << QColor("#3c2e20") << QColor("#1a3c3c")
           << QColor("#3c1a2a") << QColor("#f0faf5") << QColor("#3c3520");

    ThemeColorDialog dialog(names, colors, m_themeManager->currentThemeIndex(), this);
    connect(&dialog, &ThemeColorDialog::themeSelected, this, [this](int index) {
        m_themeManager->applyTheme(index);
        update();
    });
    dialog.exec();
}

// ===================== 设置背景图片 =====================
void ServerWidget::onBtnSetBackground()
{
    QString path = QFileDialog::getOpenFileName(this,
        "选择背景图片（建议分辨率与屏幕一致）", QString(),
        "图片文件 (*.png *.jpg *.jpeg *.bmp)");

    if (path.isEmpty()) return;

    QPixmap pixmap(path);
    if (pixmap.isNull()) {
        QMessageBox::warning(this, "提示", "无法加载该图片，请检查文件格式！");
        return;
    }

    m_themeManager->setBackgroundPath(path);
    update();

    QMessageBox::information(this, "背景已设置",
        QString("背景图片已应用！\n建议图片尺寸：与屏幕分辨率一致"));
}

// ===================== 清除背景 =====================
void ServerWidget::onBtnClearBackground()
{
    m_themeManager->clearBackground();
    update();
}

// ===================== 刷新菜单表格 =====================
void ServerWidget::refreshMenuTable()
{
    QJsonArray dishes = m_dbManager->getAllDishesJson();

    ui->tableMenu->setRowCount(dishes.size());
    ui->tableMenu->setColumnCount(7);
    ui->tableMenu->setHorizontalHeaderLabels(
        QStringList() << "编号" << "图片" << "菜名" << "单价" << "库存" << "描述" << "状态");

    for (int i = 0; i < dishes.size(); ++i) {
        QJsonObject d = dishes[i].toObject();
        ui->tableMenu->setItem(i, 0, new QTableWidgetItem(QString::number(d["dish_id"].toInt())));
        ui->tableMenu->setItem(i, 2, new QTableWidgetItem(d["dish_name"].toString()));
        ui->tableMenu->setItem(i, 3, new QTableWidgetItem(QString("￥%1").arg(d["price"].toDouble(), 0, 'f', 2)));
        ui->tableMenu->setItem(i, 4, new QTableWidgetItem(QString::number(d["stock"].toInt())));
        ui->tableMenu->setItem(i, 5, new QTableWidgetItem(d["description"].toString()));
        ui->tableMenu->setItem(i, 6, new QTableWidgetItem(d["status"].toInt() == 1 ? "上架" : "下架"));

        // 显示菜品图片
        QLabel *imgLabel = new QLabel();
        imgLabel->setAlignment(Qt::AlignCenter);
        QString imgPath = d["image_path"].toString();
        if (!imgPath.isEmpty() && QFile::exists(imgPath)) {
            QPixmap pix(imgPath);
            if (!pix.isNull()) {
                imgLabel->setPixmap(pix.scaled(48, 48, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            } else {
                imgLabel->setText("无图");
            }
        } else {
            imgLabel->setText("无图");
            imgLabel->setStyleSheet("color: #aaa; font-size: 11px;");
        }
        ui->tableMenu->setCellWidget(i, 1, imgLabel);
    }

    // 列宽设置
    ui->tableMenu->setColumnWidth(0, 45);
    ui->tableMenu->setColumnWidth(1, 55);
    ui->tableMenu->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->tableMenu->setColumnWidth(3, 65);
    ui->tableMenu->setColumnWidth(4, 45);
    ui->tableMenu->setColumnWidth(6, 45);
}

// ===================== 刷新订单表格 =====================
void ServerWidget::refreshOrderTable()
{
    QJsonArray orders = m_dbManager->getOrdersJson();
    ui->tableOrders->setRowCount(orders.size());
    ui->tableOrders->setColumnCount(6);
    ui->tableOrders->setHorizontalHeaderLabels(
        QStringList() << "订单号" << "餐桌号" << "人数" << "总价" << "下单时间" << "状态");

    for (int i = 0; i < orders.size(); ++i) {
        QJsonObject o = orders[i].toObject();
        ui->tableOrders->setItem(i, 0, new QTableWidgetItem(QString::number(o["order_id"].toInt())));
        ui->tableOrders->setItem(i, 1, new QTableWidgetItem(o["table_no"].toString()));
        ui->tableOrders->setItem(i, 2, new QTableWidgetItem(QString::number(o["people_count"].toInt())));
        ui->tableOrders->setItem(i, 3, new QTableWidgetItem(QString("￥%1").arg(o["total_price"].toDouble(), 0, 'f', 2)));
        ui->tableOrders->setItem(i, 4, new QTableWidgetItem(o["create_time"].toString()));
        ui->tableOrders->setItem(i, 5, new QTableWidgetItem(o["status"].toString()));
    }
    ui->tableOrders->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

// 手动刷新菜单
void ServerWidget::onBtnRefreshMenu()
{
    refreshMenuTable();
}

// 手动刷新订单
void ServerWidget::onBtnRefreshOrders()
{
    refreshOrderTable();
}
