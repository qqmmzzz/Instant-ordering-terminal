#include "thememanager.h"
#include <QDir>

// 构造函数：保存QApplication引用，初始化12种主题
ThemeManager::ThemeManager(QApplication &app, QObject *parent)
    : QObject(parent), m_app(app), m_targetWidget(nullptr), m_currentIndex(0)
{
    initThemes(); // 填充m_themes列表
}

// 设置需要绘制背景的目标窗口
void ThemeManager::setTargetWidget(QWidget *widget)
{
    m_targetWidget = widget;
}

int ThemeManager::currentThemeIndex() const
{
    return m_currentIndex;
}

// 获取当前主题的调色板
ThemePalette ThemeManager::currentPalette() const
{
    if (m_currentIndex >= 0 && m_currentIndex < m_themes.size())
        return m_themes[m_currentIndex];
    return m_themes[0]; // 越界保护，返回默认主题
}

// 获取所有主题名称列表
QStringList ThemeManager::getThemeNames() const
{
    QStringList names;
    for (const auto &t : m_themes)
        names << t.name;
    return names;
}

bool ThemeManager::hasBackground() const
{
    return !m_bgPixmap.isNull();
}

QPixmap ThemeManager::backgroundPixmap() const
{
    return m_bgPixmap;
}

// ========== 初始化12种预置主题颜色方案 ==========
// 每种主题包含：背景色、文字色、强调色、表面色、边框色、按钮背景、按钮文字、表头背景、表头文字
void ThemeManager::initThemes()
{
    m_themes = {
        // 名称,       背景色,        文字色,        强调色,       表面色,       边框色,       按钮背景,     按钮文字,     表头背景,     表头文字
        { "经典白",   QColor("#ffffff"), QColor("#333333"), QColor("#3498db"), QColor("#f5f6fa"),
          QColor("#dcdde1"), QColor("#3498db"), QColor("#ffffff"), QColor("#3498db"), QColor("#ffffff") },
        { "暗夜黑",   QColor("#1e1e2e"), QColor("#cdd6f4"), QColor("#89b4fa"), QColor("#181825"),
          QColor("#45475a"), QColor("#89b4fa"), QColor("#1e1e2e"), QColor("#45475a"), QColor("#cdd6f4") },
        { "海洋蓝",   QColor("#1a3a5c"), QColor("#e0e8f0"), QColor("#5dade2"), QColor("#1e4a6e"),
          QColor("#2a5a7e"), QColor("#5dade2"), QColor("#1a3a5c"), QColor("#2a5a7e"), QColor("#e0e8f0") },
        { "森林绿",   QColor("#1a3c2a"), QColor("#d0e8d8"), QColor("#58d68d"), QColor("#1e4a32"),
          QColor("#2a5a3e"), QColor("#58d68d"), QColor("#1a3c2a"), QColor("#2a5a3e"), QColor("#d0e8d8") },
        { "樱花粉",   QColor("#fff0f5"), QColor("#5c2040"), QColor("#e74c8b"), QColor("#fce4ec"),
          QColor("#f8bbd0"), QColor("#e74c8b"), QColor("#ffffff"), QColor("#f48fb1"), QColor("#5c2040") },
        { "日落橙",   QColor("#3c2a1a"), QColor("#f0d8c0"), QColor("#f39c12"), QColor("#4a3422"),
          QColor("#5a4432"), QColor("#f39c12"), QColor("#3c2a1a"), QColor("#5a4432"), QColor("#f0d8c0") },
        { "薰衣紫",   QColor("#2a1a3c"), QColor("#d8c0f0"), QColor("#bb8fce"), QColor("#32224a"),
          QColor("#4a3260"), QColor("#bb8fce"), QColor("#2a1a3c"), QColor("#4a3260"), QColor("#d8c0f0") },
        { "咖啡棕",   QColor("#3c2e20"), QColor("#e8d8c8"), QColor("#d4a574"), QColor("#4a3a2a"),
          QColor("#5a4a3a"), QColor("#d4a574"), QColor("#3c2e20"), QColor("#5a4a3a"), QColor("#e8d8c8") },
        { "天空青",   QColor("#1a3c3c"), QColor("#c0e8e8"), QColor("#48c9b0"), QColor("#1e4a4a"),
          QColor("#2a5a5a"), QColor("#48c9b0"), QColor("#1a3c3c"), QColor("#2a5a5a"), QColor("#c0e8e8") },
        { "玫瑰红",   QColor("#3c1a2a"), QColor("#f0c0d0"), QColor("#ec7063"), QColor("#4a2232"),
          QColor("#5a3242"), QColor("#ec7063"), QColor("#3c1a2a"), QColor("#5a3242"), QColor("#f0c0d0") },
        { "薄荷绿",   QColor("#f0faf5"), QColor("#2a5c40"), QColor("#27ae60"), QColor("#e8f5e9"),
          QColor("#c8e6c9"), QColor("#27ae60"), QColor("#ffffff"), QColor("#66bb6a"), QColor("#2a5c40") },
        { "琥珀金",   QColor("#3c3520"), QColor("#f0e8c0"), QColor("#f1c40f"), QColor("#4a422a"),
          QColor("#5a523a"), QColor("#f1c40f"), QColor("#3c3520"), QColor("#5a523a"), QColor("#f0e8c0") },
    };
}

// ========== 应用指定主题：设置全局样式表并发射信号 ==========
void ThemeManager::applyTheme(int index)
{
    if (index < 0 || index >= m_themes.size()) return;
    m_currentIndex = index;
    m_app.setStyleSheet(generateStyleSheet(m_themes[index])); // 全局应用样式
    emit themeChanged(index);
}

