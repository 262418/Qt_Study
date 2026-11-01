#ifndef ANIMATIONBUTTON_H
#define ANIMATIONBUTTON_H

#include <QWidget>
#include <QVariant>
#include <QPropertyAnimation>
#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QEnterEvent> // Qt 6 必须引入这个头文件

class AnimationButton : public QWidget
{
    Q_OBJECT
    // 关键修正：QPropertyAnimation 需要操作属性。
    // 这里声明一个属性 "progress"，动画通过改变这个属性来触发重绘
    Q_PROPERTY(int progress READ progress WRITE setProgress)

public:
    explicit AnimationButton(QWidget *parent = nullptr);
    ~AnimationButton();

    // 提供读写接口给动画使用
    int progress() const { return m_progress; }
    void setProgress(int value);
protected:
    // 鼠标进入和离开事件
    void enterEvent(QEnterEvent *event) override; // Qt 6 参数改为了 QEnterEvent*
    void leaveEvent(QEvent *event) override;
    // 绘图事件
    void paintEvent(QPaintEvent *event) override;
private:
    bool enter; // 记录鼠标是否进入
    bool leave; // 记录鼠标是否离开
    int pixwidth;    // 图片当前宽度
    int pixheight;   // 图片当前高度
    int oldwidth;    // 图片原始宽度
    int oldheight;   // 图片原始高度
    int targetwidth; // 动画过程中的目标宽度
    int targetheight;// 动画过程中的目标高度
    int m_progress;  // 动画的进度值（0 到 5）
    QString text;    // 按钮下方显示的文字
    QString image;   // 按钮图片的路径
    QPropertyAnimation *enteranimation; // 鼠标进入时的动画
    QPropertyAnimation *leaveanimation; // 鼠标离开时的动画
private slots:
    void enterimagechanged(QVariant index);
    void leaveimagechanged(QVariant index);
public slots:
    void settext(QString text);
    void setimage(QString image);
};

#endif // ANIMATIONBUTTON_H