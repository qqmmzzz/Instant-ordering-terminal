#include "adddishdialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDir>
#include <QFile>
#include <QPixmap>
#include <QDateTime>
#include <QFileInfo>
#include <QtDebug>

// 构造函数：初始化添加/编辑菜品的对话框界面
AddDishDialog::AddDishDialog(QWidget *parent)
    : QDialog(parent), m_editDishId(-1) // -1 表示新增模式，非编辑模式
{
    setWindowTitle("添加菜品");
    setFixedSize(460, 560); // 固定窗口大小
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint); // 移除问号按钮

    // 主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(30, 15, 30, 15);
    mainLayout->setSpacing(8);

    // 顶部标题
    QLabel *lblTitle = new QLabel("添加新菜品");
    lblTitle->setAlignment(Qt::AlignCenter);
    lblTitle->setStyleSheet("font-size: 18px; font-weight: bold; color: #2c3e50; padding: 6px;");
    mainLayout->addWidget(lblTitle);

    // 表单布局：菜品名称、单价、库存、描述、状态
    QFormLayout *formLayout = new QFormLayout();
    formLayout->setSpacing(10);

    // 菜品名称输入框
    m_editName = new QLineEdit();
    m_editName->setPlaceholderText("请输入菜品名称");
    m_editName->setMinimumHeight(30);
    formLayout->addRow("菜品名称：", m_editName);

    // 单价输入框（双精度浮点数，保留两位小数）
    m_spinPrice = new QDoubleSpinBox();
    m_spinPrice->setRange(0.01, 9999.99); // 价格范围
    m_spinPrice->setDecimals(2);
    m_spinPrice->setPrefix("￥"); // 货币前缀
    m_spinPrice->setValue(10.00); // 默认价格
    m_spinPrice->setMinimumHeight(30);
    formLayout->addRow("菜品单价：", m_spinPrice);

    // 库存数量输入框
    m_spinStock = new QSpinBox();
    m_spinStock->setRange(0, 9999);
    m_spinStock->setValue(50); // 默认库存
    m_spinStock->setMinimumHeight(30);
    formLayout->addRow("菜品库存：", m_spinStock);

    // 描述输入框（可选）
    m_editDesc = new QLineEdit();
    m_editDesc->setPlaceholderText("简短描述（可选）");
    m_editDesc->setMinimumHeight(30);
    formLayout->addRow("菜品描述：", m_editDesc);

    // 上架状态下拉框：上架(1) / 下架(0)
    m_comboStatus = new QComboBox();
    m_comboStatus->addItem("上架", 1);
    m_comboStatus->addItem("下架", 0);
    m_comboStatus->setMinimumHeight(30);
    formLayout->addRow("上架状态：", m_comboStatus);

    mainLayout->addLayout(formLayout);

    // ===== 图片选择区域 =====
    QLabel *lblImgTitle = new QLabel("菜品图片：");
    lblImgTitle->setStyleSheet("font-weight: bold; font-size: 13px;");
    mainLayout->addWidget(lblImgTitle);

    // 图片格式建议提示
    m_lblImageHint = new QLabel(
        "建议：正方形图片，200×200以上，JPG/PNG格式，文件小于2MB");
    m_lblImageHint->setStyleSheet("color: #e67e22; font-size: 11px; padding: 2px 4px;");
    m_lblImageHint->setWordWrap(true);
    mainLayout->addWidget(m_lblImageHint);

    // 图片路径显示 + 选择按钮（水平布局）
    QHBoxLayout *imgPathLayout = new QHBoxLayout();
    m_editImagePath = new QLineEdit();
    m_editImagePath->setReadOnly(true); // 只读，通过按钮选择
    m_editImagePath->setPlaceholderText("点击右侧按钮选择图片");
    m_editImagePath->setMinimumHeight(30);

    m_btnSelectImage = new QPushButton("选择图片");
    m_btnSelectImage->setStyleSheet(
        "QPushButton { background-color: #27ae60; color: white; font-weight: bold;"
        "   padding: 5px 12px; border-radius: 4px; }"
        "QPushButton:hover { background-color: #219a52; }");
    m_btnSelectImage->setMinimumWidth(80);
    connect(m_btnSelectImage, &QPushButton::clicked, this, &AddDishDialog::onBtnSelectImage);

    imgPathLayout->addWidget(m_editImagePath, 1); // 路径框占拉伸空间
    imgPathLayout->addWidget(m_btnSelectImage);
    mainLayout->addLayout(imgPathLayout);

    // 图片预览标签（100x100，虚线边框）
    m_lblImagePreview = new QLabel("暂无图片");
    m_lblImagePreview->setFixedSize(100, 100);
    m_lblImagePreview->setAlignment(Qt::AlignCenter);
    m_lblImagePreview->setStyleSheet(
        "QLabel { border: 2px dashed #bdc3c7; border-radius: 8px; "
        "background-color: #fafafa; color: #aaa; font-size: 11px; }");

    QHBoxLayout *previewLayout = new QHBoxLayout();
    previewLayout->addWidget(m_lblImagePreview);
    previewLayout->addStretch(); // 右推，居左显示
    mainLayout->addLayout(previewLayout);

    // ===== 底部按钮 =====
    QHBoxLayout *btnLayout = new QHBoxLayout();

    // 确认按钮（橙色醒目）
    m_btnConfirm = new QPushButton("确认添加");
    m_btnConfirm->setMinimumHeight(38);
    m_btnConfirm->setStyleSheet(
        "QPushButton { background-color: #e67e22; color: white; font-size: 15px;"
        "   font-weight: bold; border: none; border-radius: 5px; padding: 6px 20px; }"
        "QPushButton:hover { background-color: #d35400; }");
    connect(m_btnConfirm, &QPushButton::clicked, this, &AddDishDialog::onBtnConfirm);

    // 取消按钮（灰色）
    m_btnCancel = new QPushButton("取  消");
    m_btnCancel->setMinimumHeight(38);
    m_btnCancel->setStyleSheet(
        "QPushButton { background-color: #bdc3c7; color: #2c3e50; font-size: 15px;"
        "   font-weight: bold; border: none; border-radius: 5px; padding: 6px 20px; }"
        "QPushButton:hover { background-color: #aeb6bf; }");
    connect(m_btnCancel, &QPushButton::clicked, this, &QDialog::reject); // 直接关闭对话框

    btnLayout->addStretch();
    btnLayout->addWidget(m_btnConfirm);
    btnLayout->addWidget(m_btnCancel);
    btnLayout->addStretch(); // 按钮居中
    mainLayout->addLayout(btnLayout);
}

