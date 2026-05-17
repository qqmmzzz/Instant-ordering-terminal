-- ============================================
-- 点餐终端系统 数据库初始化脚本
-- 数据库类型: SQLite
-- ============================================

-- 1. 菜单表 dish（含 image_path）
DROP TABLE IF EXISTS dish;
CREATE TABLE dish (
    dish_id     INTEGER PRIMARY KEY AUTOINCREMENT,
    dish_name   VARCHAR(50)   NOT NULL,
    price       DECIMAL(10,2) NOT NULL DEFAULT 0,
    stock       INTEGER       NOT NULL DEFAULT 0,
    description VARCHAR(255)  DEFAULT '',
    image_path  VARCHAR(255)  DEFAULT '',
    status      INTEGER       NOT NULL DEFAULT 1
);

-- 2. 订单主表 orders
DROP TABLE IF EXISTS orders;
CREATE TABLE orders (
    order_id     INTEGER PRIMARY KEY AUTOINCREMENT,
    table_no     VARCHAR(20)   NOT NULL,
    people_count INTEGER       NOT NULL DEFAULT 1,
    total_price  DECIMAL(10,2) NOT NULL DEFAULT 0,
    create_time  DATETIME      NOT NULL,
    status       INTEGER       NOT NULL DEFAULT 0
);

-- 3. 订单详情表 order_detail
DROP TABLE IF EXISTS order_detail;
CREATE TABLE order_detail (
    detail_id  INTEGER PRIMARY KEY AUTOINCREMENT,
    order_id   INTEGER       NOT NULL,
    dish_id    INTEGER       NOT NULL,
    dish_name  VARCHAR(50)   NOT NULL,
    price      DECIMAL(10,2) NOT NULL,
    count      INTEGER       NOT NULL DEFAULT 1,
    subtotal   DECIMAL(10,2) NOT NULL,
    FOREIGN KEY (order_id) REFERENCES orders(order_id),
    FOREIGN KEY (dish_id)  REFERENCES dish(dish_id)
);

-- 4. 用户表 user
DROP TABLE IF EXISTS user;
CREATE TABLE user (
    user_id   INTEGER PRIMARY KEY AUTOINCREMENT,
    username  VARCHAR(50)  NOT NULL UNIQUE,
    password  VARCHAR(255) NOT NULL,
    create_time DATETIME   NOT NULL
);

-- 测试菜单数据
INSERT INTO dish (dish_name, price, stock, description, status) VALUES
('宫保鸡丁',   28.00, 50, '经典川菜，花生鸡丁',     1),
('鱼香肉丝',   26.00, 40, '甜酸微辣，下饭首选',     1),
('麻婆豆腐',   22.00, 35, '麻辣鲜香，嫩滑入味',     1),
('红烧肉',     38.00, 30, '肥而不腻，入口即化',     1),
('清蒸鲈鱼',   48.00, 20, '鲜嫩清甜，原汁原味',     1),
('糖醋排骨',   36.00, 25, '酸甜可口，外酥里嫩',     1),
('水煮牛肉',   42.00, 20, '麻辣鲜香，肉质嫩滑',     1),
('蛋炒饭',     15.00, 80, '粒粒分明，蛋香四溢',     1),
('米饭',        3.00, 200, '精选东北大米',           1),
('酸辣汤',     18.00, 45, '酸辣开胃，暖身暖胃',     1),
('紫菜蛋花汤', 12.00, 50, '清淡鲜美，营养丰富',     1),
('可乐',        5.00, 100, '冰镇可口可乐',           1),
('雪碧',        5.00, 100, '冰镇雪碧',               1),
('啤酒',        8.00, 60,  '青岛啤酒',               1);
