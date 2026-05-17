#include "clientwidget.h"
#include "ui_clientwidget.h"
#include <QListWidgetItem>

// 客户端主窗口构造函数
// app：应用程序对象，parent：父窗口
ClientWidget::ClientWidget(QApplication &app, QWidget *parent)
    : QWidget(parent)          // 继承QWidget
    , ui(new Ui::ClientWidget) // 初始化UI对象
    // 所有子对象指针初始化为空
    , m_tcpClient(nullptr)
    , m_cartManager(nullptr)
    , m_timer(nullptr)
    , m_themeManager(nullptr)
    , m_numpad(nullptr)
    , m_alphaKeyboard(nullptr)
{
    ui->setupUi(this);         // 加载UI布局
    setObjectName("ClientWidget"); // 设置对象名，方便主题/样式识别

    // 支付二维码图片路径（关闭窗口/下单成功时显示）
    m_qrCodePath = "C:/Users/24282/Desktop/img/屏幕截图 2026-04-14 180322.png";

    // 主题管理器：负责背景、颜色主题切换
    m_themeManager = new ThemeManager(app, this);
    m_themeManager->setTargetWidget(this);
    m_themeManager->loadSettings(); // 加载保存的主题配置

    // 创建数字软键盘 + 字母软键盘
    m_numpad = new NumpadWidget(this);
    m_alphaKeyboard = new AlphaKeyboardWidget(this);

    initUI(); // 初始化界面、信号槽、功能逻辑
}

// 析构函数：释放资源
ClientWidget::~ClientWidget()
{
    delete m_numpad;
    delete m_alphaKeyboard;
    delete ui;
}

// 重写绘制事件：绘制背景图片
void ClientWidget::paintEvent(QPaintEvent *event)
{
    // 获取主题管理器中的背景图
    QPixmap bg = m_themeManager->backgroundPixmap();
    if (!bg.isNull()) {
        QPainter painter(this);
        painter.setRenderHint(QPainter::SmoothPixmapTransform); // 平滑缩放
        painter.drawPixmap(0, 0, width(), height(), bg);       // 铺满窗口
    }
    QWidget::paintEvent(event); // 执行父类默认绘制
}

// 窗口关闭事件：关闭前显示支付二维码
void ClientWidget::closeEvent(QCloseEvent *event)
{
    m_themeManager->saveSettings(); // 保存主题配置

    QRCodeDialog dialog(m_qrCodePath, this); // 弹出二维码支付窗口
    dialog.exec();

    event->accept(); // 允许关闭
}

// 初始化UI、功能、信号槽
void ClientWidget::initUI()
{
    setWindowTitle("即刻点餐终端 - 客户端");
    // 适配 800x480 的 6818 开发板
    resize(800, 480);
    setMinimumSize(640, 400);

    // ========== TCP客户端：与服务端通信 ==========
    m_tcpClient = new MyTcpClient(this);
    // 收到菜单 → 显示菜单
    connect(m_tcpClient, &MyTcpClient::menuReceived,
            this, &ClientWidget::onMenuReceived);
    // 收到下单结果 → 提示成功/失败
    connect(m_tcpClient, &MyTcpClient::orderResult,
            this, &ClientWidget::onOrderResult);

    // ========== 购物车管理器 ==========
    m_cartManager = new CartManager(this);
    // 购物车内容变化 → 刷新界面
    connect(m_cartManager, &CartManager::cartChanged,
            this, &ClientWidget::onCartChanged);
    // 总价变化 → 更新总价显示
    connect(m_cartManager, &CartManager::totalPriceChanged,
            this, &ClientWidget::onTotalPriceChanged);

    // ========== 定时器：实时显示当前时间 ==========
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &ClientWidget::onTimeout);
    m_timer->start(1000); // 每秒刷新一次
    onTimeout();         // 立即显示一次时间

    // ========== 创建顶部“退出”按钮 ==========
    QPushButton *btnExit = new QPushButton("退出", this);
    btnExit->setObjectName("btnExit");
    btnExit->setStyleSheet("background-color: #e74c3c; color: white; padding: 5px 12px; font-size: 12px; font-weight: bold; border-radius: 4px;");
    ui->topLayout->addWidget(btnExit);
    connect(btnExit, &QPushButton::clicked, this, &ClientWidget::onBtnExit);

    // ========== 绑定按钮点击事件 ==========
    connect(ui->btnConnect, &QPushButton::clicked, this, &ClientWidget::onBtnConnect);       // 连接服务器
    connect(ui->btnGetMenu, &QPushButton::clicked, this, &ClientWidget::onBtnGetMenu);       // 获取菜单
    connect(ui->btnSubmitOrder, &QPushButton::clicked, this, &ClientWidget::onBtnSubmitOrder); // 提交订单
    connect(ui->btnClearCart, &QPushButton::clicked, this, &ClientWidget::onBtnClearCart);   // 清空购物车
    connect(ui->btnSelectTheme, &QPushButton::clicked, this, &ClientWidget::onBtnSelectTheme); // 选择主题
    connect(ui->btnSetBackground, &QPushButton::clicked, this, &ClientWidget::onBtnSetBackground); // 设置背景
    connect(ui->btnClearBackground, &QPushButton::clicked, this, &ClientWidget::onBtnClearBackground); // 清除背景

    // ========== IP地址输入框：点击弹出数字键盘 ==========
    connect(ui->editHost, &QLineEdit::selectionChanged, this, [this]() {
        m_alphaKeyboard->hide();
        m_numpad->setPositionAbove(false);
        m_numpad->setTargetInput(ui->editHost);
    });
    ui->editHost->installEventFilter(this); // 安装事件过滤器（点击响应）

    // ========== 桌号输入框：点击弹出字母/数字键盘 ==========
    connect(ui->editTableNo, &QLineEdit::selectionChanged, this, [this]() {
        m_numpad->hide();
        m_alphaKeyboard->setPositionAbove(true);
        m_alphaKeyboard->setTargetInput(ui->editTableNo);
    });
    ui->editTableNo->installEventFilter(this);
}

