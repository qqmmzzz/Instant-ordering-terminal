#include "dbmanager.h"
#include <QCryptographicHash>
#include <QDir>
#include <QFile>

// 构造函数：初始化 SQLite 数据库连接
// dbPath：数据库文件存放路径
DbManager::DbManager(const QString &dbPath, QObject *parent)
    : QObject(parent)
    , m_dbPath(dbPath) // 保存数据库文件路径
{
    // 添加 SQLite 数据库驱动
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    // 设置数据库文件名（路径）
    m_db.setDatabaseName(m_dbPath);
}

// 析构函数：关闭数据库连接
DbManager::~DbManager()
{
    if (m_db.isOpen()) // 如果数据库是打开的
        m_db.close();  // 关闭连接
}

// ========== 初始化数据库（总入口）==========
bool DbManager::initDatabase()
{
    // 1. 尝试打开数据库文件
    if (!m_db.open())
    {
        qCritical() << "数据库打开失败:" << m_db.lastError().text();
        return false;
    }

    // 2. 创建所需的四张表（用户、菜品、订单、订单详情）
    if (!createTables()) return false;

    // 3. 数据库迁移（兼容旧版本，新增字段）
    if (!migrateDatabase()) return false;

    // 4. 如果菜品表为空，插入默认的测试菜品和管理员账号
    if (isTableEmpty("dish"))
    {
        if (!insertTestData()) return false;
        qDebug() << "测试数据插入成功";
    }

    // 5. 创建 images 文件夹，用于存放菜品图片
    QDir dir;
    if (!dir.exists("images")) dir.mkdir("images");

    qDebug() << "数据库初始化成功";
    return true;
}

