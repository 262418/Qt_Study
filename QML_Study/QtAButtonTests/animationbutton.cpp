#include "animationbutton.h"

AnimationButton::AnimationButton(QWidget *parent) : QWidget(parent)
{
    enter = false;
    leave = false;
    m_progress = 0;
    pixwidth = 0; pixheight = 0;
    oldwidth = 0; oldheight = 0;

    // 修正：动画必须绑定到我们刚才写的 "progress" 属性上
    enteranimation = new QPropertyAnimation(this, "progress", this);
    enteranimation->setStartValue(0);
    enteranimation->setEndValue(5); // 动画从 0 变到 5
    enteranimation->setDuration(200); // 耗时 200 毫秒
    connect(enteranimation, SIGNAL(valueChanged(QVariant)),
            this, SLOT(enterimagechanged(QVariant)));

    leaveanimation = new QPropertyAnimation(this, "progress", this);
    leaveanimation->setStartValue(5); // 离开时从 5 变回 0
    leaveanimation->setEndValue(0);
    leaveanimation->setDuration(200);
    connect(leaveanimation, SIGNAL(valueChanged(QVariant)),
            this, SLOT(leaveimagechanged(QVariant)));
}

AnimationButton::~AnimationButton()
{
    delete enteranimation;
    delete leaveanimation;
}

// 当动画修改 progress 时，这个函数会被自动调用
void AnimationButton::setProgress(int value)
{
    m_progress = value;
    update(); // 触发重绘
}

// 鼠标进入
void AnimationButton::enterEvent(QEnterEvent *event)
{
    Q_UNUSED(event);
    enter = true;
    leave = false;

    // 把当前宽度记录下来作为动画的基准
    pixwidth = oldwidth;
    pixheight = oldheight;

    enteranimation->start();
}

// 鼠标离开
void AnimationButton::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    enter = false;
    leave = true;

    leaveanimation->start();
}

// 核心绘制函数
void AnimationButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    if (image.isEmpty()) return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // 开启抗锯齿

    // 计算当前应该画多大的图片
    QPixmap pix(image);
    pix = pix.scaled(targetwidth, targetheight, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // 计算居中位置
    int pixx = rect().center().x() - targetwidth / 2;
    int pixy = rect().center().y() - targetheight / 2;
    QPoint point(pixx, pixy);

    // 画图片
    painter.drawPixmap(point, pix);

    // 在底部画文字
    painter.drawText(QRectF(0, height() - 20, width(), 20), Qt::AlignCenter, text);
}

// 鼠标进入动画触发
void AnimationButton::enterimagechanged(QVariant index)
{
    int i = index.toInt(); // i 从 0 慢慢变成 5
    // 宽度和高度逐渐变大
    targetwidth = pixwidth + i * 5;
    targetheight = pixheight + i * 5;
    update();
}

// 鼠标离开动画触发
void AnimationButton::leaveimagechanged(QVariant index)
{
    int i = index.toInt(); // i 从 5 慢慢变成 0
    // 宽度和高度逐渐缩小
    targetwidth = pixwidth - (5 - i) * 5;
    targetheight = pixheight - (5 - i) * 5;
    update();
}

void AnimationButton::settext(QString text)
{
    this->text = text;
    update();
}

void AnimationButton::setimage(QString image)
{
    this->image = image;
    QPixmap pix(image);

    // 保存原始尺寸
    oldwidth = pix.width();
    oldheight = pix.height();

    pixwidth = oldwidth;
    pixheight = oldheight;

    targetwidth = pixwidth;
    targetheight = pixheight;

    update();
}