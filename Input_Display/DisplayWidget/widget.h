#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMessageBox>   // 弹窗提示（加载失败时用）
#include <QFile>         // 文件读写
#include <QTimer>        // 定时器
QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;            // 前向声明：ui_widget.h 里生成的界面类
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT            // 前向声明：ui_widget.h 里生成的界面类

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget() override;
private:
    int iValues=0;      // 计时器的当前值，LCD 显示用
    QTimer *timers;     // 定时器对象
    void InitFunc();    // 初始化定时器
private slots:
    // 这些是"槽函数"，Qt 通过命名规则自动连接（on_控件名_信号）progressBar_2,pushbuttonstart都是ui界面中的控件名
    void on_progressBar_2_clicked();
    void on_pushbuttonstart_clicked();
    void on_pushbuttonpause_clicked();
    void on_pushbuttonreset_clicked();

    void on_timerout();
private:
    Ui::Widget *ui;     // 指向界面对象的指针，所有控件都通过它访问
    void textlabelFunc();   // 加载图片到 label
    void textbrowserFuncReadText();     // 读文件到 textBrowser
};
#endif // WIDGET_H
