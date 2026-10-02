#include "dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("字体对话框测试");

    // ==================== 主布局 ====================
    glayout = new QGridLayout(this);   // 直接成为 Dialog 的布局

    // ==================== 按钮 ====================
    fontbutton = new QPushButton("调用字体对话框");

    // ==================== 输入框 ====================
    fontlineedit = new QLineEdit;
    fontlineedit->setText("英语四级通过");   // 设置初始文字

    // ==================== 布局 ====================
    glayout->addWidget(fontbutton,   0, 0);   // 第 0 行第 0 列：按钮
    glayout->addWidget(fontlineedit, 0, 1);   // 第 0 行第 1 列：输入框

    // ==================== 信号槽 ====================
    connect(fontbutton, SIGNAL(clicked()), this, SLOT(dispFontFunc()));
}

Dialog::~Dialog() = default;

// ==================== 打开字体对话框并应用 ====================
void Dialog::dispFontFunc()
{
    bool isbool;   // 用于接收"用户是否点了确定"

    // 弹出字体对话框
    // QFontDialog::getFont(&ok, ...) 通过参数返回用户是否确认
    QFont font = QFontDialog::getFont(&isbool);

    // 如果用户点了"确定"
    if (isbool) {
        fontlineedit->setFont(font);   // 把选中的字体应用到输入框
    }
    // 用户点"取消" → isbool 为 false → 不做任何事
}