// ========== 连接服务器按钮 ==========
void ClientWidget::onBtnConnect()
{
    QString host = ui->editHost->text().trimmed();
    quint16 port = ui->spinPort->value();

    // 尝试连接
    if (m_tcpClient->connectToServer(host, port)) {
        ui->lblConnStatus->setText("连接状态：已连接");
        ui->lblConnStatus->setStyleSheet("color: green; font-weight: bold;");
    } else {
        // 连接失败：弹出详细错误提示
        QString errorMsg = QString("无法连接到服务器！\n\n"
                                   "地址: %1:%2\n"
                                   "错误信息: %3\n\n"
                                   "请检查：\n"
                                   "- 服务器是否已启动\n"
                                   "- IP地址是否正确\n"
                                   "- 端口是否正确\n"
                                   "- 网络是否通畅")
                              .arg(host).arg(port).arg(m_tcpClient->lastErrorString());
        QMessageBox::warning(this, "连接失败", errorMsg);
    }
}

// ========== 获取菜单按钮 ==========
void ClientWidget::onBtnGetMenu()
{
    if (!m_tcpClient->isConnected()) {
        QMessageBox::warning(this, "提示", "请先连接服务器！");
        return;
    }
    m_tcpClient->requestMenu(); // 向服务端请求菜单数据
}

// ========== 收到服务端发来的菜单数据 ==========
void ClientWidget::onMenuReceived(const QJsonArray &menuData)
{
    ui->listMenu->clear(); // 清空原有菜单

    // 遍历JSON菜单，创建菜品项
    for (int i = 0; i < menuData.size(); ++i) {
        QJsonObject d = menuData[i].toObject();

        // 解码base64格式的菜品图片
        QByteArray imageData;
        if (d.contains("image_data") && !d["image_data"].toString().isEmpty()) {
            imageData = QByteArray::fromBase64(d["image_data"].toString().toUtf8());
        }

        // 创建菜品显示控件
        DishItemWidget *itemWidget = new DishItemWidget(
            d["dish_id"].toInt(),
            d["dish_name"].toString(),
            d["price"].toDouble(),
            d["stock"].toInt(),
            d["description"].toString(),
            imageData,
            this
        );

        // 绑定“加入购物车”信号
        connect(itemWidget, &DishItemWidget::addToCart,
                this, &ClientWidget::onAddToCart);

        // 添加到菜单列表
        QListWidgetItem *item = new QListWidgetItem(ui->listMenu);
        item->setSizeHint(QSize(0, 68));  // 固定行高，适配小屏
        ui->listMenu->setItemWidget(item, itemWidget);
    }
}

// ========== 处理“加入购物车”请求 ==========
void ClientWidget::onAddToCart(int dishId, const QString &dishName, double price, int count)
{
    m_cartManager->addItem(dishId, dishName, price, count);
    refreshCartUI(); // 刷新购物车界面
}

// ========== 购物车数据变化，刷新UI ==========
void ClientWidget::onCartChanged()
{
    refreshCartUI();
}

// ========== 总价变化，更新显示 ==========
void ClientWidget::onTotalPriceChanged(double total)
{
    ui->lblTotalPrice->setText(QString("总价：￥%1").arg(total, 0, 'f', 2));
}

// ========== 刷新购物车列表UI ==========
void ClientWidget::refreshCartUI()
{
    ui->listCart->clear();
    QList<CartItem> items = m_cartManager->getItems();

    // 遍历购物车数据，创建购物车项
    for (const CartItem &item : items) {
        CartItemWidget *cartWidget = new CartItemWidget(
            item.dishId, item.dishName, item.price, item.count, this);

        // 绑定购物车项信号：数量修改、删除
        connect(cartWidget, &CartItemWidget::countChanged,
                this, &ClientWidget::onCartCountChanged);
        connect(cartWidget, &CartItemWidget::removeRequested,
                this, &ClientWidget::onCartRemoveRequested);

        QListWidgetItem *listItem = new QListWidgetItem(ui->listCart);
        listItem->setSizeHint(QSize(0, 36)); // 紧凑行高
        ui->listCart->setItemWidget(listItem, cartWidget);
    }

    // 更新总价
    ui->lblTotalPrice->setText(QString("总价：￥%1").arg(m_cartManager->getTotalPrice(), 0, 'f', 2));
}

