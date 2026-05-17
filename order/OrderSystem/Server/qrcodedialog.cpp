#include "qrcodedialog.h"

// 构造函数：显示结算二维码的弹窗
QRCodeDialog::QRCodeDialog(const QString &imagePath, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("结算二维码");
    setFixedSize(320, 400); // 固定弹窗大小
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setAlignment(Qt::AlignCenter); // 内容居中

    // 标题
    QLabel *lblTitle = new QLabel("扫码结算");
    lblTitle->setAlignment(Qt::AlignCenter);
    lblTitle->setStyleSheet("font-size: 20px; font-weight: bold; color: #2c3e50; padding: 8px;");
    mainLayout->addWidget(lblTitle);

    // 二维码图片显示区域（200x200 固定大小）
    QLabel *lblQR = new QLabel();
    lblQR->setFixedSize(200, 200);
    lblQR->setAlignment(Qt::AlignCenter);
    lblQR->setStyleSheet("QLabel { border: 2px solid #bdc3c7; border-radius: 8px; background-color: #fff; }");

    // 根据图片路径是否存在显示不同内容
    if (!imagePath.isEmpty()) {
        QPixmap pixmap(imagePath);
        if (!pixmap.isNull()) {
            // 缩放图片适配200x200区域，保持宽高比
            lblQR->setPixmap(pixmap.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
        else
        {
            // 图片加载失败时显示错误提示
            lblQR->setText("二维码\n加载失败");
            lblQR->setStyleSheet("QLabel { border: 2px solid #e74c3c; border-radius: 8px; "
                                 "background-color: #fff; color: #e74c3c; font-size: 14px; }");
        }
    } else {
        // 未设置二维码图片时显示占位提示
        lblQR->setText("未设置\n二维码图片");
        lblQR->setStyleSheet("QLabel { border: 2px solid #95a5a6; border-radius: 8px; "
                             "background-color: #fff; color: #95a5a6; font-size: 14px; }");
    }
    mainLayout->addWidget(lblQR, 0, Qt::AlignCenter);

    // 操作提示文字
    QLabel *lblHint = new QLabel("请使用手机扫码完成结算");
    lblHint->setAlignment(Qt::AlignCenter);
    lblHint->setStyleSheet("font-size: 13px; color: #7f8c8d; padding: 4px;");
    mainLayout->addWidget(lblHint);

    // 确认按钮（绿色，关闭对话框）
    QPushButton *btnConfirm = new QPushButton("确  认");
    btnConfirm->setFixedSize(120, 40);
    btnConfirm->setStyleSheet(
        "QPushButton { background-color: #27ae60; color: white; font-size: 15px;"
        "   font-weight: bold; border: none; border-radius: 6px; }"
        "QPushButton:hover { background-color: #219a52; }");
    connect(btnConfirm, &QPushButton::clicked, this, &QDialog::accept);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addWidget(btnConfirm);
    btnLayout->addStretch(); // 按钮居中
    mainLayout->addLayout(btnLayout);
}
