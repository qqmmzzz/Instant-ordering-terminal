#ifndef CARTITEMWIDGET_H
#define CARTITEMWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QHBoxLayout>

/**
 * @brief 购物车条目自定义 Widget
 * 用于嵌入 QListWidget 中展示购物车中的单个菜品。
 * 包含：菜名、单价、数量（可修改）、小计、删除按钮
 */
class CartItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CartItemWidget(int dishId, const QString &dishName,
                            double price, int count,
                            QWidget *parent = nullptr);

    /// 获取菜品编号
    int getDishId() const;

    /// 获取当前数量
    int getCount() const;

signals:
    /// 数量修改信号
    void countChanged(int dishId, int newCount);

    /// 删除信号
    void removeRequested(int dishId);

private slots:
    void onSpinValueChanged(int val);
    void onBtnDelete();

private:
    int     m_dishId;
    QString m_dishName;
    double  m_price;

    QLabel    *m_lblName;
    QLabel    *m_lblPrice;
    QSpinBox  *m_spinCount;
    QLabel    *m_lblSubtotal;
    QPushButton *m_btnDelete;

    void updateSubtotal();
};

#endif // CARTITEMWIDGET_H