// ========== 购物车中菜品数量改变 ==========
void ClientWidget::onCartCountChanged(int dishId, int newCount)
{
    m_cartManager->updateItem(dishId, newCount);
    refreshCartUI();
}

// ========== 请求删除购物车中菜品 ==========
void ClientWidget::onCartRemoveRequested(int dishId)
{
    m_cartManager->removeItem(dishId);
    refreshCartUI();
}

// ========== 清空购物车 ==========
void ClientWidget::onBtnClearCart()
{
    if (m_cartManager->getItemCount() == 0) return;
    m_cartManager->clearCart();
    refreshCartUI();
}

// ========== 提交订单 ==========
void ClientWidget::onBtnSubmitOrder()
{
    // 校验：已连接 + 购物车不为空 + 桌号已填写
    if (!m_tcpClient->isConnected()) {
        QMessageBox::warning(this, "提示", "请先连接服务器！");
        return;
    }
    if (m_cartManager->getItemCount() == 0) {
        QMessageBox::warning(this, "提示", "购物车为空！");
        return;
    }
    QString tableNo = ui->editTableNo->text().trimmed();
    if (tableNo.isEmpty()) {
        QMessageBox::warning(this, "提示", "请输入餐桌号！");
        return;
    }

    // 组装订单JSON数据
    QJsonObject orderObj;
    orderObj["table_no"]     = tableNo;               // 桌号
    orderObj["people_count"] = ui->spinPeople->value(); // 就餐人数
    orderObj["total_price"]  = m_cartManager->getTotalPrice(); // 总价
    orderObj["create_time"]  = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"); // 下单时间
    orderObj["items"]        = m_cartManager->toJsonArray(); // 菜品列表

    m_tcpClient->submitOrder(orderObj); // 发送订单
}

// ========== 收到服务端返回的下单结果 ==========
void ClientWidget::onOrderResult(bool success, int orderId, const QString &msg)
{
    if (success) {
        // 下单成功：显示支付二维码
        QRCodeDialog dialog(m_qrCodePath, this);
        dialog.exec();
        m_cartManager->clearCart();    // 清空购物车
        ui->editTableNo->clear();      // 清空桌号
    } else {
        QMessageBox::critical(this, "下单失败", msg);
    }
}

// ========== 打开主题选择窗口 ==========
void ClientWidget::onBtnSelectTheme()
{
    // 主题选择对话框
    ThemeColorDialog dialog(
        m_themeManager->getThemeNames(),
        QList<QColor>() << QColor("#ffffff") << QColor("#1e1e2e") << QColor("#1a3a5c")
                        << QColor("#1a3c2a") << QColor("#fff0f5") << QColor("#3c2a1a")
                        << QColor("#2a1a3c") << QColor("#3c2e20") << QColor("#1a3c3c")
                        << QColor("#3c1a2a") << QColor("#f0faf5") << QColor("#3c3520"),
        m_themeManager->currentThemeIndex(),
        this
    );

    // 选择主题后立即应用
    connect(&dialog, &ThemeColorDialog::themeSelected, this, [this](int index) {
        m_themeManager->applyTheme(index);
        update(); // 触发重绘，刷新界面颜色
    });

    dialog.exec();
}

// ========== 设置自定义背景图片 ==========
void ClientWidget::onBtnSetBackground()
{
    QString path = QFileDialog::getOpenFileName(this, "选择背景图片\n建议尺寸：800x480", QString(),
        "图片文件 (*.png *.jpg *.jpeg *.bmp)");
    if (!path.isEmpty()) {
        m_themeManager->setBackgroundPath(path);
        update(); // 重绘背景
    }
}

// ========== 清除背景图片 ==========
void ClientWidget::onBtnClearBackground()
{
    m_themeManager->clearBackground();
    update();
}

// ========== 定时器每秒执行：更新时间 ==========
void ClientWidget::onTimeout()
{
    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    ui->lblTime->setText(currentTime);
}

// ========== 退出按钮：保存主题并关闭窗口 ==========
void ClientWidget::onBtnExit()
{
    m_themeManager->saveSettings();
    this->close();
}

// ========== 事件过滤器：监听输入框点击，弹出软键盘 ==========
bool ClientWidget::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        if (obj == ui->editHost)
        {
            // 点击IP输入框 → 弹出数字键盘
            m_alphaKeyboard->hide();
            m_numpad->setPositionAbove(false);
            m_numpad->setTargetInput(ui->editHost);
        }
        else if (obj == ui->editTableNo)
        {
            // 点击桌号输入框 → 弹出字母键盘
            m_numpad->hide();
            m_alphaKeyboard->setPositionAbove(true);
            m_alphaKeyboard->setTargetInput(ui->editTableNo);
        }
    }
    return QWidget::eventFilter(obj, event);
}
