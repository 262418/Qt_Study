#include "udpcomm.h"
#include "ui_udpcomm.h"

#include <QMessageBox>
#include <QHostInfo>
#include <QHostAddress>

// ==================== 构造函数 ====================
udpComm::udpComm(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::udpComm)
{
    ui->setupUi(this);

    QString strip = GetLocalIpAddress();
    ui->comboBoxtargetip->addItem(strip);

    udpsocket = new QUdpSocket(this);

    connect(udpsocket, SIGNAL(readyRead()),
            this, SLOT(SocketReadyReadData()));

    ui->pushButton_stop->setEnabled(false);
}

// ==================== 析构函数 ====================
udpComm::~udpComm()
{
    delete ui;
}

// ==================== 获取本机 IPv4 地址 ====================
QString udpComm::GetLocalIpAddress()
{
    QString strHostName = QHostInfo::localHostName();
    QHostInfo hostinfo = QHostInfo::fromName(strHostName);

    QString strLocalIp = "";
    QList<QHostAddress> addresslist = hostinfo.addresses();

    if (!addresslist.isEmpty())
    {
        for (int i = 0; i < addresslist.count(); i++)
        {
            QHostAddress hostaddr = addresslist.at(i);
            if (QAbstractSocket::IPv4Protocol == hostaddr.protocol())
            {
                strLocalIp = hostaddr.toString();
                break;
            }
        }
    }
    return strLocalIp;
}

// ==================== "启动服务"按钮 ====================
void udpComm::on_pushButton_start_clicked()
{
    quint16 port = ui->spinBoxbindport->value();

    if (udpsocket->bind(port))
    {
        ui->plainTextEditdispmsg->appendPlainText("**********绑定成功**********");
        ui->plainTextEditdispmsg->appendPlainText(
            "$$$$$$$$$$绑定端口$$$$$$$$$$：" +
            QString::number(udpsocket->localPort()));

        ui->pushButton_start->setEnabled(false);
        ui->pushButton_stop->setEnabled(true);
    }else{
        ui->plainTextEditdispmsg->appendPlainText("**********绑定失败**********");
    }
}

// ==================== "停止服务"按钮 ====================
void udpComm::on_pushButton_stop_clicked()
{
    udpsocket->abort();     // 强制关闭套接字，解绑端口
    ui->pushButton_start->setEnabled(true);
    ui->pushButton_stop->setEnabled(false);
    ui->plainTextEditdispmsg->appendPlainText("**********已经停止服务**********");
}

// ==================== "发送消息"按钮（单播） ====================
void udpComm::on_pushButton_sendmsg_clicked()
{
    QString targetIpAddress = ui->comboBoxtargetip->currentText();
    QHostAddress targetaddress(targetIpAddress);

    quint16 targetport = ui->spinBoxtargetport->value();

    QString strmsg = ui->lineEditmsg->text();
    QByteArray str = strmsg.toUtf8();

    udpsocket->writeDatagram(str, targetaddress, targetport);

    ui->plainTextEditdispmsg->appendPlainText("[out]：" + str);
    ui->lineEditmsg->clear();
    ui->lineEditmsg->setFocus();
}

// ==================== "广播消息"按钮 ====================
void udpComm::on_pushButton_broadcastmsg_clicked()
{
    quint16 targetport = ui->spinBoxtargetport->value();
    QString strmsg = ui->lineEditmsg->text();
    QByteArray str = strmsg.toUtf8();

    udpsocket->writeDatagram(str, QHostAddress::Broadcast, targetport);

    ui->plainTextEditdispmsg->appendPlainText("[broadcast]：" + str);
    ui->lineEditmsg->clear();
    ui->lineEditmsg->setFocus();
}

// ==================== 接收数据报 ====================
void udpComm::SocketReadyReadData()
{
    // hasPendingDatagrams()：判断是否有待读取的数据报
    while (udpsocket->hasPendingDatagrams())
    {
        QByteArray datagrams;
        // 根据待读数据报的大小，调整缓冲区大小
        datagrams.resize(udpsocket->pendingDatagramSize());

        QHostAddress paddress;
        quint16 pport;

        udpsocket->readDatagram(datagrams.data(),
                                datagrams.size(),
                                &paddress, &pport);

        QString strs = datagrams.data();
        QString peer = "[From:" + paddress.toString() + ":"
                       + QString::number(pport) + "]：";

        ui->plainTextEditdispmsg->appendPlainText(peer + strs);
    }
}