#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>          // 对话框基类
#include <QLabel>           // 标签：显示反馈文字
#include <QPushButton>      // 按钮
#include <QGridLayout>      // 网格布局
#include <QMessageBox>      // 消息框（本代码核心）

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog() override;

private:
    QGridLayout *glayout;           // 主布局
    QLabel *displabel;              // 顶部提示标签
    QPushButton *questionbutton;    // Question 按钮
    QPushButton *informationbutton; // Information 按钮
    QPushButton *warningbutton;     // Warning 按钮
    QPushButton *criticalbutton;    // Critical 按钮
    QPushButton *aboutbutton;       // About 按钮
    QPushButton *aboutqtbutton;     // AboutQt 按钮

private slots:
    void displayquestionMsg();       // 弹 Question 消息框
    void displayinformationMsg();    // 弹 Information 消息框
    void displaywarningMsg();        // 弹 Warning 消息框
    void displaycriticalMsg();       // 弹 Critical 消息框
    void displayaboutMsg();          // 弹 About 消息框
    void displayaboutqtMsg();        // 弹 AboutQt 消息框
};
#endif