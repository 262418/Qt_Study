#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QListWidget>       // 列表控件：左侧显示 Linux1~Linux5
#include <QStackedWidget>    // 堆叠页控件：右侧显示对应标签
#include <QLabel>            // 标签控件：作为堆叠页的内容

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog() override;

private:
    QStackedWidget *stacks;
    QListWidget *qlist;
    QLabel *lab1, *lab2, *lab3, *lab4, *lab5;
};
#endif // DIALOG_H