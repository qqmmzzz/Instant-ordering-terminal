#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QFrame>

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);

    /// 获取登录成功的用户名
    QString getUsername() const;

signals:
    /// 登录成功信号
    void loginSuccess(const QString &username);

private slots:
    void onBtnLogin();
    void onBtnRegister();
    void onSwitchToRegister();
    void onSwitchToLogin();

private:
    QStackedWidget *m_stackedWidget;

    // 登录页控件
    QWidget    *m_loginPage;
    QLineEdit  *m_editLoginUser;
    QLineEdit  *m_editLoginPwd;
    QPushButton *m_btnLogin;
    QPushButton *m_btnToRegister;

    // 注册页控件
    QWidget    *m_registerPage;
    QLineEdit  *m_editRegUser;
    QLineEdit  *m_editRegPwd;
    QLineEdit  *m_editRegPwdConfirm;
    QPushButton *m_btnRegister;
    QPushButton *m_btnToLogin;

    QString m_username; // 登录成功的用户名

    void setupLoginPage();
    void setupRegisterPage();
};

#endif // LOGINDIALOG_H
