#include "logindialog.h"
#include "dbmanager.h"

// 构造函数：构建登录/注册双页面堆栈布局
LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent), m_stackedWidget(new QStackedWidget(this)) // QStackedWidget切换登录/注册页
{
    setWindowTitle("即刻点餐终端 - 管理员登录");
    setFixedSize(420, 380);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    setupLoginPage(); // 构建登录页面
    setupRegisterPage(); // 构建注册页面

    // 主垂直布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    // 顶部品牌标题栏
    QLabel *lblTitle = new QLabel("即刻点餐终端管理系统");
    lblTitle->setAlignment(Qt::AlignCenter);
    lblTitle->setStyleSheet(
        "font-size: 22px; font-weight: bold; color: #2c3e50;"
        "padding: 20px; background-color: #ecf0f1;"
    );
    mainLayout->addWidget(lblTitle);

    mainLayout->addWidget(m_stackedWidget, 1); // 堆栈控件占剩余空间
}

QString LoginDialog::getUsername() const
{
    return m_username;
}

// ========== 构建登录页面 ==========
void LoginDialog::setupLoginPage()
{
    m_loginPage = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(m_loginPage);
    layout->setContentsMargins(40, 20, 40, 20);
    layout->setSpacing(15);

    // 登录标题
    QLabel *lblIcon = new QLabel("管理员登录");
    lblIcon->setAlignment(Qt::AlignCenter);
    lblIcon->setStyleSheet("font-size: 18px; font-weight: bold; color: #34495e; padding: 10px;");
    layout->addWidget(lblIcon);

    // 表单布局：用户名 + 密码
    QFormLayout *formLayout = new QFormLayout();
    formLayout->setSpacing(12);

    // 用户名输入框
    m_editLoginUser = new QLineEdit();
    m_editLoginUser->setPlaceholderText("请输入用户名");
    m_editLoginUser->setMinimumHeight(36);
    m_editLoginUser->setStyleSheet(
        "QLineEdit { padding: 6px 10px; border: 1px solid #bdc3c7; "
        "border-radius: 4px; font-size: 14px; }"
        "QLineEdit:focus { border: 2px solid #3498db; }");
    formLayout->addRow("用户名：", m_editLoginUser);

    // 密码输入框（密文显示）
    m_editLoginPwd = new QLineEdit();
    m_editLoginPwd->setPlaceholderText("请输入密码");
    m_editLoginPwd->setEchoMode(QLineEdit::Password); // 密码掩码
    m_editLoginPwd->setMinimumHeight(36);
    m_editLoginPwd->setStyleSheet(m_editLoginUser->styleSheet());
    formLayout->addRow("密  码：", m_editLoginPwd);

    layout->addLayout(formLayout);

    // 登录按钮（蓝色主题）
    m_btnLogin = new QPushButton("登  录");
    m_btnLogin->setMinimumHeight(42);
    m_btnLogin->setStyleSheet(
        "QPushButton {"
        "   background-color: #3498db; color: white; font-size: 16px;"
        "   font-weight: bold; border: none; border-radius: 5px;"
        "}"
        "QPushButton:hover { background-color: #2980b9; }"
        "QPushButton:pressed { background-color: #2471a3; }");
    connect(m_btnLogin, &QPushButton::clicked, this, &LoginDialog::onBtnLogin);
    layout->addWidget(m_btnLogin);

    // 切换到注册页的链接按钮
    m_btnToRegister = new QPushButton("还没有账号？点击注册");
    m_btnToRegister->setFlat(true); // 扁平按钮，像超链接
    m_btnToRegister->setStyleSheet(
        "QPushButton { color: #3498db; border: none; font-size: 13px; }"
        "QPushButton:hover { color: #2980b9; text-decoration: underline; }");
    connect(m_btnToRegister, &QPushButton::clicked, this, &LoginDialog::onSwitchToRegister);
    layout->addWidget(m_btnToRegister, 0, Qt::AlignCenter);

    // 默认账号提示
    QLabel *lblHint = new QLabel("默认账号: admin  密码: admin123");
    lblHint->setAlignment(Qt::AlignCenter);
    lblHint->setStyleSheet("color: #95a5a6; font-size: 11px; padding-top: 5px;");
    layout->addWidget(lblHint);

    m_stackedWidget->addWidget(m_loginPage); // 添加到堆栈
}

