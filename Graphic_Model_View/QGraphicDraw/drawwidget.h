#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>
#include <QtGui>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QPixmap>          // 内存缓冲
#include <QPainter>
#include <QPalette>
#include <QPen>

class DrawWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DrawWidget(QWidget *parent = nullptr);

    // 事件重写
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);

signals:
public slots:
    // ---------- 属性设置槽 ----------
    void setStyle(int);         // 设置线形风格
    void setWidth(int);         // 设置线宽
    void setColor(QColor);      // 设置颜色
    void clearFunc();           // 清空画布

private:
    QPixmap *pix;               // 内存缓冲画布
    QPoint startpos;            // 上一鼠标位置（画线起点）
    QPoint endPos;              // 未使用
    int style, widthss;         // 未初始化
    QColor color;               // 未初始化
};

#endif