#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QObject>          // Qt 对象基类
#include <QApplication>     // Qt 应用程序类
#include <QSettings>        // 配置存储类
#include <QPixmap>          // 图片处理类
#include <QMap>             // 映射容器

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
    QColor  accentColor;    // 强调色（按钮、选中状态）
    QColor  surfaceColor;   // 表面/卡片背景色
    QColor  borderColor;    // 边框颜色
    QColor  btnBgColor;     // 按钮背景色
    QColor  btnTextColor;   // 按钮文字色
    QColor  headerBgColor;  // 表头背景色
    QColor  headerTextColor;// 表头文字色
};

class ThemeManager : public QObject
{
    Q_OBJECT

public:
    explicit ThemeManager(QApplication &app, QObject *parent = nullptr);  // 构造函数

    void setTargetWidget(QWidget *widget);           // 设置需要应用背景的主窗口
    void applyTheme(int index);                      // 应用指定索引的主题
    int currentThemeIndex() const;                   // 获取当前主题索引
    QStringList getThemeNames() const;               // 获取所有主题名称列表
    ThemePalette currentPalette() const;             // 获取当前主题调色板
    void setBackgroundPath(const QString &path);     // 设置背景图片路径
    QString backgroundPath() const;                  // 获取背景图片路径
    QPixmap backgroundPixmap() const;                // 获取背景 QPixmap（供 paintEvent 使用）
    void clearBackground();                          // 清除背景图片
    bool hasBackground() const;                      // 是否有背景图片
    void saveSettings();                             // 保存设置到注册表
    void loadSettings();                             // 从注册表加载设置

signals:
    void themeChanged(int index);                    // 主题改变信号
    void backgroundChanged(const QString &imagePath);// 背景改变信号

private:
    QApplication &m_app;            // 应用程序引用，用于全局样式设置
    QWidget       *m_targetWidget;  // 目标窗口指针
    int            m_currentIndex;  // 当前主题索引
    QString        m_bgImagePath;   // 背景图片路径
    QPixmap        m_bgPixmap;      // 背景图片对象

    QList<ThemePalette> m_themes;   // 主题调色板列表

    void initThemes();                          // 初始化12种预设主题
    QString generateStyleSheet(const ThemePalette &p) const;  // 根据调色板生成完整样式表
};

#endif // THEMEMANAGER_H
