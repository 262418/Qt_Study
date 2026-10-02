#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 设置窗口位置和大小：屏幕(300,150)处，宽500高300
    this->setGeometry(300, 150, 500, 300);

    // 创建两个单选按钮，父对象都是 this
    qrb1 = new QRadioButton(this);
    qrb2 = new QRadioButton(this);

    // 设置按钮位置和大小（相对父窗口）
    qrb1->setGeometry(20, 20, 150, 40);   // 左上角(20,20)，宽150高40
    qrb2->setGeometry(20, 80, 150, 40);

    // 设置按钮显示的文字
    qrb1->setText("选择按钮1");
    qrb2->setText("选择按钮2");

    // 设置选中状态
    qrb1->setChecked(true);    // 按钮1默认选中
    qrb2->setChecked(false);   // 按钮2默认不选中
}

MainWindow::~MainWindow() = default;