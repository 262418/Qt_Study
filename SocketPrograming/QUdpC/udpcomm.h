#ifndef UDPCOMM_H
#define UDPCOMM_H

#include <QMainWindow>
#include <QUdpSocket>   // UDP 套接字
#include <QtNetwork>    // 网络模块

QT_BEGIN_NAMESPACE
namespace Ui { class udpComm; }
QT_END_NAMESPACE

class udpComm : public QMainWindow
{
    Q_OBJECT
public:
    udpComm(QWidget *parent = nullptr);
    ~udpComm();
public:
    QUdpSocket *udpsocket;         // UDP 套接字
    QString GetLocalIpAddress();   // 获取本机 IP
private slots:
    void on_pushButton_start_clicked();        // 启动服务
    void on_pushButton_stop_clicked();         // 停止服务
    void on_pushButton_sendmsg_clicked();      // 发送消息
    void on_pushButton_broadcastmsg_clicked(); // 广播消息

    void SocketReadyReadData();                // 收到数据报

private:
    Ui::udpComm *ui;
};

#endif // UDPCOMM_H