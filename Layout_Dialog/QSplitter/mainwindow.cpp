#include "mainwindow.h"
#include <QSplitter>      // 拆分器
#include <QTextEdit>      // 多行文本编辑框

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("拆分窗口测试");

    // ==================== 主拆分器（水平） ====================
    // QSplitter(方向, 父窗口)
    // 父窗口写 0 表示暂时没有父对象（后面通过布局或 setCentralWidget 归属）
    QSplitter *spMainWindow = new QSplitter(Qt::Horizontal, 0);

    // 在 spMainWindow 中放一个 QTextEdit 作为左边部分
    // QTextEdit("文字", 父对象)：父对象是 spMainWindow
    QTextEdit *txteditmain = new QTextEdit("左边主窗口", spMainWindow);

    // ==================== 右侧拆分器（垂直） ====================
    // 再建一个垂直拆分器，父对象是 spMainWindow（成为它的右半部分）
    QSplitter *spRight = new QSplitter(Qt::Vertical, spMainWindow);

    // 右侧上半部分
    QTextEdit *txteditup = new QTextEdit("右边上部分窗口", spRight);
    // 右侧下半部分
    QTextEdit *txteditdown = new QTextEdit("右边下部分窗口", spRight);

    // ==================== 右侧下半再分（垂直） ====================
    // 这个拆分器父对象是 spRight，会追加到 spRight 的底部
    QSplitter *sptest = new QSplitter(Qt::Vertical, spRight);

    // 往 sptest 里放文本框
    QTextEdit *txtedittest = new QTextEdit("ABCDEF", sptest);

    // ==================== 又一个水平拆分器 ====================
    // 父对象还是 spMainWindow，会追加到主拆分器右边
    QSplitter *sptestend = new QSplitter(Qt::Horizontal, spMainWindow);
    QTextEdit *txtedittestend = new QTextEdit("FEDCBA", sptestend);

    // 这里只是显示拆分器本身，但拆分器没有父窗口会变"孤立窗口"
    spMainWindow->show();
}

MainWindow::~MainWindow() = default;