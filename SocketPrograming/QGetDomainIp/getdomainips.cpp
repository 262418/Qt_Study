#include "getdomainips.h"
#include "ui_getdomainips.h"

// ==================== 构造函数 ====================
GetDomainIps::GetDomainIps(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GetDomainIps)
{
    ui->setupUi(this);
    // 默认填一个测试域名
    ui->lineEdit_InputUrl->setText("www.126.com");
}

// ==================== 析构函数 ====================
GetDomainIps::~GetDomainIps()
{
    delete ui;
}

// ==================== 协议枚举转字符串 ====================
QString GetDomainIps::ProtocolTypeName(QAbstractSocket::NetworkLayerProtocol protocoltype)
{
    switch (protocoltype)
    {
    case QAbstractSocket::IPv4Protocol:
        return "IPv4 Protocol";
    case QAbstractSocket::IPv6Protocol:
        return "IPv6 Protocol";
    case QAbstractSocket::AnyIPProtocol:
        return "Any IP Protocol";
    default:
        return "Unknown Network Layer Protocol";
    }
}

// ==================== "清空"按钮 ====================
void GetDomainIps::on_pushButton_ClearData_clicked()
{
    ui->plainTextEdit_DomainIP->clear();   // 清空文本框
}

// ==================== 解析完成回调 ====================
void GetDomainIps::LookupHostInfoFunc(const QHostInfo &host)
{
    QList<QHostAddress> addresslist = host.addresses();   // 所有 IP 地址
    for (int i = 0; i < addresslist.count(); i++)
    {
        QHostAddress addr = addresslist.at(i);   // 取一个 IP（改名避免遮蔽）
        ui->plainTextEdit_DomainIP->appendPlainText(
            "协议类型：" + ProtocolTypeName(addr.protocol()));
        ui->plainTextEdit_DomainIP->appendPlainText(
            "本地IP地址：" + addr.toString());
        ui->plainTextEdit_DomainIP->appendPlainText("");   // 空行
    }
}

// ==================== "获取IP"按钮 ====================
void GetDomainIps::on_pushButton_GetDomainIP_clicked()
{
    QString strhostname = ui->lineEdit_InputUrl->text();   // 拿域名
    ui->plainTextEdit_DomainIP->appendPlainText(
        "你所查询主机信息：" + strhostname);
    // 发起异步解析请求，完成后调用 LookupHostInfoFunc
    QHostInfo::lookupHost(strhostname, this,
                          SLOT(LookupHostInfoFunc(QHostInfo)));
}