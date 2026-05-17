#ifndef ADDDISHDIALOG_H
#define ADDDISHDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QFormLayout>
#include <QMessageBox>
#include <QFileDialog>

class AddDishDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDishDialog(QWidget *parent = nullptr);

    QString getDishName() const;
    double getPrice() const;
    int getStock() const;
    QString getDescription() const;
    QString getImagePath() const;   // 返回复制后的最终路径
    int getStatus() const;

    void setDishInfo(int dishId, const QString &name, double price, int stock, 
                     const QString &desc, const QString &imgPath, int status);

private slots:
    void onBtnSelectImage();
    void onBtnConfirm();

private:
    QLineEdit       *m_editName;
    QDoubleSpinBox  *m_spinPrice;
    QSpinBox        *m_spinStock;
    QLineEdit       *m_editDesc;
    QLineEdit       *m_editImagePath;
    QPushButton     *m_btnSelectImage;
    QLabel          *m_lblImagePreview;
    QLabel          *m_lblImageHint;
    QComboBox       *m_comboStatus;
    QPushButton     *m_btnConfirm;
    QPushButton     *m_btnCancel;

    QString m_finalImagePath;  // 复制后的最终图片路径
    int     m_editDishId;      // 编辑模式下的菜品ID
};

#endif // ADDDISHDIALOG_H
