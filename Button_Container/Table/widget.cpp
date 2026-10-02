#include "widget.h"
#include <QGridLayout>    // 网格布局
#include <QPushButton>    // 按钮
#include <QLabel>         // 标签
#include <QLineEdit>      // 输入框
#include <QMessageBox>    // 消息框

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    // 设置窗口标题和位置大小
    this->setWindowTitle("标签小部件控件测试");
    this->setGeometry(300, 200, 600, 400);

    // 创建标签页控件，父对象是 this
    tabWidgetUI = new QTabWidget(this);
    tabWidgetUI->setGeometry(20, 20, 560, 360);   // 硬编码坐标
    tabWidgetUI->show();                          // 一般不用手动调 show（父窗口显示时子控件自动显示）

    // ---------- 用布尔变量控制是否创建某个标签页 ----------
    bool showtabwidgetui1 = true;   // 是否创建"进程"页
    bool showtabwidgetui2 = true;   // 是否创建"性能"页
    // bool showtabwidgetui3 = false;
    // bool showtabwidgetui4 = false;

    // ---------- 标签页1："进程" ----------
    if (showtabwidgetui1)
    {
        QWidget *qw1 = new QWidget();   // 创建页签内容容器
        tabWidgetUI->addTab(qw1, "进程");   // 添加到标签页控件，标题"进程"

        QGridLayout *qgl = new QGridLayout();   // 页内网格布局
        QLabel *ql1 = new QLabel("请选择文件及文件夹");
        QLineEdit *qle1 = new QLineEdit();
        QPushButton *qpb1 = new QPushButton("消息框...");

        // 连接按钮点击信号到槽（旧式语法）
        connect(qpb1, SIGNAL(clicked(bool)), this, SLOT(MsgCommit()));

        // 布局：一行三列
        qgl->addWidget(ql1,  0, 0);   // 第0行第0列：标签
        qgl->addWidget(qle1, 0, 1);   // 第0行第1列：输入框
        qgl->addWidget(qpb1, 0, 2);   // 第0行第2列：按钮

        qw1->setLayout(qgl);   // 布局设置给页签容器
    }

    // ---------- 标签页2："性能" ----------
    if (showtabwidgetui2)
    {
        QWidget *qw2 = new QWidget();
        tabWidgetUI->addTab(qw2, "性能");   // 空白页
    }

    // if(showtabwidgetui3){ ... "应用历史记录" ... }
    // if(showtabwidgetui4){ ... "启动" ... }
}

Widget::~Widget() = default;

// 槽函数：弹消息框
void Widget::MsgCommit()
{
    QMessageBox::information(
        NULL,                       // 父窗口（NULL 表示没有父窗口）
        "testing",                  // 标题
        "QMessageBox:命令按钮测试成功！",  // 内容
        QMessageBox::Ok             // 按钮
        );
}