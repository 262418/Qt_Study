#ifndef HANDLETHREAD_H
#define HANDLETHREAD_H

#include <QThread>
#include <QTcpSocket>    // TCP 套接字
#include <QtNetwork>     // 网络模块
#include <QByteArray>    // 字节数组
#include <QDataStream>   // 数据流

// ==================== 处理客户端请求的线程 ====================
class HandleThread : public QThread
{
    Q_OBJECT

public:
    // Qt 6：用 qintptr，不是 int
    HandleThread(qintptr socketdescriptor, QObject *parent = nullptr);

    void run() override;   // 线程体

signals:
    // 出错信号（携带错误码）
    void error(QTcpSocket::SocketError socketerror);

private:
    qintptr socketdescriptor;
};

#endif // HANDLETHREAD_H