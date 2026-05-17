#ifndef NUMPADWIDGET_H
#define NUMPADWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>

class NumpadWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NumpadWidget(QWidget *parent = nullptr);
    ~NumpadWidget();

    void setTargetInput(QLineEdit *target);
    void setPositionAbove(bool above);

private slots:
    void onKeyPressed();
    void onBackspace();
    void onClear();
    void onConfirm();

private:
    QLineEdit *m_targetInput;
    bool m_positionAbove;
    QGridLayout *m_gridLayout;
};

#endif // NUMPADWIDGET_H