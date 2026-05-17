#ifndef CARTMANAGER_H
#define CARTMANAGER_H

#include <QObject>
#include <QList>
#include <QJsonObject>
#include <QJsonArray>

struct CartItem {
    int     dishId;      // 菜品编号
    QString dishName;    // 菜品名称
    double  price;       // 单价
    int     count;       // 数量
    double  subtotal;    // 小计 = price * count
};


//@brief 购物车管理类
//管理购物车中所有菜品的增删改查，自动计算总价。
//持添加菜品（重复则累加数量）、修改数量、删除菜品、清空购物车。

class CartManager : public QObject
{
    Q_OBJECT

public:
    explicit CartManager(QObject *parent = nullptr);

    /// 添加菜品到购物车（如果已存在则累加数量）
    void addItem(int dishId, const QString &dishName, double price, int count);

    /// 修改指定菜品的数量
    void updateItem(int dishId, int newCount);

    /// 删除指定菜品
    void removeItem(int dishId);

    /// 清空购物车
    void clearCart();

    /// 获取所有购物车条目
    QList<CartItem> getItems() const;

    /// 获取总价
    double getTotalPrice() const;

    /// 获取购物车条目数量
    int getItemCount() const;

    /// 将购物车内容转为 JSON 数组（用于订单提交）
    QJsonArray toJsonArray() const;

    /// 查找指定菜品在购物车中的索引，不存在返回 -1
    int findItem(int dishId) const;

signals:
    /// 购物车内容变化信号
    void cartChanged();

    /// 总价变化信号
    void totalPriceChanged(double totalPrice);

private:
    QList<CartItem> m_items;

    /// 重新计算总价
    void recalculate();
};

#endif // CARTMANAGER_H
