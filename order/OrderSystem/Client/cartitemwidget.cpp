#include "cartitemwidget.h"

/*
 * 购物车单项控件构造函数
 * 参数：
 * dishId    - 菜品ID（唯一标识）
 * dishName  - 菜品名称
 * price     - 菜品单价
 * count     - 初始购买数量
 * parent    - 父控件
 */
CartItemWidget::CartItemWidget(int dishId, const QString &dishName,
                               double price, int count,
                               QWidget *parent)
    : QWidget(parent)                // 继承自QWidget
    , m_dishId(dishId),              // 初始化菜品ID
      m_dishName(dishName),          // 初始化菜品名称
      m_price(price)                 // 初始化单价
{
    // ===================== 1. 创建菜品名称标签 =====================
    m_lblName = new QLabel(dishName);
    m_lblName->setStyleSheet("font-size: 13px; font-weight: bold;");  // 字体加粗
    m_lblName->setMinimumWidth(80);                                   // 设置最小宽度，防止布局错乱

    // ===================== 2. 创建单价标签 =====================
    m_lblPrice = new QLabel(QString("￥%1").arg(price, 0, 'f', 2));    // 格式化显示单价，保留2位小数
    m_lblPrice->setStyleSheet("color: #e74c3c; font-size: 12px;");    // 红色字体
    m_lblPrice->setMinimumWidth(60);

    // ===================== 3. 创建数量选择微调框 =====================
    m_spinCount = new QSpinBox();
    m_spinCount->setMinimum(1);       // 最小数量1
    m_spinCount->setMaximum(99);      // 最大数量99
    m_spinCount->setValue(count);     // 设置初始数量
    m_spinCount->setMinimumWidth(55);

    // ===================== 4. 创建小计金额标签 =====================
    m_lblSubtotal = new QLabel();
    m_lblSubtotal->setStyleSheet("color: #e67e22; font-weight: bold; font-size: 13px;");
    m_lblSubtotal->setMinimumWidth(70);
    updateSubtotal();                 // 计算并显示小计 = 单价 × 数量

    // ===================== 5. 创建删除按钮 =====================
    m_btnDelete = new QPushButton("删除");
    m_btnDelete->setStyleSheet(
        "QPushButton {"
        "   background-color: #e74c3c; color: white;"    // 红色背景，白色文字
        "   border: none; padding: 4px 10px;"            // 无边框，内边距
        "   border-radius: 3px;"                         // 圆角
        "}"
        "QPushButton:hover {"                            // 鼠标悬浮效果
        "   background-color: #c0392b;"
        "}"
    );
    m_btnDelete->setMaximumWidth(60);

    // ===================== 6. 信号与槽绑定 =====================
    // 数量改变时，触发 onSpinValueChanged
    connect(m_spinCount, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &CartItemWidget::onSpinValueChanged);

    // 点击删除按钮，触发 onBtnDelete
    connect(m_btnDelete, &QPushButton::clicked,
            this, &CartItemWidget::onBtnDelete);

    // ===================== 7. 水平布局 =====================
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(6, 2, 6, 2);  // 设置布局边距（左、上、右、下）
    layout->addWidget(m_lblName);            // 添加菜名
    layout->addWidget(m_lblPrice);           // 添加单价
    layout->addWidget(m_spinCount);          // 添加数量选择器
    layout->addWidget(m_lblSubtotal);        // 添加小计
    layout->addWidget(m_btnDelete);          // 添加删除按钮
}

// 获取菜品ID（供外部调用）
int CartItemWidget::getDishId() const
{
    return m_dishId;
}

// 获取当前选择的数量（供外部调用）
int CartItemWidget::getCount() const
{
    return m_spinCount->value();
}

/*
 * 数量选择框值改变的槽函数
 * val：改变后的新值（这里用Q_UNUSED表示没直接用到）
 * 功能：更新小计金额，并向外发送“数量已改变”信号
 */
void CartItemWidget::onSpinValueChanged(int val)
{
    Q_UNUSED(val);
    updateSubtotal();                // 重新计算小计
    emit countChanged(m_dishId, m_spinCount->value());  // 发送信号：菜品ID + 新数量
}

/*
 * 删除按钮点击槽函数
 * 功能：向外发送“请求删除此菜品”信号
 */
void CartItemWidget::onBtnDelete()
{
    emit removeRequested(m_dishId);  // 发送信号：告诉外部要删除哪个菜品
}

/*
 * 更新小计金额
 * 公式：小计 = 单价 × 当前数量
 * 并显示到标签上，保留2位小数
 */
void CartItemWidget::updateSubtotal()
{
    double sub = m_price * m_spinCount->value();
    m_lblSubtotal->setText(QString("￥%1").arg(sub, 0, 'f', 2));
}
