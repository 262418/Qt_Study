#include "widget.h"
#include "ui_widget.h"
#include <QListWidget>          // 列表控件

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);          // 加载 .ui 文件，创建界面控件

    // ==================== 添加第一条（带居中对齐） ====================
    // 1. 创建一个列表项，设置文字
    QListWidgetItem *qlwi = new QListWidgetItem("沁园春·雪");

    // 2. 把项添加到 Designer 中创建的 listWidget 里
    ui->listWidget->addItem(qlwi);

    // 3. 设置这一项的文字对齐方式：水平居中 + 垂直居中
    qlwi->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);

    // ==================== 批量添加多条 ====================
    QStringList slist;
    slist << "北国风光，千里冰封，万里雪飘"
          << "望长城内外，惟余莽莽；大河上下，顿失滔滔。";

    // addItems 一次性把 QStringList 里所有字符串加入列表
    ui->listWidget->addItems(slist);
}

Widget::~Widget()
{
    delete ui;   // 释放 UI 对象
}