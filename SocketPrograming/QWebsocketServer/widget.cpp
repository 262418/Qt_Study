#include "widget.h"
#include "ui_widget.h"
#include <QListWidgetItem>

// ==================== 构造函数 ====================
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // ★ 创建 WebSocket 服务器
    //   - "c" 是服务器名称（任意）
    //   - NonSecureMode = ws://，SecureMode = wss://
    websocketserver = new QWebSocketServer(
        QStringLiteral("c"),
        QWebSocketServer::NonSecureMode,
        this);

    // 有新客户端连接
    connect(websocketserver, &QWebSocketServer::newConnection,
            this, &Widget::getnewconnect);

    // ★ 监听 8899 端口
    websocketserver->listen(QHostAddress::Any, 8899);
}

// ==================== 析构函数 ====================
Widget::~Widget()
{
    delete ui;

    // 关闭所有客户端连接
    for (auto socket : websocketlist)
    {
        socket->close();
    }

    // 关闭服务器
    websocketserver->close();
}

// ==================== "发送数据"按钮 ====================
void Widget::on_pushButton_SendData_clicked()
{
    QString strtext = ui->textEdit_SendData->toPlainText().trimmed();
    if (strtext.isEmpty()) return;

    if (ui->radioButton_SendAll->isChecked())   // 群发
    {
        if (websocketlist.size() == 0) return;

        for (auto socket : websocketlist)
        {
            socket->sendTextMessage(strtext);
        }
        ui->textEdit_MsgList->append("服务器给所有连接发送：" + strtext);
    }
    else   // 私发
    {
        if (!ui->listWidget_Client->currentItem()) return;

        QString strcurrent = ui->listWidget_Client->currentItem()->text();

        QWebSocket *websocket = nullptr;
        for (auto socket : websocketlist)
        {
            if (socket->origin() == strcurrent)
            {
                websocket = socket;
                break;
            }
        }

        if (websocket)
        {
            websocket->sendTextMessage(strtext);
            ui->textEdit_MsgList->append(
                "服务端给[" + websocket->origin() + "]发送--->" + strtext);
        }
    }

    ui->textEdit_SendData->clear();
}

// ==================== 处理新连接 ====================
void Widget::getnewconnect()
{
    // 有挂起连接就取出来
    if (websocketserver->hasPendingConnections())
    {
        QWebSocket *websocket = websocketserver->nextPendingConnection();

        ui->textEdit_MsgList->append(
            websocket->origin() + "客户端已连接到服务器");

        websocketlist << websocket;   // 加入客户端列表

        // 在列表控件里添加一项
        QListWidgetItem *item = new QListWidgetItem;
        item->setText(websocket->origin());
        ui->listWidget_Client->addItem(item);

        // 客户端断开时
        connect(websocket, &QWebSocket::disconnected, this,
                [websocket, this]{
                    ui->textEdit_MsgList->append(
                        websocket->origin() + "客户端已断开服务器");

                    websocketlist.removeOne(websocket);   // 从列表移除

                    // 从界面列表控件移除
                    for (int i = 0; i < ui->listWidget_Client->count(); i++)
                    {
                        QListWidgetItem *item = ui->listWidget_Client->item(i);
                        if (item->text() == websocket->origin())
                        {
                            ui->listWidget_Client->removeItemWidget(item);
                            delete item;
                            break;
                        }
                    }

                    websocket->deleteLater();   // 安全删除
                });

        // 收到消息
        connect(websocket, &QWebSocket::textMessageReceived,
                this, &Widget::receiveMsg);

        // Qt 6：errorOccurred
        connect(websocket, &QWebSocket::errorOccurred,
                this, &Widget::onerrorFunc);
    }
}

// ==================== 接收消息 ====================
void Widget::receiveMsg(const QString &msg)
{
    QJsonDocument jd = QJsonDocument::fromJson(msg.toLatin1().data());

    if (jd.isNull())
    {
        // 不是 JSON
        QWebSocket *websocket = qobject_cast<QWebSocket*>(sender());
        ui->textEdit_MsgList->append(
            "收到客户端消息[" + websocket->origin() + "]--->" + msg);
    }else{
        // 是 JSON → 转发给目标客户端
        QJsonObject jdo = jd.object();

        // 注意：客户端发的键是 "dst"，这里写的是 "dst:"，会取不到
        QString dst = jdo["dst"].toString();

        for (auto socket : websocketlist)
        {
            if (dst == socket->origin())
                socket->sendTextMessage(msg);
        }
    }
}

// ==================== 错误处理 ====================
void Widget::onerrorFunc(QAbstractSocket::SocketError error)
{
    Q_UNUSED(error);
    QWebSocket *websocket = qobject_cast<QWebSocket*>(sender());
    if (websocket)
    {
        ui->textEdit_MsgList->append(
            websocket->origin() + "出错" + websocket->errorString());
    }
}