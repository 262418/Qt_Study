#ifndef TCPSERVERP_H
#define TCPSERVERP_H

#include <QTcpServer>

class Dialog;   // 向前声明（不要 #include "dialog.h"，会循环包含）

// ==================== 多线程 TCP 服务器 ====================
class tcpserverp : public QTcpServer
{
    Q_OBJECT

public:
    tcpserverp(QObject *parent = nullptr);

protected:
    // Qt 6：incomingConnection 的参数是 qintptr
    void incomingConnection(qintptr socketdescriptor) override;

private:
    Dialog *dlgs;   // 指向主对话框
};

#endif // TCPSERVERP_H