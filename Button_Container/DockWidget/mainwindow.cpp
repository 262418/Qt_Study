#include "mainwindow.h"
#include "ui_mainwindow.h"    // Qt Designer 自动生成的 UI 类
#include <QDockWidget>        // 停靠窗口
#include <QLabel>             // 标签
#include <QComboBox>          // 下拉框
#include <QGridLayout>        // 网格布局（注意小写，不规范）
#include <QpushButton>        // 按钮（注意大小写错误）

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)   // 创建 UI 对象
{
    ui->setupUi(this);         // 加载 .ui 文件定义的界面

    // ---------- 创建停靠窗口 ----------
    QDockWidget *qdw = new QDockWidget(
        "停靠窗口部件测试:Dock Widget-->ABC",   // 标题
        this                                     // 父对象：主窗口
        );

    // ---------- 设置背景色为青色 ----------
    QPalette qp;                          // 调色板对象
    qp.setColor(QPalette::Window, Qt::cyan);   // 设置"窗口"颜色角色为青色
    qdw->setAutoFillBackground(true);     // 关键：开启自动填充背景，否则调色板不生效
    qdw->setPalette(qp);                  // 应用调色板

    // 设置停靠窗口最大尺寸 300×300
    qdw->setMaximumSize(300, 300);

    // ---------- 创建停靠窗口内部控件 ----------
    QLabel *ql = new QLabel("学历层次:");
    QComboBox *qcb = new QComboBox();
    qcb->addItem("小学");
    qcb->addItem("初中");
    qcb->addItem("高中");
    qcb->addItem("专科");
    qcb->addItem("本科");
    qcb->addItem("硕士");
    qcb->addItem("博士");

    QPushButton *qpb1 = new QPushButton("清华大学");
    QPushButton *qpb2 = new QPushButton("北京大学");

    // ---------- 网格布局 ----------
    QGridLayout *qgl = new QGridLayout();
    qgl->addWidget(ql,   0, 0, 1, 1);   // 第0行第0列
    qgl->addWidget(qcb,  0, 1, 1, 1);   // 第0行第1列
    qgl->addWidget(qpb1, 1, 0, 1, 1);   // 第1行第0列
    qgl->addWidget(qpb2, 1, 1, 1, 1);   // 第1行第1列

    qgl->setHorizontalSpacing(10);      // 水平间距 10 像素
    qgl->setVerticalSpacing(10);        // 垂直间距 10 像素

    // ---------- 把布局装到 QWidget，再设为停靠窗口内容 ----------
    QWidget *qw = new QWidget();
    qw->setLayout(qgl);
    qdw->setWidget(qw);
}

MainWindow::~MainWindow()
{
    delete ui;   // 释放 UI 对象
}