#ifndef DISHITEMWIDGET_H
#define DISHITEMWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QPixmap>
#include <QByteArray>

/**
 * @brief 菜单条目自定义 Widget
 * 包含：菜品图片、菜名、价格、库存、数量选择、加入购物车按钮
 */
class DishItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DishItemWidget(int dishId, const QString &dishName,
                            double price, int stock,
                            const QString &description = "",
                            const QByteArray &imageData = QByteArray(),
                            QWidget *parent = nullptr);

    int getDishId() const;
    int getCount() const;

signals:
    void addToCart(int dishId, const QString &dishName, double price, int count);

private slots:
    void onBtnAddToCart();

private:
    int     m_dishId;
    QString m_dishName;
    double  m_price;

    QLabel      *m_lblImage;
    QLabel      *m_lblName;
    QLabel      *m_lblPrice;
    QLabel      *m_lblStock;
    QLabel      *m_lblDesc;
    QSpinBox    *m_spinCount;
    QPushButton *m_btnAdd;
};

#endif // DISHITEMWIDGET_H
