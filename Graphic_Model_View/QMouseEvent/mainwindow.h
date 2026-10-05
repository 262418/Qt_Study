#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QMouseEvent>       // 鼠标事件类
#include <QStatusBar>        // 状态栏
#include <QMessageBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    // 事件函数用 protected（Qt 规范）
    void mouseMoveEvent(QMouseEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;

private:
    QLabel *statuslabel;      // 状态栏左侧：显示事件
    QLabel *mouselabelpos;     // 状态栏右侧：显示坐标

    void disppicture();         // 显示图片
};
#endif