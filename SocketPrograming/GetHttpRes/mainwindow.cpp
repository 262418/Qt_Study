#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mgr = new QNetworkAccessManager(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ==================== "获取数据"按钮 ====================
void MainWindow::on_pushButton_GetData_clicked()
{
    ui->label_disp->setText("数据正在下载中，请耐心等待......");

    // 创建请求
    QNetworkRequest request(QUrl("https://www.baidu.com"));

    // 允许自动跟随重定向
    request.setAttribute(QNetworkRequest::RedirectPolicyAttribute,
                         QNetworkRequest::NoLessSafeRedirectPolicy);

    // 发起请求，拿到 reply 对象
    QNetworkReply *reply = mgr->get(request);

    // 连接这个 reply 自己的 finished 信号（更精确）
    connect(reply, SIGNAL(finished()), this, SLOT(onReplyFinished()));
}

// ==================== 响应完成 ====================
void MainWindow::onReplyFinished()
{
    // 拿到发信号的 reply 对象
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) return;

    if (reply->error() == QNetworkReply::NoError)
    {
        // 成功：读取数据
        QByteArray data = reply->readAll();
        QString text = QString::fromUtf8(data);

        ui->textBrowser->setPlainText(text);
        ui->label_disp->setText("下载完成！");
    }else{
        // 失败
        QMessageBox::warning(this, "错误",
                             "请求失败：" + reply->errorString());
        ui->label_disp->setText("下载失败");
    }
    reply->deleteLater();   // 释放内存
}