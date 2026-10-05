#include "drawwidget.h"

// 构造函数
DrawWidget::DrawWidget(QWidget *parent)
    : QWidget{parent}
{
    // ---------- 设置白色背景 ----------
    setAutoFillBackground(true);
    setPalette(QPalette(Qt::white));

    // ---------- 创建画布 ----------
    pix = new QPixmap(size());    // 此时 size() 可能还是默认值
    pix->fill(Qt::white);         // 填充白色

    setMinimumSize(600, 400);

    // style、widthss、color 都没初始化！
}

// 设置线形风格
void DrawWidget::setStyle(int s)
{
    style = s;
    // 没 update()！不过 drawLine 时用的是最新的 style，下次画线生效
}

// 设置线宽
void DrawWidget::setWidth(int w)
{
    widthss = w;
}

// 设置颜色
void DrawWidget::setColor(QColor c)
{
    color = c;
}

// 清空画布
void DrawWidget::clearFunc()
{
    delete pix;                           // 释放旧画布
    pix = new QPixmap(size());            // 新建同样大小
    pix->fill(Qt::white);                 // 填白
    update();                             // 触发重绘
}

// 鼠标按下：记录起始点
void DrawWidget::mousePressEvent(QMouseEvent *e)
{
    startpos = e->pos();                  // 记录起点（客户区坐标）
    if (e->button() == Qt::LeftButton) {
        startpos = e->pos();
    }
}

// 鼠标移动：绘制线段（核心）
void DrawWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (!(e->buttons() & Qt::LeftButton)) return;   // 建议加：只响应左键拖动

    // ---------- 准备画笔 ----------
    QPen pen;
    pen.setStyle(static_cast<Qt::PenStyle>(style));
    pen.setWidth(widthss);
    pen.setColor(color);

    // ---------- 在 pixmap 上绘制 ----------
    QPainter painter(pix);                   // 开始画到 pixmap
    painter.setRenderHint(QPainter::Antialiasing, true);   // 线条更平滑
    painter.setPen(pen);
    painter.drawLine(startpos, e->pos());   // 从上一位置画到当前位置
    startpos = e->pos();                    // 更新起点
    update();                               // 触发重绘，显示到屏幕
}

// 绘图事件：把 pixmap 显示到窗口
void DrawWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(QPoint(0, 0), *pix);   // 一次性把缓冲画到窗口
}

// 窗口大小变化：扩展画布
void DrawWidget::resizeEvent(QResizeEvent *event)
{
    // 只在窗口变大时扩展（变小就不管，避免内容被裁）
    if (height() > pix->height() || width() > pix->width()) {
        QPixmap *newPix = new QPixmap(size());   // 新建大画布
        newPix->fill(Qt::white);                  // 填白
        QPainter ps(newPix);
        ps.drawPixmap(QPoint(0, 0), *pix);         // 把旧内容复制过来
        delete pix;                                 // 释放旧画布
        pix = newPix;                                // 指向新画布
    }
    QWidget::resizeEvent(event);
}