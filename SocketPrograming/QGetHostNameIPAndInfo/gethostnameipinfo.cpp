#include "gethostnameipinfo.h"
#include "ui_gethostnameipinfo.h"

// ==================== 构造函数 ====================
GetHostNameIPInfo::GetHostNameIPInfo(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GetHostNameIPInfo)
{
    ui->setupUi(this);
}

// ==================== 析构函数 ====================
GetHostNameIPInfo::~GetHostNameIPInfo()
{
    delete ui;
}

// ==================== 获取主机名和 IP ====================
void GetHostNameIPInfo::GetHostNameAndIpAddress()
{
    // 1. 获取本机主机名
    QString StrLocalHostName = QHostInfo::localHostName();
    ui->lineEdit_hostname->setText(StrLocalHostName);
    // 2. 根据主机名获取 IP
    QString StrLocalIpAddress = "";
    QHostInfo hostinfo = QHostInfo::fromName(StrLocalHostName);   // 同步查询
    QList<QHostAddress> ipaddresslist = hostinfo.addresses();
    // 3. 挑出 IPv4 地址
    if (!ipaddresslist.isEmpty())
    {
        for (int i = 0; i < ipaddresslist.size(); i++)
        {
            QHostAddress addresshost = ipaddresslist.at(i);
            if (QAbstractSocket::IPv4Protocol == addresshost.protocol())
            {
                StrLocalIpAddress = addresshost.toString();
                break;
            }
        }
    }
    // 4. 显示
    ui->lineEdit_hostip->setText(StrLocalIpAddress);
}

// ==================== "获取主机名和IP"按钮 ====================
void GetHostNameIPInfo::on_pushButton_GetHostNameIP_clicked()
{
    GetHostNameAndIpAddress();
}

// ==================== "获取网卡信息"按钮 ====================
void GetHostNameIPInfo::on_pushButton_GetHostInfo_clicked()
{
    QString strTemp = "";
    // 1. 获取所有网卡
    QList<QNetworkInterface> netlist = QNetworkInterface::allInterfaces();
    // 2. 遍历每个网卡
    for (int i = 0; i < netlist.size(); i++)
    {
        QNetworkInterface interfaces = netlist.at(i);
        strTemp = strTemp + "设备名称：" + interfaces.name() + "\n";
        strTemp = strTemp + "硬件地址：" + interfaces.hardwareAddress() + "\n";
        // 3. 遍历网卡上的所有 IP 条目
        QList<QNetworkAddressEntry> entrylist = interfaces.addressEntries();
        for (int k = 0; k < entrylist.count(); k++)
        {
            QNetworkAddressEntry etry = entrylist.at(k);
            strTemp = strTemp + "IP地址：" + etry.ip().toString() + "\n";
            strTemp = strTemp + "子网掩码：" + etry.netmask().toString() + "\n";
            strTemp = strTemp + "广播地址：" + etry.broadcast().toString() + "\n";
        }
    }
    // 4. 弹窗显示
    QMessageBox::information(this, "主机所有信息", strTemp, QMessageBox::Yes);
}