#ifndef ALPHAKEYBOARDWIDGET_H
#define ALPHAKEYBOARDWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>

class AlphaKeyboardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AlphaKeyboardWidget(QWidget *parent = nullptr);
    ~AlphaKeyboardWidget();

    void setTargetInput(QLineEdit *target);
    void setPositionAbove(bool above);

private slots:
    void onKeyPressed();
    void onBackspace();
    void onClear();
    void onConfirm();
    void onToggleShift();

private:
    QLineEdit *m_targetInput;
    bool m_positionAbove;
    bool m_shiftMode;
    QGridLayout *m_gridLayout;
    QList<QPushButton*> m_keyButtons;

    QString m_normalKeys[30];
    QString m_shiftKeys[30];
};

#endif // ALPHAKEYBOARDWIDGET_H