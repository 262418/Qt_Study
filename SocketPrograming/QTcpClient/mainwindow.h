#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>     // TCP 套接字
#include <QHostAddress>   // 网络地址
#include <QHostInfo>      // 主机名/IP 查询

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
    QTcpSocket *tcpclient;    // 客户端套接字
    QString getlocalip();     // 获取本机 IP 的辅助函数
protected:
    void closeEvent(QCloseEvent *event);   // 窗口关闭事件

private slots:
    void connectfunc();                          // 连接成功
    void disconnectfunc();                       // 断开连接
    void socketreaddata();                       // 收到数据
    void on_pushButton_Connect_clicked();        // "连接"按钮
    void on_pushButton_Send_clicked();           // "发送"按钮
    void on_pushButton_Disconnect_clicked();     // "断开"按钮
};

#endif // MAINWINDOW_H