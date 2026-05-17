#include "cartmanager.h"

// 构造函数：初始化购物车管理对象
CartManager::CartManager(QObject *parent)
    : QObject(parent)
{
    // 暂无初始化逻辑
}

// ========== 添加菜品到购物车 ==========
// 参数：菜品ID、菜品名称、单价、购买数量
void CartManager::addItem(int dishId, const QString &dishName, double price, int count)
{
    // 先查找该菜品是否已在购物车中
    int idx = findItem(dishId);

    if (idx >= 0) {
        // 已存在：只增加数量，不新增条目
        m_items[idx].count += count;
        // 重新计算该菜品小计金额 = 单价 × 数量
        m_items[idx].subtotal = m_items[idx].price * m_items[idx].count;
    } else {
        // 不存在：创建新的购物车条目
        CartItem item;
        item.dishId   = dishId;       // 菜品ID
        item.dishName = dishName;     // 菜品名称
        item.price    = price;        // 单价
        item.count    = count;        // 数量
        item.subtotal = price * count;// 小计
        m_items.append(item);         // 添加到购物车列表
    }

    recalculate();             // 重新计算总价
    emit cartChanged();        // 发送信号：购物车内容已改变
}

// ========== 修改购物车中菜品的数量 ==========
void CartManager::updateItem(int dishId, int newCount)
{
    int idx = findItem(dishId);
    if (idx >= 0) {
        // 如果数量 ≤0，直接删除该菜品
        if (newCount <= 0) {
            removeItem(dishId);
            return;
        }

        // 更新数量和小计
        m_items[idx].count = newCount;
        m_items[idx].subtotal = m_items[idx].price * m_items[idx].count;

        recalculate();        // 重新计算总价
        emit cartChanged();   // 发送信号：购物车已更新
    }
}

// ========== 从购物车删除指定菜品 ==========
void CartManager::removeItem(int dishId)
{
    int idx = findItem(dishId);
    if (idx >= 0) {
        m_items.removeAt(idx);  // 从列表中移除
        recalculate();          // 重新计算总价
        emit cartChanged();     // 发送信号
    }
}

// ========== 清空整个购物车 ==========
void CartManager::clearCart()
{
    m_items.clear();            // 清空列表
    recalculate();              // 总价归0
    emit cartChanged();         // 发送信号
}

// ========== 获取购物车中所有菜品条目 ==========
QList<CartItem> CartManager::getItems() const
{
    return m_items;
}

// ========== 计算并返回购物车总价 ==========
double CartManager::getTotalPrice() const
{
    double total = 0;
    // 遍历所有菜品，累加小计
    for (const CartItem &item : m_items) {
        total += item.subtotal;
    }
    return total;
}

// ========== 获取购物车中菜品种类数量 ==========
int CartManager::getItemCount() const
{
    return m_items.size();
}

// ========== 将购物车数据转为 JSON 数组 ==========
// 用于提交订单、保存数据、网络传输等场景
QJsonArray CartManager::toJsonArray() const
{
    QJsonArray arr;
    for (const CartItem &item : m_items) {
        QJsonObject obj;
        obj["dish_id"]   = item.dishId;
        obj["dish_name"] = item.dishName;
        obj["price"]     = item.price;
        obj["count"]     = item.count;
        obj["subtotal"]  = item.subtotal;
        arr.append(obj);
    }
    return arr;
}

// ========== 根据菜品ID查找它在购物车列表中的索引 ==========
// 找到返回下标，没找到返回 -1
int CartManager::findItem(int dishId) const
{
    for (int i = 0; i < m_items.size(); ++i) {
        if (m_items[i].dishId == dishId) {
            return i;
        }
    }
    return -1;
}

// ========== 重新计算总价，并发送总价变化信号 ==========
void CartManager::recalculate()
{
    double total = getTotalPrice();
    emit totalPriceChanged(total);
}
