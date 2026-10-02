#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 设置窗口运行位置和大小
    // setGeometry(x, y, width, height)
    this->setGeometry(300, 150, 500, 300);
    //       ↑屏幕x  ↑屏幕y  ↑宽    ↑高

    // 创建两个按钮，父对象都是 this（MainWindow），自动管理内存
    pb1 = new QPushButton("命令按钮1", this);   // 按钮文字"命令按钮1"
    pb2 = new QPushButton("命令按钮2", this);

    // 手动设置按钮位置和大小（不用布局管理器）
    // setGeometry(x, y, width, height) 相对于父窗口的坐标
    pb1->setGeometry(20, 20, 150, 50);   // 左上角(20,20)，宽150，高50
    pb2->setGeometry(20, 90, 150, 50);   // 左上角(20,90)，宽150，高50

    // 信号槽连接（旧式语法）
    // 点按钮1 → 调用 pushbutton1_clicked()
    connect(pb1, SIGNAL(clicked()), this, SLOT(pushbutton1_clicked()));
    // 点按钮2 → 调用 pushbutton2_clicked()
    connect(pb2, SIGNAL(clicked()), this, SLOT(pushbutton2_clicked()));
}

MainWindow::~MainWindow() = default;    // 析构函数用默认实现

// 槽函数1：按钮1被点击时执行
void MainWindow::pushbutton1_clicked() {
    // setStyleSheet 用 CSS 语法设置控件样式
    // QMainWindow{background-color:...} 表示"这个 QMainWindow 的背景色"
    // rgba(255, 255, 0, 100%) = 红色255，绿色255，蓝色0，不透明度100%
    //                        = 黄色
    this->setStyleSheet(
        "QMainWindow{background-color:rgba(255,255,0,100%)}"
        );
}

// 槽函数2：按钮2被点击时执行
void MainWindow::pushbutton2_clicked() {
    // rgba(255, 0, 0, 100%) = 红色
    this->setStyleSheet(
        "QMainWindow{background-color:rgba(255,0,0,100%)}"
        );
}