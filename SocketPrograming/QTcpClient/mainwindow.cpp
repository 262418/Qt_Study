#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QDebug>

// ==================== 构造函数 ====================
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 1. 创建客户端套接字
    tcpclient = new QTcpSocket(this);

    // 2. 显示本机 IP 到下拉框（实际使用时应改成服务器 IP）
    QString strip = getlocalip();
    ui->comboBoxIp->addItem(strip);

    // 3. 连接信号
    connect(tcpclient, SIGNAL(connected()),
            this, SLOT(connectfunc()));
    connect(tcpclient, SIGNAL(disconnected()),
            this, SLOT(disconnectfunc()));
    connect(tcpclient, SIGNAL(readyRead()),
            this, SLOT(socketreaddata()));
    // 4. 初始按钮状态
    ui->pushButton_Disconnect->setEnabled(false);
}

// ==================== 析构函数 ====================
MainWindow::~MainWindow()
{
    delete ui;
}

// ==================== 获取本机 IPv4 地址 ====================
QString MainWindow::getlocalip()
{
    QString hostname = QHostInfo::localHostName();
    QHostInfo hostinfo = QHostInfo::fromName(hostname);
    QString localip = "";
    QList<QHostAddress> addlist = hostinfo.addresses();

    if (!addlist.isEmpty())
    {
        for (int i = 0; i < addlist.count(); i++)
        {
            QHostAddress ahost = addlist.at(i);
            if (QAbstractSocket::IPv4Protocol == ahost.protocol())
            {
                localip = ahost.toString();
                break;
            }
        }
    }
    return localip;
}

// ==================== "连接"按钮 ====================
void MainWindow::on_pushButton_Connect_clicked()
{
    QString addr = ui->comboBoxIp->currentText();
    quint16 port = ui->spinBoxPort->value();

    ui->plainTextEdit_DispMsg->appendPlainText(
        "**********正在连接服务器**********");

    tcpclient->connectToHost(addr, port);       // 发起连接（异步）
}

// ==================== "发送"按钮 ====================
void MainWindow::on_pushButton_Send_clicked()
{
    if (tcpclient->state() != QAbstractSocket::ConnectedState)
    {
        QMessageBox::warning(this, "提示", "未连接服务器，无法发送！");
        return;
    }

    QString strmsg = ui->lineEdit_InputMsg->text();
    ui->plainTextEdit_DispMsg->appendPlainText("[client]:" + strmsg);
    ui->lineEdit_InputMsg->clear();

    QByteArray str = strmsg.toUtf8();
    str.append('\n');
    tcpclient->write(str);
}

// ==================== "断开"按钮 ====================
void MainWindow::on_pushButton_Disconnect_clicked()
{
    if (tcpclient->state() == QAbstractSocket::ConnectedState)
    {
        tcpclient->disconnectFromHost();
    }
}

// ==================== 连接成功 ====================
void MainWindow::connectfunc()
{
    ui->plainTextEdit_DispMsg->appendPlainText(
        "**********已经连接到服务器端**********");
    ui->plainTextEdit_DispMsg->appendPlainText(
        "**********peer address:" + tcpclient->peerAddress().toString());
    ui->plainTextEdit_DispMsg->appendPlainText(
        "**********peer port:" + QString::number(tcpclient->peerPort()));

    ui->pushButton_Connect->setEnabled(false);
    ui->pushButton_Disconnect->setEnabled(true);
}

// ==================== 断开连接 ====================
void MainWindow::disconnectfunc()
{
    ui->plainTextEdit_DispMsg->appendPlainText(
        "**********已断开与服务器端的连接**********");
    ui->pushButton_Connect->setEnabled(true);
    ui->pushButton_Disconnect->setEnabled(false);
}

// ==================== 收到数据 ====================
void MainWindow::socketreaddata()
{
    while (tcpclient->canReadLine())
    {
        ui->plainTextEdit_DispMsg->appendPlainText(
            "[server]:" + tcpclient->readLine());
    }
}

// ==================== 窗口关闭 ====================
void MainWindow::closeEvent(QCloseEvent *event)
{
    if (tcpclient->state() == QAbstractSocket::ConnectedState)
    {
        tcpclient->disconnectFromHost();
    }
    event->accept();
}