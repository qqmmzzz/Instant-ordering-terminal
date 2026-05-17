#ifndef QRCODEDIALOG_H
#define QRCODEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QMessageBox>

/**
 * @brief 结算二维码对话框
 * 退出时显示结算二维码图片，大小200x200。
 */
class QRCodeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QRCodeDialog(const QString &imagePath, QWidget *parent = nullptr);
};

#endif // QRCODEDIALOG_H
