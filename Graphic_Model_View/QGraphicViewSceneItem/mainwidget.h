#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QGraphicsView>     // 视图
#include <QGraphicsScene>    // 场景
#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QSlider>
#include "pixitem.h"
#include <math.h>            // pow 函数

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

    void CreateControlFrameFunc();   // 创建控制面板

private:
    int iAngle;              // 当前旋转角度（累计）
    qreal scalevalues;       // 当前缩放值（累计）
    qreal leanvalues;        // 当前倾斜值（累计）

    QGraphicsView *view;             // 视图
    QFrame *controlframe;            // 控制面板容器
    PixItem *pixitem;                // 图元

private slots:
    void rotateFunc(int);   // 旋转槽
    void scaleFunc(int);    // 缩放槽
    void leanFunc(int);     // 倾斜槽
};
#endif