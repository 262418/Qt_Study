#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InitTreeViewFunc();             // 初始化树
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ==================== 初始化树视图 ====================
void MainWindow::InitTreeViewFunc()
{
    // ---------- 创建模型，父对象是 treeView ----------
    qsim = new QStandardItemModel(ui->treeView);

    // ---------- 设置表头 ----------
    qsim->setHorizontalHeaderLabels(
        QStringList() << QStringLiteral("编号") << QStringLiteral("初中部|高中部")
        );
    // QStringLiteral 是编译期字符串优化宏，可替代 tr()

    // ==================== 一级节点：初中部 ====================
    QList<QStandardItem*> item1;                  // 一行两个单元格
    QStandardItem *qsi1 = new QStandardItem(QString::number(1));   // 第0列：编号 "1"
    QStandardItem *qsi2 = new QStandardItem("初中部");              // 第1列：名称
    item1.append(qsi1);
    item1.append(qsi2);
    qsim->appendRow(item1);                       // 加入模型作为根节点

    // ==================== 二级节点：一年级 ====================
    QList<QStandardItem*> item11;
    QStandardItem *qsi11 = new QStandardItem(QString::number(2));  // 编号 "2"
    QStandardItem *qsi21 = new QStandardItem("一年级");
    item11.append(qsi11);
    item11.append(qsi21);

    // 关键：appendRow 到 qsi1（而不是 qsim）
    // 这会让 item11 成为 qsi1 的子节点
    qsi1->appendRow(item11);

    // ==================== 三级节点：一班、二班、三班 ====================
    // 一班
    QList<QStandardItem*> item111;
    QStandardItem *qsi111 = new QStandardItem(QString::number(3));
    QStandardItem *qsi211 = new QStandardItem("一班");
    item111.append(qsi111);
    item111.append(qsi211);
    qsi11->appendRow(item111);                     // 加到 qsi11 下

    // 二班
    QList<QStandardItem*> item112;
    QStandardItem *qsi112 = new QStandardItem(QString::number(3));
    QStandardItem *qsi212 = new QStandardItem("二班");
    item112.append(qsi112);
    item112.append(qsi212);
    qsi11->appendRow(item112);

    // 三班
    QList<QStandardItem*> item113;
    QStandardItem *qsi113 = new QStandardItem(QString::number(3));
    QStandardItem *qsi213 = new QStandardItem("三班");
    item113.append(qsi113);
    item113.append(qsi213);
    qsi11->appendRow(item113);

    // ==================== 一级节点：高中部 ====================
    QList<QStandardItem*> item2;
    QStandardItem *qsi3 = new QStandardItem(QString::number(2));
    QStandardItem *qsi4 = new QStandardItem("高中部");
    item2.append(qsi3);
    item2.append(qsi4);
    qsim->appendRow(item2);


    // ---------- 把模型设置给视图 ----------
    ui->treeView->setModel(qsim);
}