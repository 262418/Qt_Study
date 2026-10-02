#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);          // 加载 .ui 文件定义的界面

    resize(450, 250);

    // ==================== 创建列表视图 ====================
    qlv = new QListView(this);
    qlv->setGeometry(20, 20, 240, 160);   // 硬编码坐标

    // ==================== 准备数据 ====================
    QStringList qlist;                    // 字符串列表（数据容器）
    qlist.append("运动类:篮球、足球");
    qlist.append("游戏类:LOL、Hollow Knight");
    qlist.append("编程类:C++、Qt");

    // ==================== 创建模型并绑定 ====================
    // QStringListModel 把 QStringList 包装成 Qt 的 Model
    QStringListModel *qslm = new QStringListModel(qlist);

    // 把模型设置给视图（视图从模型取数据）
    qlv->setModel(qslm);

    // ==================== 信号槽连接 ====================
    // clicked 信号带 QModelIndex 参数
    connect(qlv, SIGNAL(clicked(const QModelIndex)),
            this, SLOT(SlotClickedFunc(const QModelIndex)));
}

Widget::~Widget()
{
    delete ui;   // 释放 UI 对象
}

// ==================== 点击项的处理 ====================
void Widget::SlotClickedFunc(const QModelIndex &index)
{
    // index.data() 获取该项的显示数据，返回 QVariant
    // toString() 把 QVariant 转成 QString
    QMessageBox::information(
        NULL,                        // 用 nullptr 更好，但这里没父窗口
        "兴趣爱好",
        "你选择的类型:\n" + index.data().toString()
        );
}