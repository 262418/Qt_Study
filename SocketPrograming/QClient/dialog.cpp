#include "dialog.h"
#include "ui_dialog.h"

// ==================== 构造函数 ====================
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    // 1. 连接按钮信号
    connect(ui->pushButton_Request, SIGNAL(clicked()), this, SLOT(opeexec()));
    connect(ui->pushButton_Exit, SIGNAL(clicked()), this, SLOT(close()));

    // 2. 创建 TCP 客户端套接字
    tcpsocket = new QTcpSocket(this);

    // ★ Qt 6：错误信号是 errorOccurred，不是 error
    connect(tcpsocket, SIGNAL(errorOccurred(QAbstractSocket::SocketError)),
            this, SLOT(dispError(QAbstractSocket::SocketError)));

    // 3. 光标定位到端口输入框
    ui->lineEdit_ServerPort->setFocus();
}

// ==================== 析构函数 ====================
Dialog::~Dialog()
{
    delete ui;
}

// ==================== 输入框内容变化时控制按钮可用状态 ====================
void Dialog::on_pushButton_Request_clicked()
{
    // 只有当服务器名和端口都不为空时，按钮才可用
    ui->pushButton_Request->setEnabled(
        !ui->lineEdit_ServerName->text().isEmpty() &&
        !ui->lineEdit_ServerPort->text().isEmpty());
}

// ==================== 处理 socket 错误 ====================
void Dialog::dispError(QAbstractSocket::SocketError socketerror)
{
    switch (socketerror)
    {
    case QAbstractSocket::RemoteHostClosedError:   // 远程主机关闭连接
        QMessageBox::information(this, "提示", "远程主机关闭连接", QMessageBox::Yes);
        break;

    case QAbstractSocket::HostNotFoundError:       // 找不到主机地址
        QMessageBox::information(this, "提示", "找不到主机地址", QMessageBox::Yes);
        break;

    case QAbstractSocket::ConnectionRefusedError:  // 连接被拒绝（或超时）
        QMessageBox::information(this, "提示", "连接被对方拒绝（或者超时）", QMessageBox::Yes);
        break;

    default:
        QMessageBox::information(this, "提示",
                                 tr("致命错误为：") + tcpsocket->errorString(), QMessageBox::Yes);
        break;
    }

    ui->pushButton_Request->setEnabled(true);   // 恢复按钮
}

// ==================== 发起连接 ====================
void Dialog::opeexec()
{
    ui->lineEdit_ServerName->setEnabled(false);   // 禁用输入框

    tcpsocket->abort();   // 取消已有连接（防止重复连接）

    // 发起连接（异步）
    tcpsocket->connectToHost(
        ui->lineEdit_ServerName->text(),                 // 服务器 IP/域名
        ui->lineEdit_ServerPort->text().toInt());        // 端口
}