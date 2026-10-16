#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTcpSocket>          // TCP 套接字
#include <QAbstractSocket>     // 抽象套接字（错误枚举）
#include <QDataStream>         // 数据流
#include <QMessageBox>         // 消息弹窗

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    // 输入框内容变化时，控制"请求连接"按钮的可用状态
    void on_pushButton_Request_clicked();

private:
    Ui::Dialog *ui;
    QTcpSocket *tcpsocket;     // TCP 客户端套接字

public slots:
    // 处理各种 socket 错误
    void dispError(QAbstractSocket::SocketError socketerror);

    // 发起连接
    void opeexec();
};

#endif // DIALOG_H