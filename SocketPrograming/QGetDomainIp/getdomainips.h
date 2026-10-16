#ifndef GETDOMAINIPS_H
#define GETDOMAINIPS_H

#include <QDialog>      // 对话框基类
#include <QHostInfo>    // 域名解析相关类
#include <QAbstractSocket>   // 网络协议枚举（IPv4/IPv6）

QT_BEGIN_NAMESPACE
namespace Ui { class GetDomainIps; }
QT_END_NAMESPACE

class GetDomainIps : public QDialog
{
    Q_OBJECT   // 使用信号与槽必须加的宏

public:
    GetDomainIps(QWidget *parent = nullptr);   // 构造函数
    ~GetDomainIps();                           // 析构函数

    // 把"网络层协议枚举"转成可读的字符串（IPv4 Protocol / IPv6 Protocol）
    QString ProtocolTypeName(QAbstractSocket::NetworkLayerProtocol pro);

private slots:
    // 关键：解析完成后的回调槽函数
    // 域名解析是异步的，解析完成后 QHostInfo 会发信号，调用这个函数
    void LookupHostInfoFunc(const QHostInfo &host);

    // 两个按钮的槽函数（Qt 自动连接）
    void on_pushButton_ClearData_clicked();     // "清空"按钮
    void on_pushButton_GetDomainIP_clicked();   // "获取IP"按钮

private:
    Ui::GetDomainIps *ui;   // .ui 界面对象
};

#endif // GETDOMAINIPS_H