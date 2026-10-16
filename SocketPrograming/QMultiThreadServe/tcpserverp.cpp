#include "tcpserverp.h"
#include "handlethread.h"
#include "dialog.h"

// ==================== 构造函数 ====================
tcpserverp::tcpserverp(QObject *parent)
    : QTcpServer(parent)
{
    dlgs = qobject_cast<Dialog*>(parent);   // ★ 用 qobject_cast 更安全
}

// ==================== 新客户端连接时自动调用 ====================
void tcpserverp::incomingConnection(qintptr socketdescriptor)
{
    // Qt 6：socketdescriptor 是 qintptr，直接传给 HandleThread
    HandleThread *thread = new HandleThread(socketdescriptor, this);   // parent = this

    // 线程结束 → 通知对话框更新计数
    connect(thread, SIGNAL(finished()), dlgs, SLOT(slotsdispFunc()));

    // 线程结束 → 自动删除自己
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    thread->start();   // 启动线程
}