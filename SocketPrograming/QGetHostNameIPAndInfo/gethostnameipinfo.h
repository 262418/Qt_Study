#ifndef GETHOSTNAMEIPINFO_H
#define GETHOSTNAMEIPINFO_H

#include <QDialog>            // 对话框基类
#include <QHostInfo>          // 主机名和 IP 查询
#include <QNetworkInterface>  // 网络接口（网卡）信息
#include <QMessageBox>        // 消息弹窗

QT_BEGIN_NAMESPACE
namespace Ui { class GetHostNameIPInfo; }
QT_END_NAMESPACE

class GetHostNameIPInfo : public QDialog
{
    Q_OBJECT   // 使用信号与槽必须加的宏
public:
    GetHostNameIPInfo(QWidget *parent = nullptr);
    ~GetHostNameIPInfo();

    // 获取主机名称和 IP 地址（自己的辅助函数）
    void GetHostNameAndIpAddress();
private slots:
    void on_pushButton_GetHostNameIP_clicked();   // "获取主机名和IP"按钮
    void on_pushButton_GetHostInfo_clicked();     // "获取网卡信息"按钮
private:
    Ui::GetHostNameIPInfo *ui;   // .ui 界面对象
};

#endif // GETHOSTNAMEIPINFO_H