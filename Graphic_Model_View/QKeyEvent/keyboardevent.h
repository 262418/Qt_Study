#ifndef KEYBOARDEVENT_H
#define KEYBOARDEVENT_H

#include <QWidget>
#include <QKeyEvent>       // 键盘事件
#include <QPaintEvent>     // 绘图事件
#include <QPainter>        // 画笔

class keyboardevent : public QWidget
{
    Q_OBJECT

public:
    keyboardevent(QWidget *parent = nullptr);
    ~keyboardevent();

    void drawpixfunc();              // 绘制网格 + 老虎
    void paintEvent(QPaintEvent *);   // 显示到屏幕
    void keyPressEvent(QKeyEvent *);  // 处理键盘

private:
    QPixmap *pix;        // 内存画布（双缓冲）
    QImage image;         // 老虎图片
    int startx;           // 老虎 x 坐标
    int starty;           // 老虎 y 坐标
    int width;            // 窗口宽度
    int height;           // 窗口高度
    int step;             // 移动步长
};
#endif