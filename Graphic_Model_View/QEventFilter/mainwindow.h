#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QImage>          // 图像类
#include <QMouseEvent>      // 鼠标事件
#include <QEvent>            // 事件基类（事件过滤器必须）
#include <QBoxLayout>        // 水平/垂直布局

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    // ---------- 3 个图片标签 ----------
    QLabel *label1jpg;
    QLabel *label2jpg;
    QLabel *label3jpg;

    // ---------- 提示信息标签 ----------
    QLabel *labeldispinfo;

    // ---------- 3 张 QImage（原始图片，用于恢复） ----------
    QImage image1jpg;
    QImage image2jpg;
    QImage image3jpg;

public slots:
    // 事件过滤器函数（必须是这个签名）
    bool eventFilter(QObject *watched, QEvent *event);
};
#endif