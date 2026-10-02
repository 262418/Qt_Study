#include "mainwindow.h"
#include <QTextEdit>      // 多行文本编辑框
#include <QDockWidget>    // 停靠窗口

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 把界面创建逻辑封装到 DockWidgetFunc 里
    DockWidgetFunc();
}

MainWindow::~MainWindow() = default;

// ==================== 创建停靠窗口 ====================
void MainWindow::DockWidgetFunc()
{
    setWindowTitle("QDockWidget类停靠窗口测试");

    // ---------- 中央控件 ----------
    // 主窗口必须有 centralWidget，否则中间是空的
    QTextEdit *tedit = new QTextEdit(this);
    tedit->setText("QWERTYUIOP");
    tedit->setAlignment(Qt::AlignCenter);
    setCentralWidget(tedit);   // 设为中央控件

    // ==================== 停靠窗口(一) ====================
    QDockWidget *dw1 = new QDockWidget("停靠窗口(一)", this);

    // 设置停靠窗口的特性（能做什么）
    // 这里只设置了 Movable，表示：
    //   - 可以移动（拖动标题栏重排）
    //   - 不能关闭（没有 × 按钮）
    //   - 不能浮动成独立窗口
    dw1->setFeatures(QDockWidget::DockWidgetMovable);

    // 设置允许停靠的区域
    // 只允许在左侧和右侧停靠，不能停靠到上下
    dw1->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    // 创建停靠窗口内部的内容控件
    QTextEdit *qtedit1 = new QTextEdit();
    qtedit1->setText("ASDFGHJKL");
    dw1->setWidget(qtedit1);   // 把 qtedit1 设为 dw1 的内容

    // 把停靠窗口加到主窗口右侧
    addDockWidget(Qt::RightDockWidgetArea, dw1);

    // ==================== 停靠窗口(二) ====================
    QDockWidget *dw2 = new QDockWidget("停靠窗口(二)", this);

    // 设置特性：Closable + Floatable
    //   - Closable：可以关闭（有 × 按钮）
    //   - Floatable：可以浮动成独立窗口
    //   - 没有 Movable：不能拖动
    dw2->setFeatures(QDockWidget::DockWidgetClosable
                     | QDockWidget::DockWidgetFloatable);

    // 没有 setAllowedAreas，默认允许所有区域

    QTextEdit *qtedit2 = new QTextEdit();
    qtedit2->setText("ZXCVBNM");
    dw2->setWidget(qtedit2);

    // 也加到右侧（会和 dw1 堆叠，用页签切换）
    addDockWidget(Qt::RightDockWidgetArea, dw2);
}