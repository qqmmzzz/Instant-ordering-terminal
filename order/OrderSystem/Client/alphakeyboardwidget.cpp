#include "alphakeyboardwidget.h"

// 构造函数：初始化键盘窗口、样式、按键布局、信号槽绑定
AlphaKeyboardWidget::AlphaKeyboardWidget(QWidget *parent)
    : QWidget(parent, Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint)  // 设置窗口属性：工具窗口、无边框、置顶显示
    , m_targetInput(nullptr)    // 目标输入框初始化为空
    , m_positionAbove(false)    // 键盘默认显示在输入框下方
    , m_shiftMode(false)        // 大写/符号模式初始化为关闭
{
    // 设置键盘整体样式表（背景、按钮颜色、大小、圆角、hover/pressed效果）
    setStyleSheet(R"(
        QWidget {
            background-color: #2c3e50;
            border-radius: 8px;
        }
        QPushButton {
            background-color: #34495e;
            color: white;
            font-size: 18px;
            font-weight: bold;
            border: none;
            border-radius: 4px;
            min-width: 45px;
            min-height: 40px;
        }
        QPushButton:hover {
            background-color: #3d5268;
        }
        QPushButton:pressed {
            background-color: #2c3e50;
        }
        QPushButton#btnBackspace, QPushButton#btnClear {
            background-color: #e67e22;
        }
        QPushButton#btnBackspace:hover, QPushButton#btnClear:hover {
            background-color: #d35400;
        }
        QPushButton#btnShift {
            background-color: #9b59b6;
        }
        QPushButton#btnShift:hover, QPushButton#btnShift.shifted {
            background-color: #8e44ad;
        }
        QPushButton#btnConfirm {
            background-color: #27ae60;
        }
        QPushButton#btnConfirm:hover {
            background-color: #1e8449;
        }
    )");

    // 定义普通模式下的按键字符（大写字母+数字）
    QString normal[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0",
                        "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P",
                        "A", "S", "D", "F", "G", "H", "J", "K", "L", "Back"};
    // 定义Shift模式下的按键字符（小写字母+符号）
    QString shifted[] = {"!", "@", "#", "$", "%", "^", "&", "*", "(", ")",
                         "q", "w", "e", "r", "t", "y", "u", "i", "o", "p",
                         "a", "s", "d", "f", "g", "h", "j", "k", "l", "Back"};

    // 将两种模式的字符存入成员数组，方便切换
    for (int i = 0; i < 30; ++i) {
        m_normalKeys[i] = normal[i];
        m_shiftKeys[i] = shifted[i];
    }

    // 创建网格布局，设置间距和边距
    m_gridLayout = new QGridLayout(this);
    m_gridLayout->setSpacing(3);        // 按键之间的间距
    m_gridLayout->setContentsMargins(6, 6, 6, 6);  // 布局内边距

    // 循环创建前30个主按键（数字+字母+退格）
    for (int i = 0; i < 30; ++i) {
        QPushButton *btn = new QPushButton(m_normalKeys[i]);  // 创建按钮，默认显示普通字符
        // 如果是退格键，设置对象名并绑定退格槽函数
        if (m_normalKeys[i] == "Back") {
            btn->setObjectName("btnBackspace");
            connect(btn, &QPushButton::clicked, this, &AlphaKeyboardWidget::onBackspace);
        } else {
            // 普通字符键，绑定通用按键点击槽函数
            connect(btn, &QPushButton::clicked, this, &AlphaKeyboardWidget::onKeyPressed);
        }
        m_keyButtons.append(btn);  // 将按键存入列表统一管理
        m_gridLayout->addWidget(btn, i / 10, i % 10);  // 按网格布局：3行10列
    }

    // 创建Shift按键，切换大小写/符号
    QPushButton *btnShift = new QPushButton("Shift");
    btnShift->setObjectName("btnShift");
    connect(btnShift, &QPushButton::clicked, this, &AlphaKeyboardWidget::onToggleShift);
    m_gridLayout->addWidget(btnShift, 3, 0, 1, 2);  // 第4行，占2列

    // 创建清空按键（C），清空输入框内容
    QPushButton *btnClear = new QPushButton("C");
    btnClear->setObjectName("btnClear");
    connect(btnClear, &QPushButton::clicked, this, &AlphaKeyboardWidget::onClear);
    m_gridLayout->addWidget(btnClear, 3, 2, 1, 2);  // 第4行，占2列

    // 创建确认按键（OK），隐藏键盘并取消输入框焦点
    QPushButton *btnConfirm = new QPushButton("OK");
    btnConfirm->setObjectName("btnConfirm");
    connect(btnConfirm, &QPushButton::clicked, this, &AlphaKeyboardWidget::onConfirm);
    m_gridLayout->addWidget(btnConfirm, 3, 4, 1, 6);  // 第4行，占6列

    adjustSize();  // 自动调整窗口大小以适应所有按键
}

