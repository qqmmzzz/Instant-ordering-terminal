#include "themecolordialog.h"

// 构造函数：创建主题颜色选择对话框，以4列网格展示12种主题色
ThemeColorDialog::ThemeColorDialog(const QStringList &themeNames,
                                   const QList<QColor> &previewColors,
                                   int currentIndex,
                                   QWidget *parent)
    : QDialog(parent), m_selectedIndex(currentIndex) // 初始化为当前已选主题索引
{
    setWindowTitle("选择主题颜色");
    setFixedSize(420, 380);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 15, 20, 15);

    // 顶部提示标题
    QLabel *lblTitle = new QLabel("请选择您喜欢的主题颜色");
    lblTitle->setAlignment(Qt::AlignCenter);
    lblTitle->setStyleSheet("font-size: 16px; font-weight: bold; padding: 6px;");
    mainLayout->addWidget(lblTitle);

    // 4列 x 3行的颜色网格布局
    m_gridLayout = new QGridLayout();
    m_gridLayout->setSpacing(10);

    // 遍历所有主题名称和颜色，创建颜色按钮
    for (int i = 0; i < themeNames.size() && i < previewColors.size(); ++i) {
        QColor color = previewColors[i];

        // 每个按钮显示主题名称，背景设为主题预览色
        QPushButton *btn = new QPushButton(themeNames[i]);
        btn->setFixedSize(90, 60); // 固定按钮大小
        btn->setToolTip(themeNames[i]); // 悬停提示

        // 根据颜色亮度自动选择黑色或白色文字（保证可读性）
        QString textColor = color.lightness() > 128 ? "#333333" : "#ffffff";
        // 当前选中的主题用红色边框高亮
        QString borderColor = (i == currentIndex) ? "#e74c3c" : "transparent";
        int borderWidth = (i == currentIndex) ? 3 : 0;

        btn->setStyleSheet(QString(
            "QPushButton {"
            "   background-color: %1; color: %2;"
            "   border: %3px solid %4; border-radius: 8px;"
            "   font-size: 12px; font-weight: bold;"
            "}"
            "QPushButton:hover { border: 2px solid #e74c3c; }" // 悬停红框
        ).arg(color.name(), textColor).arg(borderWidth).arg(borderColor));

        // 点击按钮：记录索引 -> 发射信号 -> 关闭对话框
        connect(btn, &QPushButton::clicked, this, [this, i]() {
            m_selectedIndex = i;
            emit themeSelected(i); // 通知外部应用主题
            accept();
        });

        // 网格布局：行 = i/4, 列 = i%4
        m_gridLayout->addWidget(btn, i / 4, i % 4);
    }

    mainLayout->addLayout(m_gridLayout);
    mainLayout->addStretch(); // 底部留白
}