// Getter方法：获取去除首尾空格后的菜品名称
QString AddDishDialog::getDishName() const { return m_editName->text().trimmed(); }
double AddDishDialog::getPrice() const { return m_spinPrice->value(); }
int AddDishDialog::getStock() const { return m_spinStock->value(); }
QString AddDishDialog::getDescription() const { return m_editDesc->text().trimmed(); }
int AddDishDialog::getStatus() const { return m_comboStatus->currentData().toInt(); } // 返回当前选中项的data值(1或0)

// 返回复制后的最终图片路径（images/目录下的副本路径）
QString AddDishDialog::getImagePath() const { return m_finalImagePath; }

// ========== 设置菜品信息（编辑模式）==========
void AddDishDialog::setDishInfo(int dishId, const QString &name, double price, int stock,
                                 const QString &desc, const QString &imgPath, int status)
{
    m_editDishId = dishId; // 记录菜品ID，进入编辑模式
    setWindowTitle("编辑菜品");

    // 将已有数据填入表单
    m_editName->setText(name);
    m_spinPrice->setValue(price);
    m_spinStock->setValue(stock);
    m_editDesc->setText(desc);
    m_comboStatus->setCurrentIndex(status == 1 ? 0 : 1); // 1=上架(索引0), 0=下架(索引1)

    m_finalImagePath = imgPath;
    m_editImagePath->setText(imgPath);

    // 如果已有图片路径且文件存在，显示预览
    if (!imgPath.isEmpty() && QFile::exists(imgPath)) {
        QPixmap pixmap(imgPath);
        if (!pixmap.isNull()) {
            m_lblImagePreview->setPixmap(pixmap.scaled(96, 96, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            m_lblImagePreview->setStyleSheet(
                "QLabel { border: 2px solid #27ae60; border-radius: 8px; background-color: #fafafa; }");
        }
    }

    m_btnConfirm->setText("确认修改"); // 按钮文字切换为"确认修改"
}

// ========== 选择图片按钮 ==========
void AddDishDialog::onBtnSelectImage()
{
    // 打开文件选择对话框，筛选图片格式
    QString path = QFileDialog::getOpenFileName(this, "选择菜品图片", QString(),
        "图片文件 (*.png *.jpg *.jpeg *.bmp *.gif *.webp)");

    if (path.isEmpty()) return; // 用户取消选择

    // 检查文件大小：限制2MB以内
    QFileInfo fi(path);
    if (fi.size() > 2 * 1024 * 1024) {
        QMessageBox::warning(this, "提示", "图片文件过大（超过2MB），请选择更小的图片！");
        return;
    }

    m_editImagePath->setText(path); // 显示所选路径
    m_finalImagePath = path;  // 暂存原始路径，确认时再复制到images/

    // 预览所选图片
    QPixmap pixmap(path);
    if (!pixmap.isNull()) {
        m_lblImagePreview->setPixmap(pixmap.scaled(96, 96, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        m_lblImagePreview->setStyleSheet(
            "QLabel { border: 2px solid #27ae60; border-radius: 8px; background-color: #fafafa; }");
    }
}

// ========== 确认添加/修改 ==========
void AddDishDialog::onBtnConfirm()
{
    // 校验：菜名不能为空
    if (getDishName().isEmpty()) {
        QMessageBox::warning(this, "提示", "菜品名称不能为空！");
        m_editName->setFocus();
        return;
    }

    // 校验：单价必须大于0
    if (getPrice() <= 0) {
        QMessageBox::warning(this, "提示", "菜品单价必须大于0！");
        m_spinPrice->setFocus();
        return;
    }

    // 复制图片到 images/ 目录（统一管理图片文件）
    if (!m_finalImagePath.isEmpty()) {
        QDir dir;
        if (!dir.exists("images")) {
            dir.mkdir("images"); // 如果images目录不存在则创建
        }

        // 获取文件扩展名，默认为png
        QString ext = QFileInfo(m_finalImagePath).suffix();
        if (ext.isEmpty()) ext = "png";
        // 用时间戳生成唯一文件名，避免重名
        QString timestamp = QString::number(QDateTime::currentDateTime().toSecsSinceEpoch());
        QString destPath = QString("images/dish_%1.%2").arg(timestamp).arg(ext);

        // 先删除目标文件（如果存在），避免 QFile::copy 失败
        if (QFile::exists(destPath)) {
            QFile::remove(destPath);
        }

        // 执行复制，成功则更新为相对路径
        if (QFile::copy(m_finalImagePath, destPath)) 
        {
            m_finalImagePath = destPath;
            qDebug() << "图片复制成功:" << destPath;
        } 
        else 
        {
            QMessageBox::warning(this, "提示",
                "图片复制失败！\n请检查图片文件是否被其他程序占用。\n菜品将不包含图片。");
            m_finalImagePath.clear(); // 复制失败则清空图片路径
        }
    }

    accept(); // 关闭对话框，返回Accepted
}
