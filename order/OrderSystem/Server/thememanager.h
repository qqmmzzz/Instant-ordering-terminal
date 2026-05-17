#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QObject>
#include <QApplication>
#include <QSettings>
#include <QPixmap>
#include <QMap>

/**
 * @brief 主题管理器
 * 支持12种颜色主题 + 自定义背景图片。
 * 背景图片通过 paintEvent 绘制（最可靠的方式），
 * 主题通过 QApplication::setStyleSheet() 全局应用。
 */

struct ThemePalette {
    QString name;           // 主题名称
    QColor  bgColor;        // 主背景色
    QColor  textColor;      // 正文文字色
    QColor  accentColor;    // 强调色（按钮、选中）
    QColor  surfaceColor;   // 表面/卡片色
    QColor  borderColor;    // 边框色
    QColor  btnBgColor;     // 按钮背景色
    QColor  btnTextColor;   // 按钮文字色
    QColor  headerBgColor;  // 表头背景色
    QColor  headerTextColor;// 表头文字色
};

class ThemeManager : public QObject
{
    Q_OBJECT

public:
    explicit ThemeManager(QApplication &app, QObject *parent = nullptr);

    /// 设置需要应用背景的主窗口
    void setTargetWidget(QWidget *widget);

    /// 应用指定索引的主题
    void applyTheme(int index);

    /// 获取当前主题索引
    int currentThemeIndex() const;

    /// 获取所有主题名称列表
    QStringList getThemeNames() const;

    /// 获取当前主题调色板
    ThemePalette currentPalette() const;

    /// 设置背景图片路径
    void setBackgroundPath(const QString &path);

    /// 获取背景图片路径
    QString backgroundPath() const;

    /// 获取背景 QPixmap（供 paintEvent 使用）
    QPixmap backgroundPixmap() const;

    /// 清除背景图片
    void clearBackground();

    /// 是否有背景图片
    bool hasBackground() const;

    /// 保存设置
    void saveSettings();

    /// 加载设置
    void loadSettings();

signals:
    void themeChanged(int index);
    void backgroundChanged(const QString &imagePath);

private:
    QApplication &m_app;
    QWidget       *m_targetWidget;
    int            m_currentIndex;
    QString        m_bgImagePath;
    QPixmap        m_bgPixmap;

    QList<ThemePalette> m_themes;

    /// 初始化12种主题
    void initThemes();

    /// 根据调色板生成完整样式表
    QString generateStyleSheet(const ThemePalette &p) const;
};

#endif // THEMEMANAGER_H
