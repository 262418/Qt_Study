#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrl>

// ==================== 构造函数 ====================
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    websocket = nullptr;   // 初始为空
}

// ==================== 析构函数 ====================
Widget::~Widget()
{
    delete ui;

    if (websocket)
        websocket->close();
}

// ==================== 接收消息 ====================
void Widget::receviedMsgFunc(const QString &msg)
{
    // 尝试把消息当成 JSON 解析
    QJsonDocument jsd = QJsonDocument::fromJson(msg.toUtf8().data());

    if (jsd.isNull())
    {
        // 不是 JSON → 当成普通文本显示
        ui->textEdit_MsgList->append("收到消息:" + msg);
    }
    else
    {
        // 是 JSON → 按字段解析
        QJsonObject jsobj = jsd.object();
        ui->textEdit_MsgList->append(
            "收到来自" + jsobj["SRC"].toString() +
            "的消息:" + jsobj["MSG"].toString());
    }
}

// ==================== 错误处理 ====================
void Widget::onerrorFunc(QAbstractSocket::SocketError error)
{
    Q_UNUSED(error);
    ui->textEdit_MsgList->append(
        websocket->origin() + "出错" + websocket->errorString());
}

// ==================== "连接/断开"按钮 ====================
void Widget::on_pushButton_Connect_clicked()
{
    if (!websocket)   // 未连接 → 创建并连接
    {
        // 检查服务器名是否为空
        if (ui->lineEdit_ServerName->text().trimmed().isEmpty())
        {
            QMessageBox::critical(this, "错误",
                                  "服务器名称不能为空，请重新检查!", QMessageBox::Yes);
            return;
        }

        // ★ 创建 WebSocket 对象
        websocket = new QWebSocket(
            ui->lineEdit_ServerName->text().trimmed(),          // 客户端标识
            QWebSocketProtocol::VersionLatest,                  // 协议版本
            this);                                              // 父对象

        // 连接成功
        connect(websocket, &QWebSocket::connected, this, [this]{
            ui->textEdit_MsgList->append(
                "已经连接上" + websocket->peerAddress().toString());
            bConnect = true;
            ui->pushButton_Connect->setText("断开服务器");
        });

        // 断开连接
        connect(websocket, &QWebSocket::disconnected, this, [this]{
            ui->textEdit_MsgList->append(
                "已" + websocket->peerAddress().toString() + "断开连接");
            bConnect = false;
            ui->pushButton_Connect->setText("连接服务器");
        });

        // ★ Qt 6：错误信号是 errorOccurred，不是 error
        connect(websocket, &QWebSocket::errorOccurred,
                this, &Widget::onerrorFunc);

        // 收到文本消息
        connect(websocket, &QWebSocket::textMessageReceived,
                this, &Widget::receviedMsgFunc);
    }

    // 根据状态决定是"打开"还是"关闭"
    if (!bConnect)
    {
        // 打开连接
        websocket->open(QUrl(ui->lineEdit_ServerAddress->text().trimmed()));
    }
    else
    {
        // 断开连接
        websocket->close();
        websocket->deleteLater();
        websocket = nullptr;
    }
}

// ==================== "发送消息"按钮 ====================
void Widget::on_pushButton_SendMsg_clicked()
{
    if (!websocket) return;
    if (!websocket->isValid()) return;

    QString strtext = ui->textEdit_SendData->toPlainText().trimmed();
    if (strtext.isEmpty()) return;

    // 获取目标客户端名（可选）
    QString strclient = ui->lineEdit_ClientName->text().trimmed();

    if (strclient.isEmpty())
    {
        // 没填目标 → 直接发原始文本
        websocket->sendTextMessage(strtext);
        ui->textEdit_MsgList->append("发送消息：" + strtext);
    }
    else
    {
        // 填了目标 → 组装 JSON 发出去
        QJsonObject jsobj;
        jsobj["src"] = websocket->origin();
        jsobj["dst"] = strclient;
        jsobj["msg"] = strtext;

        websocket->sendTextMessage(
            QString(QJsonDocument(jsobj).toJson(QJsonDocument::Compact)));

        ui->textEdit_MsgList->append(
            "给客户端" + strclient + "发送消息:" + strtext);
    }

    ui->textEdit_SendData->clear();
}