#include "mainwindow.h"
#include <QApplication>
#include <QStyle>         // 为了 QStyle 类和标准图标枚举

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 设置窗口位置和大小
    this->setGeometry(300, 150, 500, 300);

    // 创建工具栏，父对象是 this（MainWindow）
    tbar = new QToolBar(this);

    // 手动设置工具栏位置和大小（一般不需要这样，见下方说明）
    tbar->setGeometry(20, 20, 200, 90);

    // 获取当前应用程序的"样式"对象
    // QStyle 是 Qt 的样式抽象类，管理所有控件的外观
    QStyle *sty = QApplication::style();

    // 从样式中获取一个"标准图标"
    // SP_TitleBarContextHelpButton = 标题栏上的"?"帮助按钮图标
    QIcon ico = sty->standardIcon(QStyle::SP_TitleBarContextHelpButton);

    // 创建工具按钮，但没传父对象！（后面 addWidget 时会自动改父对象）
    tbutton = new QToolButton(tbar);
    // 设置按钮图标
    tbutton->setIcon(ico);

    // 设置按钮文字
    tbutton->setText("系统帮助提示");

    // 设置按钮的显示样式：
    // ToolButtonTextUnderIcon = 图标在上，文字在下
    tbutton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    // 把按钮添加到工具栏
    // addWidget 后，tbutton 的父对象自动变成 tbar
    tbar->addWidget(tbutton);
}

MainWindow::~MainWindow() = default;