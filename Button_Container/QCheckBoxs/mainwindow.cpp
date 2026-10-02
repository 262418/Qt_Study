#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 设置窗口位置和大小
    this->setGeometry(300, 150, 500, 300);

    // 创建复选框，父对象是 this
    qcb = new QCheckBox(this);

    // 设置复选框位置和大小（相对父窗口）
    qcb->setGeometry(30, 50, 250, 50);

    // 设置初始状态为"选中"
    // 注意：这里用了 setCheckState 而不是 setChecked
    qcb->setCheckState(Qt::Checked);

    // 设置复选框显示的初始文字
    qcb->setText("初始化状态为：Checked状态");

    // 关键：启用三态（三态复选框）
    qcb->setTristate();

    // 连接信号槽（旧式语法）
    // stateChanged(int) 是 Qt6 里的信号，参数是 int
    // 在 Qt5 里是 stateChanged(int)，Qt6 里也是 int（枚举转 int）
    connect(qcb, SIGNAL(stateChanged(int)),
            this, SLOT(checkboxstate(int)));
}
MainWindow::~MainWindow() = default;

// 槽函数：处理状态变化
void MainWindow::checkboxstate(int istate)
{
    // istate 是整型，但实际值对应 Qt::CheckState 枚举
    switch (istate)
    {
    case Qt::Checked:              // 值为 2
        qcb->setText("选中状态ok");
        break;
    case Qt::Unchecked:            // 值为 0
        qcb->setText("未选中状态no");
        break;
    case Qt::PartiallyChecked:     // 值为 1
        qcb->setText("半选中状态");
        break;
    }
}