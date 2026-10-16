#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>   // TCP 服务器类
#include <QtNetwork>    // 网络模块（包含 QTcpSocket、QHostInfo 等）

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
private:
    QTcpServer *tcpserver;    // TCP 服务器，负责监听
    QTcpSocket *tcpsocket;    // 与客户端通信的套接字
    QString GetLocalIpAddress();   // 获取本机 IP 的辅助函数
private slots:
    void clientconnect();              // 客户端连接成功时
    void clientdisconnect();           // 客户端断开时
    void socketreaddata();             // 收到数据时
    void newconnection();              // 有新客户端接入时
    void on_pushButton_Start_clicked();  // "开始监听"按钮
    void on_pushButton_Stop_clicked();   // "停止监听"按钮
    void on_pushButton_Send_clicked();   // "发送"按钮
protected:
    void closeEvent(QCloseEvent *event);   // 窗口关闭事件（重写）
};

#endif // MAINWINDOW_H