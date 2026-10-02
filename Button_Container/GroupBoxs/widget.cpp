#include "widget.h"
#include <QGroupBox>       // 分组框
#include <QRadioButton>    // 单选按钮
#include <QPushButton>     // 普通按钮
#include <QCheckBox>       // 复选框
#include <QVBoxLayout>     // 垂直布局
#include <QGridLayout>     // 网格布局
#include <QMenu>           // 菜单

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    // ==================== 组1：纯单选按钮组 ====================
    QGroupBox *qgb1 = new QGroupBox("单选按钮组1");

    QRadioButton *qrb1 = new QRadioButton("RadioButton1");
    QRadioButton *qrb2 = new QRadioButton("RadioButton2");
    QRadioButton *qrb3 = new QRadioButton("RadioButton3");

    QVBoxLayout *qvbl1 = new QVBoxLayout;    // 垂直布局
    qvbl1->addWidget(qrb1);                  // 从上到下依次添加
    qvbl1->addWidget(qrb2);
    qvbl1->addWidget(qrb3);

    qgb1->setLayout(qvbl1);
    // 这一步很关键：
    //   1. 把 qvbl1 设为 qgb1 的顶层布局
    //   2. 布局里的控件（qrb1/2/3）自动认 qgb1 为父对象
    //   3. 它们因此成为 qgb1 下的"同一组"，自动互斥

    // ==================== 组2：纯复选按钮组 ====================
    QGroupBox *qgb2 = new QGroupBox("复选按钮组2");
    QCheckBox *qcb1 = new QCheckBox("checkbox1");
    QCheckBox *qcb2 = new QCheckBox("checkbox2");
    QCheckBox *qcb3 = new QCheckBox("checkbox3");

    // qcb2->setTristate(true);   // 这行被注释掉了，启用三态
    qcb2->setChecked(true);       // checkbox2 默认勾选

    QVBoxLayout *qvbl2 = new QVBoxLayout;
    qvbl2->addWidget(qcb1);
    qvbl2->addWidget(qcb2);
    qvbl2->addWidget(qcb3);
    qgb2->setLayout(qvbl2);

    // ==================== 组3：单选 + 复选混合 ====================
    QGroupBox *qgb3 = new QGroupBox("单选按钮和复选按钮组3");
    QRadioButton *qrb4 = new QRadioButton("RadioButton4");
    QRadioButton *qrb5 = new QRadioButton("RadioButton5");
    QRadioButton *qrb6 = new QRadioButton("RadioButton6");
    QCheckBox *qcb4 = new QCheckBox("checkbox4");

    qgb3->setCheckable(true);     // 让 GroupBox 自己带一个勾选框
    // 勾选 GroupBox 时，里面的子控件才"可用"；取消勾选时子控件变灰
    qcb4->setChecked(true);       // checkbox4 默认勾选

    QVBoxLayout *qvbl3 = new QVBoxLayout;
    qvbl3->addWidget(qrb4);
    qvbl3->addWidget(qrb5);
    qvbl3->addWidget(qrb6);
    qvbl3->addWidget(qcb4);       // 复选按钮也加入同一布局
    qgb3->setLayout(qvbl3);

    // 注意：qrb4/qrb5/qrb6 属于同一组（父对象都是 qgb3），互斥
    //       qcb4 是复选框，独立于它们，可以单独勾选

    // ==================== 组4：按钮 + 菜单 ====================
    QGroupBox *qgb4 = new QGroupBox("单选按钮和下拉按钮组4");

    qgb4->setCheckable(true);     // GroupBox 自带勾选框
    qgb4->setChecked(true);       // 默认勾选

    QPushButton *qpb7 = new QPushButton("PushButton7");
    QPushButton *qpb8 = new QPushButton("PushButton8");
    QPushButton *qpb9 = new QPushButton("PushButton9");

    QMenu *mu = new QMenu(this);  // 创建弹出菜单
    mu->addAction("A");           // 添加菜单项
    mu->addAction("B");
    mu->addAction("C");
    mu->addAction("D");

    qpb9->setMenu(mu);
    // 给 qpb9 关联菜单：点击 qpb9 会弹出菜单（具体行为取决于平台）

    QVBoxLayout *qvbl4 = new QVBoxLayout;
    qvbl4->addWidget(qpb7);
    qvbl4->addWidget(qpb8);
    qvbl4->addWidget(qpb9);
    qgb4->setLayout(qvbl4);

    // ==================== 主布局：网格摆放 4 个 GroupBox ====================
    QGridLayout *qgl = new QGridLayout;

    // addWidget(widget, row, column, rowSpan, columnSpan)
    //                  ↑行  ↑列    ↑跨行数  ↑跨列数
    qgl->addWidget(qgb1, 0, 0, 1, 1);   // 第0行第0列
    qgl->addWidget(qgb2, 0, 2, 1, 1);   // 第0行第2列
    qgl->addWidget(qgb3, 1, 0, 1, 1);   // 第1行第0列
    qgl->addWidget(qgb4, 1, 2, 1, 1);   // 第1行第2列

    this->setLayout(qgl);   // 设为主布局，4 个 GroupBox 自动认 this 为父对象
}

Widget::~Widget() = default;