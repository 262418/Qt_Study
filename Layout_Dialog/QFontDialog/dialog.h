#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>          // 对话框基类
#include <QPushButton>      // 按钮
#include <QLineEdit>        // 单行输入框
#include <QFontDialog>      // 字体对话框
#include <QGridLayout>      // 网格布局
class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog() override;
private:
    QGridLayout *glayout;
    QPushButton *fontbutton;
    QLineEdit *fontlineedit;
private slots:
    void dispFontFunc();
};
#endif // DIALOG_H
