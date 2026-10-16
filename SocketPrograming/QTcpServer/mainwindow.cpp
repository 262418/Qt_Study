#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QHostInfo>
#include <QHostAddress>
// ==================== 构造函数 ====================
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 1. 获取本机 IP 并显示到下拉框
    QString strip = GetLocalIpAddress();
    ui->comboBoxIp->addItem(strip);
    // 2. 初始化套接字指针为空
    tcpsocket = nullptr;
    // 3. 创建 TCP 服务器对象
    tcpserver = new QTcpServer(this);
    // 4. 连接"有新连接"信号
    connect(tcpserver, SIGNAL(newConnection()),
            this, SLOT(newconnection()));
    // 5. 初始按钮状态
    ui->pushButton_Stop->setEnabled(false);
}

// ==================== 析构函数 ====================
MainWindow::~MainWindow()
{
    delete ui;
}

// ==================== 获取本机 IPv4 地址 ====================
QString MainWindow::GetLocalIpAddress()
{
    QString hostname = QHostInfo::localHostName();          // 拿主机名
    QHostInfo hostinfo = QHostInfo::fromName(hostname);     // 查 IP
    QString localip = "";
    QList<QHostAddress> addresslist = hostinfo.addresses();
    if (!addresslist.isEmpty())
    {
        for (int i = 0; i < addresslist.count(); i++)
        {
            QHostAddress addrhost = addresslist.at(i);
            if (QAbstractSocket::IPv4Protocol == addrhost.protocol())
            {
                localip = addrhost.toString();
                break;
            }
        }
    }
    return localip;
}

// ==================== "开始监听"按钮 ====================
void MainWindow::on_pushButton_Start_clicked()
{
    QString ip = ui->comboBoxIp->currentText();
    quint16 port = ui->spinBoxPort->value();
    QHostAddress address(ip);
    if (!tcpserver->listen(address, port))
    {
        QMessageBox::critical(this, "错误", "监听失败：" + tcpserver->errorString());
        return;
    }
    ui->plainTextEdit_DispMsg->appendPlainText("$$$$$$$$$$开始监听$$$$$$$$$$");
    ui->plainTextEdit_DispMsg->appendPlainText(
        "$$$$$$$$$$服务器地址$$$$$$$$$$：" +
        tcpserver->serverAddress().toString());
    ui->plainTextEdit_DispMsg->appendPlainText(
        "$$$$$$$$$$服务器端口$$$$$$$$$$：" +
        QString::number(tcpserver->serverPort()));
    ui->pushButton_Start->setEnabled(false);
    ui->pushButton_Stop->setEnabled(true);
}

// ==================== "停止监听"按钮 ====================
void MainWindow::on_pushButton_Stop_clicked()
{
    if (tcpserver->isListening())
    {
        tcpserver->close();
        ui->plainTextEdit_DispMsg->appendPlainText("$$$$$$$$$$停止监听$$$$$$$$$$");
        ui->pushButton_Start->setEnabled(true);
        ui->pushButton_Stop->setEnabled(false);
    }
}

// ==================== "发送"按钮 ====================
void MainWindow::on_pushButton_Send_clicked()
{
    // 判空：没有客户端连接时不能发
    if (tcpsocket == nullptr || tcpsocket->state() != QAbstractSocket::ConnectedState)
    {
        QMessageBox::warning(this, "提示", "没有客户端连接，无法发送！");
        return;
    }

    QString strmsg = ui->lineEdit_InputMsg->text();
    ui->plainTextEdit_DispMsg->appendPlainText("[server]:" + strmsg);
    ui->lineEdit_InputMsg->clear();

    QByteArray str = strmsg.toUtf8();
    str.append("\n");
    tcpsocket->write(str);
}

// ==================== 客户端连接成功 ====================
void MainWindow::clientconnect()
{
    ui->plainTextEdit_DispMsg->appendPlainText(
        "**********客户端socket连接**********");
    ui->plainTextEdit_DispMsg->appendPlainText(
        "**********peer address:" + tcpsocket->peerAddress().toString());
    ui->plainTextEdit_DispMsg->appendPlainText(
        "**********peer port:" + QString::number(tcpsocket->peerPort()));
}

// ==================== 客户端断开 ====================
void MainWindow::clientdisconnect()
{
    ui->plainTextEdit_DispMsg->appendPlainText(
        "**********客户端socket断开连接**********");

    if (tcpsocket != nullptr)
    {
        tcpsocket->deleteLater();       //延迟删除。因为当前可能还在信号处理中，立即 delete 会崩，deleteLater 让 Qt 在安全时机删除。
        tcpsocket = nullptr;
    }
}

// ==================== 收到数据 ====================
void MainWindow::socketreaddata()
{
    while (tcpsocket->canReadLine())    //是否有完整一行可读（以 \n 结尾）
    {
        ui->plainTextEdit_DispMsg->appendPlainText(
            "[client]" + tcpsocket->readLine());
    }
}

// ==================== 有新客户端接入 ====================
void MainWindow::newconnection()
{
    // 取出待处理的连接（返回一个 QTcpSocket）
    tcpsocket = tcpserver->nextPendingConnection();

    // 立刻显示连接信息
    clientconnect();

    // 连接各种信号
    connect(tcpsocket, SIGNAL(disconnected()),
            this, SLOT(clientdisconnect()));
    connect(tcpsocket, SIGNAL(readyRead()),
            this, SLOT(socketreaddata()));
}

// ==================== 窗口关闭事件 ====================
void MainWindow::closeEvent(QCloseEvent *event)
{
    if (tcpserver->isListening())
        tcpserver->close();

    event->accept();
}