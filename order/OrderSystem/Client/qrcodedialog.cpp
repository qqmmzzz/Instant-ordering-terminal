#include "qrcodedialog.h"

/*
 * 二维码结算弹窗构造函数
 * imagePath：二维码图片路径
 * parent：父窗口
 */
QRCodeDialog::QRCodeDialog(const QString &imagePath, QWidget *parent)
    : QDialog(parent)  // 继承自弹窗窗口
{
    // 窗口基础设置
    setWindowTitle("结算二维码");    // 窗口标题
    setFixedSize(320, 400);           // 固定窗口大小（宽320，高400）
    // 去掉问号帮助按钮
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    // 主垂直布局（所有控件从上到下排列）
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20);  // 窗口内边距
    mainLayout->setAlignment(Qt::AlignCenter);      // 整体居中

    // ===================== 1. 标题标签：扫码结算 =====================
    QLabel *lblTitle = new QLabel("扫码结算");
    lblTitle->setAlignment(Qt::AlignCenter);         // 文字居中
    lblTitle->setStyleSheet("font-size: 20px; font-weight: bold; color: #2c3e50; padding: 8px;");
    mainLayout->addWidget(lblTitle);

    // ===================== 2. 二维码显示区域 =====================
    QLabel *lblQR = new QLabel();
    lblQR->setFixedSize(200, 200);          // 二维码固定大小 200x200
    lblQR->setAlignment(Qt::AlignCenter);   // 图片居中
    // 灰色边框 + 白色背景 + 圆角
    lblQR->setStyleSheet("QLabel { border: 2px solid #bdc3c7; border-radius: 8px; background-color: #fff; }");

    // 如果传入了图片路径，尝试加载图片
    if (!imagePath.isEmpty()) {
        QPixmap pixmap(imagePath);
        if (!pixmap.isNull()) {
            // 加载成功：缩放显示二维码
            lblQR->setPixmap(pixmap.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            // 加载失败：显示错误文字
            lblQR->setText("二维码\n加载失败");
            lblQR->setStyleSheet("QLabel { border: 2px solid #e74c3c; border-radius: 8px; "
                                 "background-color: #fff; color: #e74c3c; font-size: 14px; }");
        }
    } else {
        // 没有传入图片路径：显示提示文字
        lblQR->setText("未设置\n二维码图片");
        lblQR->setStyleSheet("QLabel { border: 2px solid #95a5a6; border-radius: 8px; "
                             "background-color: #fff; color: #95a5a6; font-size: 14px; }");
    }
    // 将二维码控件添加到布局，并居中
    mainLayout->addWidget(lblQR, 0, Qt::AlignCenter);

    // ===================== 3. 提示文字 =====================
    QLabel *lblHint = new QLabel("请使用手机扫码完成结算");
    lblHint->setAlignment(Qt::AlignCenter);
    lblHint->setStyleSheet("font-size: 13px; color: #7f8c8d; padding: 4px;");
    mainLayout->addWidget(lblHint);

    // ===================== 4. 确认按钮 =====================
    QPushButton *btnConfirm = new QPushButton("确  认");
    btnConfirm->setFixedSize(120, 40);        // 固定按钮大小
    // 绿色按钮样式
    btnConfirm->setStyleSheet(
        "QPushButton { background-color: #27ae60; color: white; font-size: 15px;"
        "   font-weight: bold; border: none; border-radius: 6px; }"
        "QPushButton:hover { background-color: #219a52; }");
    // 点击按钮 → 关闭弹窗
    connect(btnConfirm, &QPushButton::clicked, this, &QDialog::accept);

    // 按钮水平布局（让按钮居中）
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addStretch();           // 左侧弹簧
    btnLayout->addWidget(btnConfirm);  // 按钮
    btnLayout->addStretch();           // 右侧弹簧
    mainLayout->addLayout(btnLayout);
}
