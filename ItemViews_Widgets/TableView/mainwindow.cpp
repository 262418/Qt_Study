#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItemModel>    // ⭐ 通用模型：可以存多列、多行、带图标

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);          // 加载 .ui 界面
    InitTableViewFunc();         // 初始化表格
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ==================== 初始化表格 ====================
void MainWindow::InitTableViewFunc()
{
    // ==================== 创建模型 ====================
    QStandardItemModel *qsim = new QStandardItemModel();

    // ---------- 设置水平表头（列标题） ----------
    // setHorizontalHeaderItem(列号, QStandardItem*)
    qsim->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("学号")));
    qsim->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("姓名")));
    qsim->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("性别")));
    qsim->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("分数")));
    // QObject::tr() 用于国际化翻译，这里可以省略

    // ==================== 绑定模型到视图 ====================
    ui->tableView->setModel(qsim);

    // ---------- 设置列宽 ----------
    ui->tableView->setColumnWidth(0, 120);   // 第 0 列（学号）宽度 120 像素
    // 其它 3 列没有设置，会用默认宽度

    // ==================== 填充数据 ====================
    // setItem(行号, 列号, QStandardItem*)
    // 第 0 行
    qsim->setItem(0, 0, new QStandardItem("2022001"));
    qsim->setItem(0, 1, new QStandardItem("A"));
    qsim->setItem(0, 2, new QStandardItem("男"));
    qsim->setItem(0, 3, new QStandardItem("714"));

    // 第 1 行
    qsim->setItem(1, 0, new QStandardItem("2022002"));
    qsim->setItem(1, 1, new QStandardItem("B"));
    qsim->setItem(1, 2, new QStandardItem("男"));
    qsim->setItem(1, 3, new QStandardItem("712"));

    // 第 2 行
    qsim->setItem(2, 0, new QStandardItem("2022003"));
    qsim->setItem(2, 1, new QStandardItem("C"));
    qsim->setItem(2, 2, new QStandardItem("男"));
    qsim->setItem(2, 3, new QStandardItem("704"));

    // ==================== 禁止编辑 ====================
    // EditTrigger 控制"什么操作会进入编辑状态"
    // NoEditTriggers：任何操作都不触发编辑
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // ==================== 排序 ====================
    // sort(列号, 排序方式)
    // 按第 3 列（分数）降序排列
    qsim->sort(3, Qt::DescendingOrder);
}