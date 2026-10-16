#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QAbstractSocket>
#include <QWebSocketServer>   // WebSocket 服务器
#include <QWebSocket>         // WebSocket 连接
#include <QJsonDocument>
#include <QJsonObject>

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

    class QWebSocketServer *websocketserver;   // WebSocket 服务器对象
    QList<QWebSocket*> websocketlist;          // 所有已连接的客户端

    void getnewconnect();                        // 处理新连接
    void receiveMsg(const QString &msg);         // 接收消息

public slots:
    void onerrorFunc(QAbstractSocket::SocketError error);

private slots:
    void on_pushButton_SendData_clicked();       // 发送数据按钮
};

#endif // WIDGET_H