#include "myhttpserver.h"
#include <QtDebug>

// ==================== 构造函数 ====================
myhttpserver::myhttpserver(QObject *parent) : QObject(parent)
{
    ser = new QTcpServer(this);   // 创建 TCP 服务器

    // 信号与槽：有新连接时调用 connection()
    connect(ser, &QTcpServer::newConnection,
            this, &myhttpserver::connection);

    // 开始监听 8088 端口（所有网卡）
    if (!ser->listen(QHostAddress::Any, 8088))
    {
        qDebug() << "\n致命错误：Web服务器没有启动，请重新检查!";
    }else{
        qDebug() << "\n正常启动：Web服务器端口:8088，等待客户端连接......";
    }
}

// ==================== 析构函数 ====================
myhttpserver::~myhttpserver()
{
    socket->close();   // 关闭套接字
}

// ==================== 处理客户端连接 ====================
void myhttpserver::connection()
{
    // 1. 取出待处理的客户端连接
    socket = ser->nextPendingConnection();

    // 2. 等待浏览器发来 HTTP 请求
    //    waitForReadyRead(100)：最多等 100 毫秒
    //    外层 while 循环是为了确保真的读到数据
    while (!(socket->waitForReadyRead(100)));

    // 3. 读取浏览器发来的 HTTP 请求头
    char webdata[1000];
    int sv = socket->read(webdata, 1000);
    qDebug() << "正常运行：从浏览器读取数据信息......" << QString(webdata);

    // 4. 按 HTTP 协议写响应头
    socket->write("HTTP/1.1 200 OK\r\n");              // 状态行：200 OK
    socket->write("Content-Type: text/html\r\n");      // 内容类型：HTML
    socket->write("Connection: close\r\n");            // 关闭连接
    socket->write("Refresh: 3\r\n\r\n");               // 每 3 秒刷新页面

    // 5. 写 HTML 响应体
    socket->write("<!DOCTYPE>"
                  "<html>"
                  "<header>"
                  "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"/>"
                  "<title>HttpServer</title>"
                  "</header>"
                  "<body>客户端已经连接HttpSever服务器秒数为：");

    // 6. 显示访问次数（静态变量，每次 +1）
    QByteArray bytesary;
    static qint16 icount;   // 静态变量：跨函数调用保留值
    bytesary.setNum(icount++);
    socket->write(bytesary);

    socket->write("</html>");

    // 7. 发送数据
    socket->flush();

    // 8. 断开连接，连接断开后自动删除 socket
    connect(socket, &QTcpSocket::disconnected,
            socket, &QTcpSocket::deleteLater);
    socket->disconnectFromHost();
}