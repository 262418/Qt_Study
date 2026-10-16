#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "workerthread.h"    // 自定义线程类
#include <QPushButton>       // 按钮
#include <QHBoxLayout>       // 水平布局

#define MAXSIZE 5   // 定义线程数量为 5

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    QPushButton *startbutton;    // "开始"按钮
    QPushButton *stopbutton;     // "停止"按钮
    QPushButton *exitbutton;     // "退出"按钮

    // 线程数组：5 个 WorkerThread 指针
    WorkerThread *workerthread[MAXSIZE];

public slots:
    void onSlotStart();   // "开始"槽函数
    void onSlotStop();    // "停止"槽函数
};

#endif // DIALOG_H