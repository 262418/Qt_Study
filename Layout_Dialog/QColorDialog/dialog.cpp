#include "dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("颜色对话框测试");

    // ==================== 主布局 ====================
    glayout = new QGridLayout(this);   // 直接成为 Dialog 的布局

    // ==================== 按钮 ====================
    colorbutton = new QPushButton("调用颜色对话框");

    // ==================== 颜色框架 ====================
    colorFrame = new QFrame;

    // 设置框架的形状
    // QFrame::Box = 四周有边框
    colorFrame->setFrameShape(QFrame::Box);

    // 关键：让框架自动填充背景
    // 不设这个，setPalette 设置的颜色不会显示
    colorFrame->setAutoFillBackground(true);

    // ==================== 布局 ====================
    glayout->addWidget(colorbutton, 0, 0);   // 第 0 行第 0 列
    glayout->addWidget(colorFrame,  1, 0);   // 第 1 行第 0 列

    // ==================== 信号槽 ====================
    connect(colorbutton, SIGNAL(clicked()), this, SLOT(dispcolorFunc()));
}

Dialog::~Dialog() = default;

// ==================== 打开颜色对话框并更新 ====================
void Dialog::dispcolorFunc()
{
    // 弹出颜色对话框，初始颜色是红色
    QColor colorvalues = QColorDialog::getColor(Qt::red);

    // 判断用户是否选了颜色（点了确定）
    if (colorvalues.isValid()) {
        // 设置框架的背景色
        colorFrame->setPalette(QPalette(colorvalues));
        // 等价于：
        // QPalette pal;
        // pal.setColor(QPalette::Window, colorvalues);
        // colorFrame->setPalette(pal);
    }
    // 如果用户点了"取消"，colorvalues 无效，什么都不做
}