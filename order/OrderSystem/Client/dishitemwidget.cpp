#include "dishitemwidget.h"

/*
 * 菜品单项控件构造函数
 * 作用：菜单列表里的每一个菜品条目，显示图片、名称、价格、库存、描述、数量选择、加购按钮
 * 参数：
 * dishId      - 菜品ID
 * dishName    - 菜品名称
 * price       - 单价
 * stock       - 库存
 * description - 菜品描述
 * imageData   - 菜品图片二进制数据
 * parent      - 父控件
 */
DishItemWidget::DishItemWidget(int dishId, const QString &dishName,
                               double price, int stock,
                               const QString &description,
                               const QByteArray &imageData,
                               QWidget *parent)
    : QWidget(parent)
    , m_dishId(dishId),      // 初始化菜品ID
      m_dishName(dishName),  // 初始化菜品名称
      m_price(price)         // 初始化菜品价格
{
    // ===================== 1. 菜品图片标签 =====================
    m_lblImage = new QLabel();
    m_lblImage->setFixedSize(48, 48);                // 固定图片大小（小屏适配）
    m_lblImage->setAlignment(Qt::AlignCenter);       // 图片居中显示
    m_lblImage->setStyleSheet(
        "QLabel { border: 1px solid #ccc; border-radius: 4px; background-color: #fafafa; }");

    // 如果有图片数据，加载并显示图片
    if (!imageData.isEmpty())
    {
        QPixmap pixmap;
        pixmap.loadFromData(imageData);              // 从二进制数据加载图片
        if (!pixmap.isNull())
        {
            // 缩放图片，保持比例，平滑显示
            m_lblImage->setPixmap(pixmap.scaled(44, 44, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    }

    // ===================== 2. 菜品名称标签 =====================
    m_lblName = new QLabel(dishName);
    m_lblName->setStyleSheet("font-size: 12px; font-weight: bold;");
    m_lblName->setMinimumWidth(70);
    m_lblName->setMaximumWidth(90);

    // ===================== 3. 菜品价格标签 =====================
    m_lblPrice = new QLabel(QString("￥%1").arg(price, 0, 'f', 2));  // 格式化价格，保留2位小数
    m_lblPrice->setStyleSheet("color: #e74c3c; font-size: 12px; font-weight: bold;");
    m_lblPrice->setMinimumWidth(55);

    // ===================== 4. 库存标签 =====================
    m_lblStock = new QLabel(QString("存:%1").arg(stock));  // 显示：存:xx
    m_lblStock->setStyleSheet("color: #7f8c8d; font-size: 10px;");
    m_lblStock->setMinimumWidth(35);

    // ===================== 5. 菜品描述标签 =====================
    m_lblDesc = new QLabel(description);
    m_lblDesc->setStyleSheet("color: #95a5a6; font-size: 10px;");
    m_lblDesc->setMaximumWidth(80);

    // ===================== 6. 数量选择器 =====================
    m_spinCount = new QSpinBox();
    m_spinCount->setMinimum(1);                      // 最少买1份
    m_spinCount->setMaximum(stock > 0 ? stock : 99); // 最多不能超过库存
    m_spinCount->setValue(1);                        // 默认数量1
    m_spinCount->setFixedWidth(48);
    m_spinCount->setFixedHeight(26);

    // ===================== 7. 加入购物车按钮 =====================
    m_btnAdd = new QPushButton("加购");
    m_btnAdd->setStyleSheet(
        "QPushButton { background-color: #3498db; color: white;"
        "   border: none; padding: 4px 8px; border-radius: 3px; font-size: 11px; font-weight: bold; }"
        "QPushButton:hover { background-color: #2980b9; }");  // 蓝色按钮 + 悬浮效果
    m_btnAdd->setFixedWidth(52);
    m_btnAdd->setFixedHeight(26);

    // 按钮点击 → 触发加购槽函数
    connect(m_btnAdd, &QPushButton::clicked, this, &DishItemWidget::onBtnAddToCart);

    // ===================== 8. 水平布局，紧凑排列 =====================
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(4, 2, 4, 2);  // 内边距很小，适合小屏
    layout->setSpacing(4);                   // 控件间距
    layout->addWidget(m_lblImage);           // 图片
    layout->addWidget(m_lblName);            // 菜名
    layout->addWidget(m_lblPrice);           // 价格
    layout->addWidget(m_lblStock);           // 库存
    layout->addWidget(m_lblDesc, 1);         // 描述（占剩余空间）
    layout->addWidget(m_spinCount);          // 数量选择
    layout->addWidget(m_btnAdd);             // 加购按钮
}

// 获取菜品ID（外部调用）
int DishItemWidget::getDishId() const { return m_dishId; }

// 获取当前选择的购买数量（外部调用）
int DishItemWidget::getCount() const { return m_spinCount->value(); }

// ===================== 加购按钮点击槽函数 =====================
// 功能：发送信号，告诉主界面把这个菜品加入购物车
void DishItemWidget::onBtnAddToCart()
{
    emit addToCart(m_dishId, m_dishName, m_price, m_spinCount->value());
}
