#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);       // 加载 .ui 界面

    // ==================== 设置表格尺寸 ====================
    // setRowCount(行数) / setColumnCount(列数)
    ui->tableWidget->setRowCount(3);        // 3 行数据
    ui->tableWidget->setColumnCount(2);     // 2 列

    // ==================== 设置表头 ====================
    QStringList slist;
    slist << "学号" << "高考分数";

    // setHorizontalHeaderLabels 一次性设置所有列标题
    ui->tableWidget->setHorizontalHeaderLabels(slist);

    // ==================== 准备数据 ====================
    QList<QString> strno;
    strno << "202201" << "202202" << "202203";

    QList<QString> strscore;
    strscore << "708" << "712" << "690";

    // ==================== 填充单元格 ====================
    for (int i = 0; i < 3; i++) {
        int iCol = 0;   // 列计数器，初始 0

        // 第 0 列：学号
        QTableWidgetItem *pitem = new QTableWidgetItem(strno.at(i));
        ui->tableWidget->setItem(i, iCol++, pitem);   // 先设，后 ++
        // setItem(行, 列, 项)

        // 第 1 列：分数
        // iCol++ 后变成 1，正好是第 1 列
        ui->tableWidget->setItem(i, iCol,
                                 new QTableWidgetItem(strscore.at(i)));
    }
}

Widget::~Widget()
{
    delete ui;   // 释放 UI 对象
}