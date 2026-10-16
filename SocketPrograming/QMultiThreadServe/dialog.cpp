#include "dialog.h"
#include "ui_dialog.h"

// ==================== 构造函数 ====================
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    icount = 0;   // 初始化计数
    // 创建多线程服务器，parent 传 this
    // 这样 tcpserverp 里就能通过 (Dialog*)parent 拿到对话框
    tcpserver = new tcpserverp(this);
    // 开始监听（默认监听所有网卡，随机端口）
    if (!tcpserver->listen())
    {
        QMessageBox::critical(this, tr("提示"),
                              tr("多线程服务器无法启动，请重新检查").arg(tcpserver->errorString()));
        close();
        return;
    }
    // 把实际监听的端口显示到界面
    ui->lineEdit_ServerPort->setText(tr("%1").arg(tcpserver->serverPort()));
    // 退出按钮 → 关闭窗口
    connect(ui->pushButton_Exit, SIGNAL(clicked()), this, SLOT(close()));
}
// ==================== 析构函数 ====================
Dialog::~Dialog()
{
    delete ui;
}
// ==================== 更新客户端访问次数 ====================
void Dialog::slotsdispFunc()
{
    ui->lineEdit_Count->setText(tr("客户端请求%1次").arg(++icount));
}