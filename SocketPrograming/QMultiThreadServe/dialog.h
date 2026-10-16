#ifndef DIALOG_H
#define DIALOG_H

class tcpserverp;   // 向前声明
#include <QDialog>
#include <QMessageBox>
#include "tcpserverp.h"   // 具体定义

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;

private:
    int icount;                    // 统计客户端访问次数
    tcpserverp *tcpserver;         // 多线程服务器对象

public slots:
    void slotsdispFunc();          // 更新界面计数的槽
};

#endif // DIALOG_H