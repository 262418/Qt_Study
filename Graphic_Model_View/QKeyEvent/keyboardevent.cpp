#include "keyboardevent.h"

keyboardevent::keyboardevent(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("键盘事件测试：控制图片动向");

    // ==================== 设置白色背景 ====================
    setAutoFillBackground(true);
    QPalette plet = this->palette();
    plet.setColor(QPalette::Window, Qt::white);
    setPalette(plet);

    // ==================== 固定窗口大小 800×600 ====================
    setMinimumSize(800, 600);
    setMaximumSize(800, 600);

    width = size().width();
    height = size().height();

    // ==================== 创建内存画布 ====================
    pix = new QPixmap(width, height);
    pix->fill(Qt::white);

    // ==================== 加载图片 ====================
    image.load("D:/Qt_Project/Graphic_Model_View/images/D.png");   // 硬编码路径

    // ==================== 初始位置和步长 ====================
    startx = 30;
    starty = 30;
    step = 30;

    // ==================== 首次绘制 ====================
    drawpixfunc();

    resize(800, 600);
}

keyboardevent::~keyboardevent()
{
    delete pix;
}


// 绘制网格
void keyboardevent::drawpixfunc()
{
    // ---------- 清空画布为绿色 ----------
    pix->fill(Qt::green);

    QPainter *painter = new QPainter;
    QPen pen(Qt::DashDotLine);              // 点划线

    // ---------- 画竖线 ----------
    for (int i = step; i < width; i += step) {
        painter->begin(pix);                 // 循环里反复 begin/end
        painter->setPen(pen);
        painter->drawLine(QPoint(i, 0), QPoint(i, height));
        painter->end();
    }

    // ---------- 画横线 ----------
    for (int j = step; j < height; j += step) {
        painter->begin(pix);
        painter->setPen(pen);
        painter->drawLine(QPoint(0, j), QPoint(width, j));
        painter->end();
    }

    // ---------- 绘制图片 ----------
    painter->begin(pix);
    painter->drawImage(QPoint(startx, starty), image);
    painter->end();

    delete painter;
}

// 绘图事件：把 pixmap 显示到窗口
void keyboardevent::paintEvent(QPaintEvent *)
{
    QPainter pt;
    pt.begin(this);
    pt.drawPixmap(QPoint(0, 0), *pix);   // 一次性复制到窗口
    pt.end();
}

// 键盘按下：控制图片移动
void keyboardevent::keyPressEvent(QKeyEvent *evt)
{
    // ---------- 把位置对齐到网格 ----------
    startx = startx - startx % step;
    starty = starty - starty % step;
    // 例如 startx=37, step=30 → 37-37%30=30

    // ---------- 左键 ----------
    if (evt->key() == Qt::Key_Left) {
        startx = (startx - step < 0) ? startx : startx - step;
        // 边界检查：左边不能小于 0
    }

    // ---------- 右键 ----------
    if (evt->key() == Qt::Key_Right) {
        startx = (startx + step + image.width() > width) ? startx : startx + step;
        // 边界检查：右边不能超出窗口
    }

    // ---------- 上键 ----------
    if (evt->key() == Qt::Key_Up) {
        starty = (starty - step < 0) ? starty : starty - step;
    }

    // ---------- 下键 ----------
    if (evt->key() == Qt::Key_Down) {
        starty = (starty + step + image.height() > height) ? starty : starty + step;
    }

    // ---------- 重绘 ----------
    drawpixfunc();
    update();   // 触发 paintEvent
}