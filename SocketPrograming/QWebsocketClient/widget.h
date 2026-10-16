#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QAbstractSocket>   // 套接字基类（错误枚举）
#include <QWebSocket>        // WebSocket 客户端
#include <QJsonDocument>     // JSON 文档
#include <QJsonObject>       // JSON 对象

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

    class QWebSocket *websocket;   // WebSocket 客户端对象
    bool bConnect = false;         // 连接状态标志

    // 接收消息的处理函数
    void receviedMsgFunc(const QString &msg);

private slots:
    void onerrorFunc(QAbstractSocket::SocketError error);   // 错误处理
    void on_pushButton_Connect_clicked();                   // 连接/断开按钮
    void on_pushButton_SendMsg_clicked();                   // 发送按钮
};

#endif // WIDGET_H