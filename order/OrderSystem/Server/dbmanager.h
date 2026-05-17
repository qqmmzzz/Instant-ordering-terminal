#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDateTime>
#include <QDebug>

class DbManager : public QObject
{
    Q_OBJECT

public:
    explicit DbManager(const QString &dbPath, QObject *parent = nullptr);
    ~DbManager();

    bool initDatabase();

    // 用户管理
    bool registerUser(const QString &username, const QString &password);
    bool loginUser(const QString &username, const QString &password);
    bool isUserExists(const QString &username);

    // 菜品管理
    QJsonArray getMenuJson();
    QJsonArray getAllDishesJson();
    bool addDish(const QString &dishName, double price, int stock,
                 const QString &description, const QString &imagePath, int status = 1);
    bool updateDish(int dishId, const QString &dishName, double price,
                    int stock, const QString &description,
                    const QString &imagePath, int status);
    bool deleteDish(int dishId);

    // 订单管理
    int saveOrder(const QJsonObject &orderObj);
    QJsonArray getOrdersJson();
    bool updateDishStock(int dishId, int soldCount);

private:
    QSqlDatabase m_db;
    QString m_dbPath;

    bool createTables();
    bool insertTestData();
    bool isTableEmpty(const QString &tableName);
    bool migrateDatabase();  // 数据库迁移（添加新列）
};

#endif // DBMANAGER_H
