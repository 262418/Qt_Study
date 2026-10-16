#ifndef MYHTTPSERVER_H
#define MYHTTPSERVER_H

#include <QObject>
#include <QTcpServer>   // TCP 服务器
#include <QTcpSocket>   // TCP 套接字

// ==================== 简易 HTTP 服务器 ====================
class myhttpserver : public QObject
{
    Q_OBJECT

public:
    explicit myhttpserver(QObject *parent = nullptr);
    ~myhttpserver();

public:
    QTcpSocket *socket;   // 与客户端通信的套接字

private:
    QTcpServer *ser;      // 监听服务器

public slots:
    void connection();    // 有新客户端连接时调用
};

#endif // MYHTTPSERVER_H