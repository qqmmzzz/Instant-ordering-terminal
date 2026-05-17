#ifndef THEMECOLORDIALOG_H
#define THEMECOLORDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

/*
主题颜色选择对话框
显示12种颜色主题供用户选择，每种显示色块预览。
*/
class ThemeColorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ThemeColorDialog(const QStringList &themeNames,
                              const QList<QColor> &previewColors,
                              int currentIndex,
                              QWidget *parent = nullptr);

signals:
    void themeSelected(int index);

private:
    QGridLayout *m_gridLayout;
    int m_selectedIndex;
};

#endif // THEMECOLORDIALOG_H
