#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // ==================== 清华大学（一级节点） ====================
    // 构造时直接传 ui->treeWidget，自动加入树
    QTreeWidgetItem *topitem1 = new QTreeWidgetItem(ui->treeWidget);

    topitem1->setText(0, "清华大学");              // 第 0 列显示文字
    topitem1->setCheckState(0, Qt::Checked);        // 第 0 列加勾选框并选中

    ui->treeWidget->addTopLevelItem(topitem1);

    // ==================== 树整体属性 ====================
    ui->treeWidget->setHeaderHidden(true);          // 隐藏表头
    ui->treeWidget->expandAll();                    // 展开所有节点

    // ==================== 清华大学的子节点 ====================
    // 用 topitem1 作为父节点，自动成为其子项
    QTreeWidgetItem *item11 = new QTreeWidgetItem(topitem1);
    item11->setText(0, "清华大学建筑学院");
    item11->setCheckState(0, Qt::Checked);

    QTreeWidgetItem *item12 = new QTreeWidgetItem(topitem1);
    item12->setText(0, "清华大学计算机学院");
    item12->setCheckState(0, Qt::Checked);

    QTreeWidgetItem *item13 = new QTreeWidgetItem(topitem1);
    item13->setText(0, "清华大学土木学院");
    item13->setCheckState(0, Qt::Checked);

    QTreeWidgetItem *item14 = new QTreeWidgetItem(topitem1);
    item14->setText(0, "清华大学马克思主义学院");
    item14->setCheckState(0, Qt::Checked);

    QTreeWidgetItem *item15 = new QTreeWidgetItem(topitem1);
    item15->setText(0, "清华大学医学院");
    item15->setCheckState(0, Qt::Checked);

    // ==================== 北京大学（一级节点） ====================
    QTreeWidgetItem *topitem2 = new QTreeWidgetItem(ui->treeWidget);
    topitem2->setText(0, "北京大学");
    topitem2->setCheckState(0, Qt::Checked);
    ui->treeWidget->addTopLevelItem(topitem2);

    // ==================== 北京大学的子节点 ====================
    QTreeWidgetItem *item21 = new QTreeWidgetItem(topitem2);
    item21->setText(0, "北京大学建筑学院");
    item21->setCheckState(0, Qt::Checked);

    QTreeWidgetItem *item22 = new QTreeWidgetItem(topitem2);
    item22->setText(0, "北京大学计算机学院");
    item22->setCheckState(0, Qt::Checked);
}

Widget::~Widget()
{
    delete ui;
}