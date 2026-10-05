#include "painterarea.h"
#include <QPainter>     // 绘图器

// 构造函数
PainterArea::PainterArea(QWidget *parent)
    : QWidget(parent)
{
    // ---------- 背景设为白色 ----------
    // 用 QSS 替代 setPalette + setAutoFillBackground，更简洁
    setStyleSheet("background-color: white;");

    // ---------- 设置最小尺寸 ----------
    // 防止窗口缩得太小看不清图形
    setMinimumSize(410, 410);
}

// 设置形状
void PainterArea::setShape(Shape shape)
{
    if (m_shape == shape) return;   // 无变化则提前返回，避免多余重绘
    m_shape = shape;
    update();                        // 触发重绘，Qt 随后会调用 paintEvent
}

// 设置画笔
void PainterArea::setPen(const QPen &pen)
{
    m_pen = pen;
    update();
}

// 设置画刷
void PainterArea::setBrush(const QBrush &brush)
{
    m_brush = brush;
    update();
}

// 绘图事件（核心）
void PainterArea::paintEvent(QPaintEvent *event)
{
    // 1. 创建画笔，绑定到当前 widget
    QPainter painter(this);

    // 2. 开启抗锯齿，让线条/边缘更平滑
    painter.setRenderHint(QPainter::Antialiasing, true);

    // 3. 应用画笔和画刷
    painter.setPen(m_pen);
    painter.setBrush(m_brush);

    // 4. 定义绘制区域
    QRect rect(55, 100, 290, 180);
    //         ↑   ↑    ↑    ↑
    //        x   y   宽   高

    // 5. 根据形状绘制
    switch (m_shape) {
    case Shape::Line:
        // 从矩形左上角画到右下角
        painter.drawLine(rect.topLeft(), rect.bottomRight());
        break;

    case Shape::Rectangle:
        // 画矩形（m_pen 描边，m_brush 填充）
        painter.drawRect(rect);
        break;

    case Shape::None:
    default:
        // 什么都不画
        break;
    }

    // 6. 调用基类实现（规范写法，让 Qt 完成默认处理）
    QWidget::paintEvent(event);
}