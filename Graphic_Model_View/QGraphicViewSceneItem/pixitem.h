#ifndef PIXITEM_H
#define PIXITEM_H

#include <QGraphicsItem>    // 图元基类
#include <QPixmap>
#include <QPainter>

// ============================================================================
// PixItem —— 自定义图元，用于显示一张图片
// 继承 QGraphicsItem，重写 boundingRect 和 paint
// ============================================================================
class PixItem : public QGraphicsItem
{
public:
    PixItem(QPixmap *pixmap);

private:
    QPixmap pix;    // 值存储，不是指针

public:
    // ---------- 必须重写：返回图元的边界矩形 ----------
    // 场景需要用它做碰撞检测、重绘区域计算
    QRectF boundingRect() const override;

    // ---------- 必须重写：绘制操作 ----------
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
};

#endif