#include "dialog.h"
#include <QHBoxLayout>   // 水平布局：把列表和堆叠页左右摆放

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    // ==================== 窗口标题 ====================
    setWindowTitle("堆栈窗体测试");

    // ==================== 左侧：列表 ====================
    qlist = new QListWidget(this);     // 父对象是 Dialog，自动管理内存

    // 逐个插入 5 个列表项
    // insertItem(行号, 文本)：把文本插入到指定行
    qlist->insertItem(0, "Linux1");    // 第 0 行
    qlist->insertItem(1, "Linux2");    // 第 1 行
    qlist->insertItem(2, "Linux3");    // 第 2 行
    qlist->insertItem(3, "Linux4");    // 第 3 行
    qlist->insertItem(4, "Linux5");    // 第 4 行
    // 也可以用 addItem("Linux1") 逐条追加，效果一样

    // ==================== 右侧：5 个标签 ====================
    lab1 = new QLabel("Linux1 Qt");
    lab2 = new QLabel("Linux2 Qt");
    lab3 = new QLabel("Linux3 Qt");
    lab4 = new QLabel("Linux4 Qt");
    lab5 = new QLabel("Linux5 Qt");

    // 让标签文字在堆叠页中居中显示
    lab1->setAlignment(Qt::AlignCenter);
    lab2->setAlignment(Qt::AlignCenter);
    lab3->setAlignment(Qt::AlignCenter);
    lab4->setAlignment(Qt::AlignCenter);
    lab5->setAlignment(Qt::AlignCenter);

    // ==================== 堆叠页容器 ====================
    stacks = new QStackedWidget(this);   // 父对象是 Dialog

    // addWidget 按顺序添加，每个 widget 获得一个索引（从 0 开始）
    stacks->addWidget(lab1);   // 索引 0 → 对应列表第 0 行
    stacks->addWidget(lab2);   // 索引 1 → 对应列表第 1 行
    stacks->addWidget(lab3);   // 索引 2
    stacks->addWidget(lab4);   // 索引 3
    stacks->addWidget(lab5);   // 索引 4
    // 同一时刻只显示其中一个，默认显示索引 0（即 lab1）

    // ==================== 主布局 ====================
    // QHBoxLayout：水平排列子控件
    // 传入 this 表示直接成为 Dialog 的顶层布局
    QHBoxLayout *mlayout = new QHBoxLayout(this);
    mlayout->setSpacing(20);   // 控件之间的间距 20 像素

    // 左侧：列表
    mlayout->addWidget(qlist);

    // 右侧：堆叠页
    // addWidget(控件, 拉伸比例, 对齐方式)
    //   - 拉伸比例：这里写 0，具体比例靠下面的 setStretchFactor 决定
    //   - Qt::AlignCenter：让 stacks 在分配到的区域内居中，而不是拉伸填满
    mlayout->addWidget(stacks, 0, Qt::AlignCenter);

    // setStretchFactor(控件, 比例)
    // 布局中所有控件按比例分配剩余空间
    // qlist : stacks = 1 : 2，即右侧宽度是左侧的两倍
    mlayout->setStretchFactor(qlist, 1);
    mlayout->setStretchFactor(stacks, 2);

    // ==================== 关键：信号槽连接 ====================
    // 列表的 currentRowChanged(int) 信号  →  堆叠页的 setCurrentIndex(int) 槽
    // 作用：点击列表的某一行，右侧自动切换到对应的堆叠页
    //
    // 为什么能直接连？
    //   列表行号（0~4）和堆叠页索引（0~4）恰好一一对应：
    //     列表第 0 行 → 堆叠页索引 0 → lab1
    //     列表第 1 行 → 堆叠页索引 1 → lab2
    //     ...
    //   所以不需要中间函数，直接连接即可
    connect(qlist, &QListWidget::currentRowChanged,
            stacks, &QStackedWidget::setCurrentIndex);

    // ==================== 默认选中第 0 行 ====================
    // 必须放在 connect 之后！
    // 原因：setCurrentRow(0) 会发出 currentRowChanged(0) 信号
    //       如果还没连接，信号会被丢弃
    //       连接后调用，信号才能触发槽，右侧显示同步
    qlist->setCurrentRow(0);
}

Dialog::~Dialog() = default;   // 所有子控件都有父对象，自动释放