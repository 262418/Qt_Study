#include "mainwindow.h"
#include <QDebug>               // 用于输出调试信息到控制台

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 设置窗口位置和大小
    this->setGeometry(400, 300, 500, 300);

    // 创建对话框按钮盒，父对象是 this
    qdbb = new QDialogButtonBox(this);

    // 设置按钮盒位置和大小
    qdbb->setGeometry(80, 80, 250, 150);

    // 添加一个"标准取消按钮"
    // QDialogButtonBox::Cancel 是内置的标准按钮枚举
    // addButton(StandardButton) 会自动创建对应的按钮并加入盒中
    qdbb->addButton(QDialogButtonBox::Cancel);

    // 修改刚添加的标准取消按钮的文字为中文"取消"
    // button(StandardButton) 返回对应的 QPushButton 指针
    qdbb->button(QDialogButtonBox::Cancel)->setText("取消");

    // 创建自定义按钮，注意这里没传父对象
    qpb = new QPushButton("自定义");

    // 把自定义按钮加入按钮盒
    // ActionRole 表示这个按钮扮演"动作"角色
    qdbb->addButton(qpb, QDialogButtonBox::ActionRole);

    // 连接信号槽（旧式语法）
    // clicked(QAbstractButton*) 是按钮盒的信号，任何内部按钮被点击都会发出
    // 参数是被点击的那个按钮指针
    connect(qdbb, SIGNAL(clicked(QAbstractButton*)),
            this, SLOT(qdbbqpbClicked(QAbstractButton*)));
}

MainWindow::~MainWindow() = default;

// 槽函数：处理按钮点击
void MainWindow::qdbbqpbClicked(QAbstractButton *qab)
{
    // 通过指针比较，判断是哪个按钮被点了
    if (qab == qdbb->button(QDialogButtonBox::Cancel)) {
        qDebug() << "你已经点击【取消】按钮";
    }
    else if (qab == qpb) {
        qDebug() << "你已经点击【自定义】按钮";
    }
}