// ========== 构建注册页面 ==========
void LoginDialog::setupRegisterPage()
{
    m_registerPage = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(m_registerPage);
    layout->setContentsMargins(40, 20, 40, 20);
    layout->setSpacing(15);

    // 注册标题
    QLabel *lblTitle = new QLabel("注册新账号");
    lblTitle->setAlignment(Qt::AlignCenter);
    lblTitle->setStyleSheet("font-size: 18px; font-weight: bold; color: #34495e; padding: 10px;");
    layout->addWidget(lblTitle);

    // 表单布局：用户名 + 密码 + 确认密码
    QFormLayout *formLayout = new QFormLayout();
    formLayout->setSpacing(12);

    m_editRegUser = new QLineEdit();
    m_editRegUser->setPlaceholderText("请输入用户名（3-20位）");
    m_editRegUser->setMinimumHeight(36);
    m_editRegUser->setStyleSheet(
        "QLineEdit { padding: 6px 10px; border: 1px solid #bdc3c7; "
        "border-radius: 4px; font-size: 14px; }"
        "QLineEdit:focus { border: 2px solid #27ae60; }");
    formLayout->addRow("用户名：", m_editRegUser);

    m_editRegPwd = new QLineEdit();
    m_editRegPwd->setPlaceholderText("请输入密码（6位以上）");
    m_editRegPwd->setEchoMode(QLineEdit::Password);
    m_editRegPwd->setMinimumHeight(36);
    m_editRegPwd->setStyleSheet(m_editRegUser->styleSheet());
    formLayout->addRow("密  码：", m_editRegPwd);

    // 确认密码输入框（用于二次验证）
    m_editRegPwdConfirm = new QLineEdit();
    m_editRegPwdConfirm->setPlaceholderText("请再次输入密码");
    m_editRegPwdConfirm->setEchoMode(QLineEdit::Password);
    m_editRegPwdConfirm->setMinimumHeight(36);
    m_editRegPwdConfirm->setStyleSheet(m_editRegUser->styleSheet());
    formLayout->addRow("确认密码：", m_editRegPwdConfirm);

    layout->addLayout(formLayout);

    // 注册按钮（绿色主题）
    m_btnRegister = new QPushButton("注  册");
    m_btnRegister->setMinimumHeight(42);
    m_btnRegister->setStyleSheet(
        "QPushButton {"
        "   background-color: #27ae60; color: white; font-size: 16px;"
        "   font-weight: bold; border: none; border-radius: 5px;"
        "}"
        "QPushButton:hover { background-color: #229954; }"
        "QPushButton:pressed { background-color: #1e8449; }");
    connect(m_btnRegister, &QPushButton::clicked, this, &LoginDialog::onBtnRegister);
    layout->addWidget(m_btnRegister);

    // 切换回登录页的链接按钮
    m_btnToLogin = new QPushButton("已有账号？点击登录");
    m_btnToLogin->setFlat(true);
    m_btnToLogin->setStyleSheet(
        "QPushButton { color: #27ae60; border: none; font-size: 13px; }"
        "QPushButton:hover { color: #229954; text-decoration: underline; }");
    connect(m_btnToLogin, &QPushButton::clicked, this, &LoginDialog::onSwitchToLogin);
    layout->addWidget(m_btnToLogin, 0, Qt::AlignCenter);

    m_stackedWidget->addWidget(m_registerPage);
}

// ========== 登录按钮处理 ==========
void LoginDialog::onBtnLogin()
{
    QString username = m_editLoginUser->text().trimmed();
    QString password = m_editLoginPwd->text();

    // 非空校验
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "提示", "用户名和密码不能为空！");
        return;
    }

    // 使用全局 DbManager 实例验证用户名密码
    extern DbManager *g_dbManager;
    if (!g_dbManager) {
        QMessageBox::critical(this, "错误", "数据库未初始化！");
        return;
    }

    if (g_dbManager->loginUser(username, password)) {
        m_username = username;
        emit loginSuccess(username); // 发射登录成功信号
        QMessageBox::information(this, "成功",
                                 QString("欢迎回来，%1！").arg(username));
        accept(); // 关闭对话框，返回 Accepted
    } else {
        QMessageBox::warning(this, "登录失败", "用户名或密码错误！");
        m_editLoginPwd->clear();
        m_editLoginPwd->setFocus(); // 聚焦密码框方便重试
    }
}

// ========== 注册按钮处理 ==========
void LoginDialog::onBtnRegister()
{
    QString username = m_editRegUser->text().trimmed();
    QString password = m_editRegPwd->text();
    QString confirm  = m_editRegPwdConfirm->text();

    // 空值校验
    if (username.isEmpty() || password.isEmpty() || confirm.isEmpty()) {
        QMessageBox::warning(this, "提示", "所有字段都必须填写！");
        return;
    }

    // 用户名长度校验：3-20位
    if (username.length() < 3 || username.length() > 20) {
        QMessageBox::warning(this, "提示", "用户名长度应为3-20位！");
        return;
    }

    // 密码长度校验：至少6位
    if (password.length() < 6) {
        QMessageBox::warning(this, "提示", "密码长度不能少于6位！");
        return;
    }

    // 两次密码一致性校验
    if (password != confirm) {
        QMessageBox::warning(this, "提示", "两次输入的密码不一致！");
        m_editRegPwdConfirm->clear();
        m_editRegPwdConfirm->setFocus();
        return;
    }

    extern DbManager *g_dbManager;
    if (!g_dbManager) {
        QMessageBox::critical(this, "错误", "数据库未初始化！");
        return;
    }

    // 调用数据库注册接口
    if (g_dbManager->registerUser(username, password)) {
        QMessageBox::information(this, "注册成功",
                                 "账号注册成功！请返回登录页面登录。");
        // 自动切换到登录页，并填入刚注册的用户名
        m_editLoginUser->setText(username);
        m_editLoginPwd->setFocus();
        onSwitchToLogin();
    } else {
        QMessageBox::warning(this, "注册失败", "该用户名已被注册，请更换用户名！");
        m_editRegUser->setFocus();
        m_editRegUser->selectAll(); // 全选方便重新输入
    }
}

// ========== 切换到注册页 ==========
void LoginDialog::onSwitchToRegister()
{
    m_stackedWidget->setCurrentWidget(m_registerPage); // 切换堆栈当前页
    m_editRegUser->setFocus();
}

// ========== 切换到登录页 ==========
void LoginDialog::onSwitchToLogin()
{
    m_stackedWidget->setCurrentWidget(m_loginPage);
    m_editLoginPwd->setFocus();
}
