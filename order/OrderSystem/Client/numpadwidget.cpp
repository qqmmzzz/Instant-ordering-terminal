#include "numpadwidget.h"

// 构造函数：创建数字软键盘窗口，设置样式、布局、按钮、信号槽
NumpadWidget::NumpadWidget(QWidget *parent)
    : QWidget(parent, Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint)  // 无边框、置顶、工具窗口
    , m_targetInput(nullptr)    // 绑定的目标输入框，初始为空
    , m_positionAbove(false)    // 键盘默认显示在输入框下方
{
    // ===================== 软键盘样式表 =====================
    setStyleSheet(R"(
        QWidget {
            background-color: #2c3e50;  // 键盘整体背景色
            border-radius: 8px;          // 圆角
        }
        QPushButton {
            background-color: #34495e;   // 按钮默认背景
            color: white;                // 文字白色
            font-size: 20px;             // 字体大小
            font-weight: bold;           // 加粗
            border: none;                // 无边框
            border-radius: 6px;          // 按钮圆角
            min-width: 60px;             // 按钮最小宽度
            min-height: 50px;            // 按钮最小高度
        }
        QPushButton:hover {              // 鼠标悬浮效果
            background-color: #3d5268;
        }
        QPushButton:pressed {            // 按钮按下效果
            background-color: #2c3e50;
        }
        QPushButton#btnBackspace, QPushButton#btnClear {  // 退格、清空按钮（橙色）
            background-color: #e67e22;
        }
        QPushButton#btnBackspace:hover, QPushButton#btnClear:hover {
            background-color: #d35400;
        }
        QPushButton#btnConfirm {         // 确认按钮（绿色）
            background-color: #27ae60;
        }
        QPushButton#btnConfirm:hover {
            background-color: #1e8449;
        }
    )");

    // ===================== 创建网格布局 =====================
    m_gridLayout = new QGridLayout(this);
    m_gridLayout->setSpacing(5);           // 按钮之间的间距
    m_gridLayout->setContentsMargins(8, 8, 8, 8);  // 布局内边距

    // 数字键盘按钮文本：12个按键
    QString keys[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", ".", "0", "Back"};

    // 循环创建 12 个数字/符号/退格按钮
    for (int i = 0; i < 12; ++i) {
        QPushButton *btn = new QPushButton(keys[i]);

        // 如果是退格键，设置名称并绑定退格槽函数
        if (keys[i] == "Back") {
            btn->setObjectName("btnBackspace");
            connect(btn, &QPushButton::clicked, this, &NumpadWidget::onBackspace);
        } else {
            // 普通数字键，绑定通用按键点击函数
            connect(btn, &QPushButton::clicked, this, &NumpadWidget::onKeyPressed);
        }

        // 把按钮添加到网格：4行3列布局
        m_gridLayout->addWidget(btn, i / 3, i % 3);
    }

    // ===================== 创建底部功能键 =====================
    // 清空按钮 C
    QPushButton *btnClear = new QPushButton("C");
    btnClear->setObjectName("btnClear");
    connect(btnClear, &QPushButton::clicked, this, &NumpadWidget::onClear);
    m_gridLayout->addWidget(btnClear, 4, 0);  // 第5行第1列

    // 确认按钮 OK（占2列）
    QPushButton *btnConfirm = new QPushButton("OK");
    btnConfirm->setObjectName("btnConfirm");
    connect(btnConfirm, &QPushButton::clicked, this, &NumpadWidget::onConfirm);
    m_gridLayout->addWidget(btnConfirm, 4, 1, 1, 2);

    adjustSize();  // 自动调整窗口大小适配所有按钮
}

// 析构函数：Qt自动管理子控件，无需手动释放
NumpadWidget::~NumpadWidget()
{
}

// ===================== 设置目标输入框，并显示键盘 =====================
void NumpadWidget::setTargetInput(QLineEdit *target)
{
    m_targetInput = target;  // 绑定要输入的框
    if (target) {
        // 获取输入框在屏幕上的坐标
        QPoint pos = target->mapToGlobal(QPoint(0, 0));

        // 根据配置显示在输入框 上方 / 下方
        if (m_positionAbove) {
            move(pos.x(), pos.y() - height());
        } else {
            move(pos.x(), pos.y() + target->height());
        }

        show();                // 显示软键盘
        target->setFocus();    // 让输入框获得焦点
    }
}

// 设置键盘显示位置：true=显示在输入框上方，false=下方
void NumpadWidget::setPositionAbove(bool above)
{
    m_positionAbove = above;
}

// ===================== 普通数字按键点击：向输入框插入内容 =====================
void NumpadWidget::onKeyPressed()
{
    // 获取点击的按钮
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (btn && m_targetInput) {
        QString text = btn->text();

        // 特殊处理小数点：只能输入一个
        if (text == ".") {
            if (!m_targetInput->text().contains(".")) {
                m_targetInput->insert(".");
            }
        } else {
            // 普通数字直接插入
            m_targetInput->insert(text);
        }
    }
}

// ===================== 退格键：删除最后一个字符 =====================
void NumpadWidget::onBackspace()
{
    if (m_targetInput) {
        QString text = m_targetInput->text();
        if (!text.isEmpty()) {
            // 截取去掉最后一个字符的内容
            m_targetInput->setText(text.left(text.length() - 1));
        }
    }
}

// ===================== 清空键：删除输入框所有内容 =====================
void NumpadWidget::onClear()
{
    if (m_targetInput) {
        m_targetInput->clear();
    }
}

// ===================== 确认键：隐藏键盘，取消输入框焦点 =====================
void NumpadWidget::onConfirm()
{
    hide();
    if (m_targetInput) {
        m_targetInput->clearFocus();
    }
}
