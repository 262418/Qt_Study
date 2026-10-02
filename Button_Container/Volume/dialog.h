#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>          // QDialog 基类，对话框窗口
#include <QLabel>         // QLabel 标签控件
#include <QPushButton>    // QPushButton 按钮控件
#include <Qlineedit>        // QLineEdit 单行文本输入框
class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog() override;
private:
    QLabel *lab1, *lab2;    // 两个标签指针：lab1提示输入，lab2显示结果
    QLineEdit *lEdit;       // 输入框指针：接收用户输入的半径
    QPushButton *pbt;       // 按钮指针：触发计算（虽然实际用的是 textChanged 信号）

private slots:              // 槽函数区（Qt 关键字，可被信号连接）
    void CalcBallVolume();  // 计算球体积的槽函数
};
#endif // DIALOG_H