// ========== 创建四张核心数据表 ==========
bool DbManager::createTables()
{
    QSqlQuery query; // 执行 SQL 语句的对象

    // -------------------- 1. 用户表 --------------------
    // 存储：管理员/用户账号、密码（MD5加密）、创建时间
    if (!query.exec(R"(
        CREATE TABLE IF NOT EXISTS user (
            user_id     INTEGER PRIMARY KEY AUTOINCREMENT,  -- 用户ID，自增主键
            username    VARCHAR(50)  NOT NULL UNIQUE,       -- 用户名，唯一
            password    VARCHAR(255) NOT NULL,               -- 密码（MD5加密后）
            create_time DATETIME     NOT NULL                -- 创建时间
        );
    )"))
    {
        qCritical() << "创建user表失败:" << query.lastError().text();
        return false;
    }

    // -------------------- 2. 菜品表 --------------------
    // 存储：所有菜品信息、价格、库存、图片路径、上下架状态
    if (!query.exec(R"(
        CREATE TABLE IF NOT EXISTS dish (
            dish_id     INTEGER PRIMARY KEY AUTOINCREMENT,  -- 菜品ID
            dish_name   VARCHAR(50)  NOT NULL,               -- 菜名
            price       DECIMAL(10,2) NOT NULL DEFAULT 0,    -- 单价
            stock       INTEGER      NOT NULL DEFAULT 0,    -- 库存
            description VARCHAR(255) DEFAULT '',            -- 菜品描述
            image_path  VARCHAR(255) DEFAULT '',            -- 菜品图片路径
            status      INTEGER      NOT NULL DEFAULT 1     -- 状态：1=上架，0=下架
        );
    )")) {
        qCritical() << "创建dish表失败:" << query.lastError().text();
        return false;
    }

    // -------------------- 3. 订单主表 --------------------
    // 存储：订单总信息（桌号、人数、总价、时间、状态）
    if (!query.exec(R"(
        CREATE TABLE IF NOT EXISTS orders (
            order_id     INTEGER PRIMARY KEY AUTOINCREMENT,  -- 订单ID
            table_no     VARCHAR(20)  NOT NULL,              -- 桌号
            people_count INTEGER      NOT NULL DEFAULT 1,    -- 就餐人数
            total_price  DECIMAL(10,2) NOT NULL DEFAULT 0,    -- 订单总价
            create_time  DATETIME     NOT NULL,               -- 下单时间
            status       INTEGER      NOT NULL DEFAULT 0      -- 状态：0=已下单，1=已完成
        );
    )")) {
        qCritical() << "创建orders表失败:" << query.lastError().text();
        return false;
    }

    // -------------------- 4. 订单详情表 --------------------
    // 存储：某一个订单里具体买了哪些菜（关联订单ID）
    if (!query.exec(R"(
        CREATE TABLE IF NOT EXISTS order_detail (
            detail_id  INTEGER PRIMARY KEY AUTOINCREMENT,   -- 详情ID
            order_id   INTEGER       NOT NULL,               -- 所属订单ID
            dish_id    INTEGER       NOT NULL,               -- 菜品ID
            dish_name  VARCHAR(50)   NOT NULL,               -- 菜品名（快照）
            price      DECIMAL(10,2) NOT NULL,               -- 下单时的单价
            count      INTEGER       NOT NULL DEFAULT 1,     -- 购买数量
            subtotal   DECIMAL(10,2) NOT NULL                -- 小计：单价×数量
        );
    )")) {
        qCritical() << "创建order_detail表失败:" << query.lastError().text();
        return false;
    }

    return true;
}

// ========== 数据库迁移：兼容旧版本，自动添加新字段 ==========
bool DbManager::migrateDatabase()
{
    QSqlQuery query;
    // 如果旧版本的 dish 表没有 image_path 列，就自动添加
    // 即使列已存在，执行失败也不影响，所以不判断返回值
    query.exec("ALTER TABLE dish ADD COLUMN image_path VARCHAR(255) DEFAULT ''");
    return true;
}

// ========== 插入测试数据（初始化用）==========
bool DbManager::insertTestData()
{
    QSqlQuery query;

    // -------------------- 1. 插入默认管理员账号 --------------------
    // 密码：admin123，使用 MD5 加密存储
    QString defaultPwd = QString(QCryptographicHash::hash(
        QString("admin123").toUtf8(), QCryptographicHash::Md5).toHex());
    query.prepare("INSERT INTO user (username, password, create_time) VALUES (?, ?, ?)");
    query.addBindValue("admin");
    query.addBindValue(defaultPwd);
    query.addBindValue(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    if (!query.exec()) {
        qWarning() << "插入默认用户失败:" << query.lastError().text();
    }

    // -------------------- 2. 插入14道测试菜品 --------------------
    QStringList names   = {"宫保鸡丁","鱼香肉丝","麻婆豆腐","红烧肉","清蒸鲈鱼",
                           "糖醋排骨","水煮牛肉","蛋炒饭","米饭","酸辣汤",
                           "紫菜蛋花汤","可乐","雪碧","啤酒"};
    QList<double> prices = {28,26,22,38,48,36,42,15,3,18,12,5,5,8};
    QList<int> stocks    = {50,40,35,30,20,25,20,80,200,45,50,100,100,60};
    QStringList descs    = {"经典川菜，花生鸡丁","甜酸微辣，下饭首选","麻辣鲜香，嫩滑入味",
                           "肥而不腻，入口即化","鲜嫩清甜，原汁原味","酸甜可口，外酥里嫩",
                           "麻辣鲜香，肉质嫩滑","粒粒分明，蛋香四溢","精选东北大米",
                           "酸辣开胃，暖身暖胃","清淡鲜美，营养丰富","冰镇可口可乐",
                           "冰镇雪碧","青岛啤酒"};

    // 循环插入
    for (int i = 0; i < names.size(); ++i) {
        query.prepare("INSERT INTO dish (dish_name, price, stock, description, image_path, status) "
                      "VALUES (?, ?, ?, ?, '', 1)");
        query.addBindValue(names[i]);
        query.addBindValue(prices[i]);
        query.addBindValue(stocks[i]);
        query.addBindValue(descs[i]);
        if (!query.exec()) {
            qWarning() << "插入菜品失败:" << names[i] << query.lastError().text();
        }
    }
    return true;
}

// ========== 用户注册 ==========
bool DbManager::registerUser(const QString &username, const QString &password)
{
    // 先检查用户名是否已存在
    if (isUserExists(username)) return false;

    // 密码 MD5 加密
    QString hashedPwd = QString(QCryptographicHash::hash(
        password.toUtf8(), QCryptographicHash::Md5).toHex());

    QSqlQuery query;
    query.prepare("INSERT INTO user (username, password, create_time) VALUES (?, ?, ?)");
    query.addBindValue(username);
    query.addBindValue(hashedPwd);
    query.addBindValue(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    return query.exec();
}

// ========== 用户登录验证 ==========
bool DbManager::loginUser(const QString &username, const QString &password)
{
    // 密码加密后对比
    QString hashedPwd = QString(QCryptographicHash::hash(
        password.toUtf8(), QCryptographicHash::Md5).toHex());

    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM user WHERE username = ? AND password = ?");
    query.addBindValue(username);
    query.addBindValue(hashedPwd);
    query.exec();
    if (query.next()) {
        return query.value(0).toInt() > 0; // 查询到结果 >0 表示登录成功
    }
    return false;
}

// ========== 检查用户名是否已存在 ==========
bool DbManager::isUserExists(const QString &username)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM user WHERE username = ?");
    query.addBindValue(username);
    query.exec();
    if (query.next()) return query.value(0).toInt() > 0;
    return false;
}

// ========== 获取【已上架】的菜单数据（给客户端用）==========
// 返回 JSON 数组，包含图片 base64 编码
QJsonArray DbManager::getMenuJson()
{
    QJsonArray arr;
    QSqlQuery query;
    // 只查询 status=1（上架）的菜品
    query.exec("SELECT dish_id, dish_name, price, stock, description, image_path, status "
               "FROM dish WHERE status = 1");

    while (query.next()) {
        QJsonObject obj;
        obj["dish_id"]     = query.value("dish_id").toInt();
        obj["dish_name"]   = query.value("dish_name").toString();
        obj["price"]       = query.value("price").toDouble();
        obj["stock"]       = query.value("stock").toInt();
        obj["description"] = query.value("description").toString();
        obj["image_path"]  = query.value("image_path").toString();
        obj["status"]      = query.value("status").toInt();

        // 读取图片文件，转为 Base64 字符串传给客户端
        QString imgPath = query.value("image_path").toString();
        if (!imgPath.isEmpty() && QFile::exists(imgPath)) {
            QFile imgFile(imgPath);
            if (imgFile.open(QIODevice::ReadOnly)) {
                QByteArray ba = imgFile.readAll();
                obj["image_data"] = QString(ba.toBase64()); // 图片编码
                imgFile.close();
            } else {
                obj["image_data"] = "";
            }
        } else {
            obj["image_data"] = "";
        }
        arr.append(obj);
    }
    return arr;
}

// ========== 获取【所有】菜品（给管理端用，包含下架）==========
QJsonArray DbManager::getAllDishesJson()
{
    QJsonArray arr;
    QSqlQuery query;
    query.exec("SELECT dish_id, dish_name, price, stock, description, image_path, status FROM dish");

    while (query.next()) {
        QJsonObject obj;
        obj["dish_id"]     = query.value("dish_id").toInt();
        obj["dish_name"]   = query.value("dish_name").toString();
        obj["price"]       = query.value("price").toDouble();
        obj["stock"]       = query.value("stock").toInt();
        obj["description"] = query.value("description").toString();
        obj["image_path"]  = query.value("image_path").toString();
        obj["status"]      = query.value("status").toInt();
        arr.append(obj);
    }
    return arr;
}

// ========== 管理端：添加新菜品 ==========
bool DbManager::addDish(const QString &dishName, double price, int stock,
                         const QString &description, const QString &imagePath, int status)
{
    QSqlQuery query;
    query.prepare("INSERT INTO dish (dish_name, price, stock, description, image_path, status) "
                  "VALUES (?, ?, ?, ?, ?, ?)");
    query.addBindValue(dishName);
    query.addBindValue(price);
    query.addBindValue(stock);
    query.addBindValue(description);
    query.addBindValue(imagePath);
    query.addBindValue(status);

    if (!query.exec()) {
        qWarning() << "添加菜品失败:" << query.lastError().text();
        return false;
    }
    qDebug() << "添加菜品成功:" << dishName;
    return true;
}

// ========== 管理端：修改菜品信息 ==========
bool DbManager::updateDish(int dishId, const QString &dishName, double price,
                            int stock, const QString &description,
                            const QString &imagePath, int status)
{
    QSqlQuery query;
    query.prepare("UPDATE dish SET dish_name=?, price=?, stock=?, description=?, "
                  "image_path=?, status=? WHERE dish_id=?");
    query.addBindValue(dishName);
    query.addBindValue(price);
    query.addBindValue(stock);
    query.addBindValue(description);
    query.addBindValue(imagePath);
    query.addBindValue(status);
    query.addBindValue(dishId);

    if (!query.exec()) {
        qWarning() << "修改菜品失败:" << query.lastError().text();
        return false;
    }
    return true;
}

// ========== 管理端：删除菜品 ==========
bool DbManager::deleteDish(int dishId)
{
    QSqlQuery query;
    query.prepare("DELETE FROM dish WHERE dish_id = ?");
    query.addBindValue(dishId);
    return query.exec();
}

// ========== 保存订单（核心！事务保证安全）==========
// 传入：客户端发来的订单 JSON
// 返回：生成的订单 ID
int DbManager::saveOrder(const QJsonObject &orderObj)
{
    // 开启数据库事务：要么全部成功，要么全部失败
    m_db.transaction();

    // -------------------- 1. 插入订单主表 --------------------
    QSqlQuery query;
    query.prepare("INSERT INTO orders (table_no, people_count, total_price, create_time, status) "
                  "VALUES (?, ?, ?, ?, 0)");
    query.addBindValue(orderObj["table_no"].toString());
    query.addBindValue(orderObj["people_count"].toInt());
    query.addBindValue(orderObj["total_price"].toDouble());
    query.addBindValue(orderObj["create_time"].toString());

    if (!query.exec()) {
        qWarning() << "插入订单主表失败:" << query.lastError().text();
        m_db.rollback(); // 回滚事务
        return -1;
    }

    // 获取刚生成的订单 ID
    int orderId = query.lastInsertId().toInt();
    QJsonArray items = orderObj["items"].toArray();

    // -------------------- 2. 循环插入订单详情 --------------------
    for (const QJsonValue &val : items) {
        QJsonObject item = val.toObject();
        QSqlQuery detailQuery;
        detailQuery.prepare("INSERT INTO order_detail (order_id, dish_id, dish_name, price, count, subtotal) "
                            "VALUES (?, ?, ?, ?, ?, ?)");
        detailQuery.addBindValue(orderId);
        detailQuery.addBindValue(item["dish_id"].toInt());
        detailQuery.addBindValue(item["dish_name"].toString());
        detailQuery.addBindValue(item["price"].toDouble());
        detailQuery.addBindValue(item["count"].toInt());
        detailQuery.addBindValue(item["subtotal"].toDouble());

        if (!detailQuery.exec()) {
            qWarning() << "插入订单详情失败:" << detailQuery.lastError().text();
            m_db.rollback();
            return -1;
        }

        // -------------------- 3. 扣减库存 --------------------
        updateDishStock(item["dish_id"].toInt(), item["count"].toInt());
    }

    // 所有操作成功，提交事务
    m_db.commit();
    qDebug() << "订单保存成功，订单号:" << orderId;
    return orderId;
}

// ========== 获取所有订单列表（带详情）==========
QJsonArray DbManager::getOrdersJson()
{
    QJsonArray arr;
    QSqlQuery query;
    // 查询所有订单，按 ID 倒序（最新的在最前）
    query.exec("SELECT order_id, table_no, people_count, total_price, create_time, status FROM orders "
               "ORDER BY order_id DESC");

    // 状态映射
    QMap<int, QString> statusNames = {{0,"已下单"},{1,"已完成"},{2,"已取消"}};

    while (query.next()) {
        QJsonObject obj;
        obj["order_id"]     = query.value("order_id").toInt();
        obj["table_no"]     = query.value("table_no").toString();
        obj["people_count"] = query.value("people_count").toInt();
        obj["total_price"]  = query.value("total_price").toDouble();
        obj["create_time"]  = query.value("create_time").toString();
        int st = query.value("status").toInt();
        obj["status"] = statusNames.contains(st) ? statusNames[st] : "未知";

        // 查询该订单对应的菜品详情
        QJsonArray detailArr;
        QSqlQuery detailQuery;
        detailQuery.prepare("SELECT dish_name, price, count, subtotal FROM order_detail WHERE order_id = ?");
        detailQuery.addBindValue(query.value("order_id").toInt());
        detailQuery.exec();
        while (detailQuery.next()) {
            QJsonObject d;
            d["dish_name"] = detailQuery.value("dish_name").toString();
            d["price"]     = detailQuery.value("price").toDouble();
            d["count"]     = detailQuery.value("count").toInt();
            d["subtotal"]  = detailQuery.value("subtotal").toDouble();
            detailArr.append(d);
        }
        obj["details"] = detailArr;
        arr.append(obj);
    }
    return arr;
}

// ========== 下单后扣减菜品库存 ==========
bool DbManager::updateDishStock(int dishId, int soldCount)
{
    QSqlQuery query;
    // 安全扣减：必须库存 >= 卖出数量才扣
    query.prepare("UPDATE dish SET stock = stock - ? WHERE dish_id = ? AND stock >= ?");
    query.addBindValue(soldCount);
    query.addBindValue(dishId);
    query.addBindValue(soldCount);
    if (!query.exec()) {
        qWarning() << "更新库存失败:" << query.lastError().text();
        return false;
    }
    return true;
}

// ========== 判断表是否为空（用于初始化）==========
bool DbManager::isTableEmpty(const QString &tableName)
{
    QSqlQuery query;
    query.exec(QString("SELECT COUNT(*) FROM %1").arg(tableName));
    if (query.next()) return query.value(0).toInt() == 0;
    return true;
}
