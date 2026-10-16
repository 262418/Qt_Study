#include "handlethread.h"

// ==================== 构造函数 ====================
HandleThread::HandleThread(qintptr socketdescriptor, QObject *parent)
    : QThread(parent)                    // 调用父类构造函数
    , socketdescriptor(socketdescriptor) // 保存 socket 描述符
{
}

// ==================== 线程体 ====================
void HandleThread::run()
{
    QTcpSocket tcpsocket;   // 在当前线程里创建 socket

    // 把描述符绑定到 socket
    if (!tcpsocket.setSocketDescriptor(socketdescriptor))
    {
        emit error(tcpsocket.error());
        return;
    }

    QByteArray blocks;
    QDataStream out(&blocks, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);   // Qt 6 版本号

    tcpsocket.write(blocks);
    tcpsocket.disconnectFromHost();
}