// 析构函数：Qt会自动管理子控件，无需手动释放
AlphaKeyboardWidget::~AlphaKeyboardWidget()
{
}

// 设置目标输入框，并将键盘显示在输入框旁边
void AlphaKeyboardWidget::setTargetInput(QLineEdit *target)
{
    m_targetInput = target;  // 绑定输入框
    if (target) {
        // 获取输入框在屏幕上的全局坐标
        QPoint pos = target->mapToGlobal(QPoint(0, 0));
        // 根据配置显示在输入框上方/下方
        if (m_positionAbove) {
            move(pos.x(), pos.y() - height());
        } else {
            move(pos.x(), pos.y() + target->height());
        }
        show();          // 显示键盘
        target->setFocus();  // 让输入框获得焦点
    }
}

// 设置键盘显示位置：true=显示在输入框上方，false=下方
void AlphaKeyboardWidget::setPositionAbove(bool above)
{
    m_positionAbove = above;
}

// 普通字符按键点击的槽函数：向输入框插入字符
void AlphaKeyboardWidget::onKeyPressed()
{
    // 获取发送信号的按钮对象
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (btn && m_targetInput) {
        QString text = btn->text();
        // 排除功能键，只插入字符键内容
        if (text != "Back" && text != "Shift" && text != "C" && text != "OK") {
            m_targetInput->insert(text);  // 插入文本到输入框
            if (m_shiftMode) {
                onToggleShift();  // 输入后自动关闭Shift模式（单次生效）
            }
        }
    }
}

// 退格键槽函数：删除输入框最后一个字符
void AlphaKeyboardWidget::onBackspace()
{
    if (m_targetInput) {
        QString text = m_targetInput->text();
        if (!text.isEmpty()) {
            m_targetInput->setText(text.left(text.length() - 1));  // 截取除最后一个字符外的内容
        }
    }
}

// 清空键槽函数：清空输入框所有内容
void AlphaKeyboardWidget::onClear()
{
    if (m_targetInput) {
        m_targetInput->clear();
    }
}

// 确认键槽函数：隐藏键盘，取消输入框焦点
void AlphaKeyboardWidget::onConfirm()
{
    hide();
    if (m_targetInput) {
        m_targetInput->clearFocus();
    }
}

// Shift切换槽函数：切换大小写/符号模式
void AlphaKeyboardWidget::onToggleShift()
{
    m_shiftMode = !m_shiftMode;  // 取反状态
    QPushButton *shiftBtn = findChild<QPushButton*>("btnShift");  // 找到Shift按键
    if (shiftBtn) {
        if (m_shiftMode) {
            // Shift开启：更改按键颜色，并将所有字符切换为小写/符号
            shiftBtn->setStyleSheet("background-color: #8e44ad; color: white;");
            for (int i = 0; i < m_keyButtons.size(); ++i) {
                if (m_normalKeys[i] != "Back") {
                    m_keyButtons[i]->setText(m_shiftKeys[i]);
                }
            }
        } else {
            // Shift关闭：恢复颜色，并切换回大写/数字
            shiftBtn->setStyleSheet("background-color: #9b59b6; color: white;");
            for (int i = 0; i < m_keyButtons.size(); ++i) {
                if (m_normalKeys[i] != "Back") {
                    m_keyButtons[i]->setText(m_normalKeys[i]);
                }
            }
        }
    }
}
