#include "themecolordialog.h"

/*
 * 主题颜色选择对话框构造函数
 * themeNames: 主题名称列表（如：浅色、深色、蓝色等）
 * previewColors: 每个主题对应的预览颜色
 * currentIndex: 当前正在使用的主题索引
 * parent: 父窗口
 */
ThemeColorDialog::ThemeColorDialog(const QStringList &themeNames,
                                   const QList<QColor> &previewColors,
                                   int currentIndex,
                                   QWidget *parent)
    : QDialog(parent)                // 继承自弹窗窗口
    , m_selectedIndex(currentIndex)  // 记录用户选中的主题索引
{
    // 窗口基础设置
    setWindowTitle("选择主题颜色");    // 窗口标题
    setFixedSize(420, 380);           // 固定窗口大小，防止拉伸变形
    // 移除窗口右上角的问号帮助按钮
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    // 主垂直布局：从上到下排列控件
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 15, 20, 15); // 设置布局内边距

    // ===================== 1. 标题标签 =====================
    QLabel *lblTitle = new QLabel("请选择您喜欢的主题颜色");
    lblTitle->setAlignment(Qt::AlignCenter); // 文字居中
    lblTitle->setStyleSheet("font-size: 16px; font-weight: bold; padding: 6px;");
    mainLayout->addWidget(lblTitle);

    // ===================== 2. 主题颜色网格布局 =====================
    // 4列3行网格布局，用于排列多个主题按钮
    m_gridLayout = new QGridLayout();
    m_gridLayout->setSpacing(10); // 按钮之间的间距

    // 遍历所有主题，创建对应的颜色按钮
    for (int i = 0; i < themeNames.size() && i < previewColors.size(); ++i) {
        QColor color = previewColors[i]; // 当前主题的颜色

        // 创建主题按钮，显示主题名称
        QPushButton *btn = new QPushButton(themeNames[i]);
        btn->setFixedSize(90, 60); // 固定按钮大小
        btn->setToolTip(themeNames[i]); // 鼠标悬浮提示

        // 根据背景色亮度自动选择文字颜色（浅色背景用深色字，反之亦然）
        QString textColor = color.lightness() > 128 ? "#333333" : "#ffffff";
        // 当前选中的主题按钮显示红色边框，其他无边框
        QString borderColor = (i == currentIndex) ? "#e74c3c" : "transparent";
        int borderWidth = (i == currentIndex) ? 3 : 0;

        // 设置按钮样式：背景色、文字颜色、边框、圆角
        btn->setStyleSheet(QString(
            "QPushButton {"
            "   background-color: %1; color: %2;"
            "   border: %3px solid %4; border-radius: 8px;"
            "   font-size: 12px; font-weight: bold;"
            "}"
            "QPushButton:hover { border: 2px solid #e74c3c; }" // 鼠标悬浮显示红色边框
        ).arg(color.name(), textColor).arg(borderWidth).arg(borderColor));

        // 按钮点击事件：记录选中索引 → 发送信号 → 关闭弹窗
        connect(btn, &QPushButton::clicked, this, [this, i]() {
            m_selectedIndex = i;               // 更新选中的主题索引
            emit themeSelected(i);             // 发送主题选择信号
            accept();                          // 关闭弹窗
        });

        // 将按钮添加到网格：4列布局（行 = i/4，列 = i%4）
        m_gridLayout->addWidget(btn, i / 4, i % 4);
    }

    // 将主题网格添加到主布局
    mainLayout->addLayout(m_gridLayout);
    mainLayout->addStretch(); // 添加弹性空白，让布局更美观
}
