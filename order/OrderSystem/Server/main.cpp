#include "serverwidget.h"
#include "logindialog.h"
#include "dbmanager.h"
#include <QApplication>

// 全局数据库管理器指针，供整个程序使用
DbManager *g_dbManager = nullptr;

// 程序入口：初始化数据库 -> 登录验证 -> 进入主界面
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 初始化SQLite数据库
    g_dbManager = new DbManager("order_system.db");
    if (!g_dbManager->initDatabase()) {
        qCritical() << "数据库初始化失败，程序退出";
        delete g_dbManager;
        return -1; // 数据库初始化失败，异常退出
    }

    // 显示登录对话框，阻塞等待用户操作
    LoginDialog loginDialog;
    if (loginDialog.exec() != QDialog::Accepted) 
    {
        delete g_dbManager; // 用户取消登录，清理资源
        return 0;
    }

    // 获取登录成功的用户名
    QString currentUser = loginDialog.getUsername();

    // 登录成功，创建并显示主窗口
    ServerWidget w(currentUser, a);
    w.show();

    // 进入Qt事件循环
    int ret = a.exec();

    // 程序退出前清理全局数据库实例
    delete g_dbManager;
    g_dbManager = nullptr;

    return ret;
}