// ========== 设置背景图片路径并加载为QPixmap ==========
void ThemeManager::setBackgroundPath(const QString &path)
{
    m_bgImagePath = path;
    m_bgPixmap = QPixmap(path); // 加载图片
    emit backgroundChanged(path);
}

QString ThemeManager::backgroundPath() const
{
    return m_bgImagePath;
}

// ========== 清除背景图片 ==========
void ThemeManager::clearBackground()
{
    m_bgImagePath.clear();
    m_bgPixmap = QPixmap(); // 置空
    emit backgroundChanged(QString());
}

// ========== 根据调色板生成完整的QSS样式表 ==========
QString ThemeManager::generateStyleSheet(const ThemePalette &p) const
{
    // 提取各颜色值
    QString bg = p.bgColor.name();
    QString txt = p.textColor.name();
    QString accent = p.accentColor.name();
    QString surface = p.surfaceColor.name();
    QString border = p.borderColor.name();
    QString btnBg = p.btnBgColor.name();
    QString btnTxt = p.btnTextColor.name();
    QString hdrBg = p.headerBgColor.name();
    QString hdrTxt = p.headerTextColor.name();

    // 当有背景图时，主窗口背景透明，容器使用半透明色
    QString mainBg = hasBackground()
        ? "background: transparent;"
        : QString("background-color: %1;").arg(bg);
    QString containerBg = hasBackground()
        ? QString("background-color: %1;").arg(
            p.bgColor.lightness() > 128
                ? QColor(255,255,255,210).name(QColor::HexArgb)  // 浅色背景 -> 白色半透明
                : QColor(30,30,46,210).name(QColor::HexArgb))    // 深色背景 -> 深色半透明
        : QString("background-color: %1;").arg(surface);

    // 生成Qt样式表字符串，覆盖所有常用控件
    return QString(R"(
        QWidget#ServerWidget, QWidget#ClientWidget { %1 }
        QWidget { color: %2; font-family: "Microsoft YaHei", "SimHei", sans-serif; }
        QGroupBox { %3 border: 1px solid %4; border-radius: 6px; margin-top: 10px; padding-top: 14px; }
        QGroupBox::title { subcontrol-origin: margin; left: 12px; padding: 0 6px; color: %5; }
        QLineEdit { background-color: %6; color: %2; border: 1px solid %4;
            border-radius: 4px; padding: 5px 8px; font-size: 13px; }
        QLineEdit:focus { border: 2px solid %5; }
        QPushButton { background-color: %7; color: %8; border: none;
            border-radius: 4px; padding: 6px 14px; font-size: 13px; font-weight: bold; }
        QPushButton:hover { opacity: 0.85; }
        QSpinBox, QDoubleSpinBox { background-color: %6; color: %2; border: 1px solid %4;
            border-radius: 4px; padding: 3px 6px; font-size: 13px; }
        QComboBox { background-color: %6; color: %2; border: 1px solid %4;
            border-radius: 4px; padding: 5px 8px; font-size: 13px; }
        QComboBox::drop-down { border: none; width: 24px; }
        QTabWidget::pane { border: 1px solid %4; %3 border-radius: 4px; }
        QTabBar::tab { background-color: %6; color: %2; padding: 8px 18px;
            border: 1px solid %4; border-bottom: none; border-top-left-radius: 6px;
            border-top-right-radius: 6px; margin-right: 2px; font-size: 13px; }
        QTabBar::tab:selected { background-color: %5; color: %8; font-weight: bold; }
        QTableWidget { background-color: %6; color: %2; border: 1px solid %4;
            gridline-color: %4; font-size: 12px; }
        QTableWidget::item { padding: 4px; }
        QTableWidget::item:selected { background-color: %5; color: %8; }
        QHeaderView::section { background-color: %9; color: %10;
            padding: 6px; border: 1px solid %4; font-weight: bold; font-size: 12px; }
        QTextEdit { background-color: %6; color: %2; border: 1px solid %4;
            border-radius: 4px; font-size: 12px; }
        QListWidget { background-color: %6; color: %2; border: 1px solid %4; font-size: 12px; }
        QListWidget::item { padding: 4px; }
        QListWidget::item:selected { background-color: %5; color: %8; }
        QLabel { color: %2; font-size: 13px; }
        QScrollBar:vertical { background-color: %6; width: 10px; }
        QScrollBar::handle:vertical { background-color: %4; border-radius: 5px; min-height: 30px; }
        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height: 0; }
        QScrollBar:horizontal { background-color: %6; height: 10px; }
        QScrollBar::handle:horizontal { background-color: %4; border-radius: 5px; min-width: 30px; }
        QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal { width: 0; }
    )").arg(mainBg, txt, containerBg, border, accent, surface, btnBg, btnTxt, hdrBg, hdrTxt);
}

// ========== 保存主题和背景设置到系统注册表/配置文件 ==========
void ThemeManager::saveSettings()
{
    QSettings settings("OrderSystem", "Theme"); // 组织名=OrderSystem, 应用名=Theme
    settings.setValue("themeIndex", m_currentIndex);
    settings.setValue("background", m_bgImagePath);
}

// ========== 从系统注册表/配置文件加载设置 ==========
void ThemeManager::loadSettings()
{
    QSettings settings("OrderSystem", "Theme");
    m_currentIndex = settings.value("themeIndex", 0).toInt(); // 默认索引0
    QString bgPath = settings.value("background", QString()).toString();
    if (!bgPath.isEmpty()) {
        m_bgImagePath = bgPath;
        m_bgPixmap = QPixmap(bgPath); // 重新加载背景图片
    }
    applyTheme(m_currentIndex); // 应用加载的主题
}
