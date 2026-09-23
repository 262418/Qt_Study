#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);          // 把 .ui 文件里的控件"搭建"到 this 上
    textlabelFunc();            // 加载图片到 labeljpg
    textbrowserFuncReadText();  // 读取文本到 textBrowser
    ui->progressBar->setRange(0,100000);        // 进度条范围 0~100000
    ui->progressBar->setValue(0);               // 初始值 0

    InitFunc();
    // 手动连接：定时器超时 → on_timerout
    connect(timers,&QTimer::timeout,this,&Widget::on_timerout);
}

Widget::~Widget()
{
    delete ui;
}
void Widget::textlabelFunc(){
    QString fName("D:\\Qt_Project\\Button_Container\\ScrollArea\\Image\\C.jpg");
    QImage qimg;
    if(!(qimg.load(fName))){
        QMessageBox::information(this,"失败","加载jpg图片失败请重新检查");
        return;
    }
    ui->labeljpg->setPixmap(QPixmap::fromImage(qimg));
}
void Widget::textbrowserFuncReadText(){
    QString qStrData;
    QFile qfile("D:\\Qt_Project\\Input_Display\\DisplayWidget\\ABC.txt");   // 同样硬编码路径

    // 打开失败只弹窗，但没 return，后面还会继续执行
    if (!(qfile.open(QIODevice::ReadOnly | QIODevice::Text))) {
        QMessageBox::warning(this, "失败", "加载文件失败请重新检查");
    }
    // 逐行读取，拼接到 qStrData
    while (!qfile.atEnd()) {
        QByteArray ay = qfile.readLine();
        QString strs(ay);
        qStrData.append(strs);
    }
    ui->textBrowser->setText(qStrData);
}
void Widget::on_progressBar_2_clicked()
{
    // 点击后启动一个定时器，每次 +1
    //创建一个定时器，父对象是 this（当前 Widget),传this是为了让 Qt 的对象树自动管理内存——Widget 销毁时，这个定时器会被自动 delete，不用你手动释放。
    QTimer *progressTimer = new QTimer(this);
    connect(progressTimer, &QTimer::timeout, this, [this, progressTimer]{
        int v = ui->progressBar->value();
        if (v >= 100000) {
            progressTimer->stop();
            progressTimer->deleteLater();
            return;
        }
        ui->progressBar->setValue(v + 1);
    });
    progressTimer->start(1);
}
void Widget::on_pushbuttonstart_clicked()
{
    timers->start();          // 启动定时器（每 1000ms 触发一次）
    ui->pushbuttonstart->setEnabled(false);  // 开始后不能再点开始
    ui->pushbuttonpause->setEnabled(true);   // 暂停可用
    ui->pushbuttonreset->setEnabled(true);   // 重置可用
}

void Widget::on_pushbuttonpause_clicked()
{
    timers->stop();           // 停止定时器
    ui->pushbuttonstart->setEnabled(true);
    ui->pushbuttonpause->setEnabled(false);
    ui->pushbuttonreset->setEnabled(true);
}

void Widget::on_pushbuttonreset_clicked()
{
    timers->stop();
    iValues = 0;
    ui->lcdNumber->display(iValues);          // LCD 归零
    ui->pushbuttonstart->setEnabled(true);
    ui->pushbuttonpause->setEnabled(false);    // ⚠️ 重置后暂停不该可用
    ui->pushbuttonreset->setEnabled(false);
}
void Widget::InitFunc(){
    timers=new QTimer(this);
    timers->setInterval(1000);
    timers->stop();
}
void Widget::on_timerout(){
    iValues++;                            // 计数 +1
    ui->lcdNumber->display(iValues);      // 更新 LCD 显示
}
