#include "mainwindow.h"
#include <QDesktopServices>   // 提供打开 URL、文件、邮件等系统服务
#include <QUrl>               // 统一资源定位符，表示网址/文件路径

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 设置窗口位置和大小
    this->setGeometry(400, 300, 500, 300);

    // 创建命令链接按钮
    // 构造函数签名：QCommandLinkButton(const QString &text,
    //                                   const QString &description,
    //                                   QWidget *parent = nullptr)
    //   text        = 大标题文字 "testqclb"
    //   description = 下方说明文字 "clicked testqclb"
    //   parent      = this
    qclb = new QCommandLinkButton("testqclb", "clicked testqclb", this);

    // 设置按钮位置和大小
    qclb->setGeometry(50, 100, 250, 60);

    // 连接信号槽（旧式语法）
    // 点击按钮 → 调用 qclbClicked()
    connect(qclb, SIGNAL(clicked()), this, SLOT(qclbClicked()));
}

MainWindow::~MainWindow() = default;

// 槽函数：按钮被点击时执行
void MainWindow::qclbClicked()
{
    // QDesktopServices::openUrl() 用系统默认程序打开 URL
    // 对 http/https 网址来说，就是打开默认浏览器
    QDesktopServices::openUrl(QUrl("https://www.bilibili.com/index.html/"));
}