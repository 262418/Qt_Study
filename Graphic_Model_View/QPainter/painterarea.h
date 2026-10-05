#ifndef PAINTERAREA_H
#define PAINTERAREA_H

#include <QWidget>      // 基类
#include <QPen>         // 画笔（控制线条样式）
#include <QBrush>       // 画刷（控制填充样式）

// ============================================================================
// PainterArea —— 自定义绘图控件
// 重写 paintEvent，根据 m_shape 绘制直线或矩形
// ============================================================================
class PainterArea : public QWidget
{
    Q_OBJECT

public:
    // ---------- 形状枚举 ----------
    // 使用 enum class 避免命名污染（Line、Rectangle 不会外泄）
    // None 用于"清除"状态
    enum class Shape {
        None,        // 不绘制
        Line,        // 直线
        Rectangle    // 矩形
    };

    explicit PainterArea(QWidget *parent = nullptr);

    // ---------- 属性设置接口 ----------
    // 每个 setter 都调用 update() 触发重绘
    void setShape(Shape shape);
    void setPen(const QPen &pen);        // const 引用：避免拷贝
    void setBrush(const QBrush &brush);

    // ---------- 属性读取接口 ----------
    // 用于外部查询当前状态（比如同步 UI 控件）
    Shape shape() const { return m_shape; }
    const QPen &pen() const { return m_pen; }
    const QBrush &brush() const { return m_brush; }

protected:
    // ---------- 绘图事件 ----------
    // 每次需要重绘时由 Qt 自动调用
    void paintEvent(QPaintEvent *event) override;

private:
    // ---------- 成员变量（带初始值） ----------
    Shape m_shape = Shape::None;                      // 默认不绘制
    QPen m_pen = QPen(Qt::black, 2);                   // 黑色 2px 实线
    QBrush m_brush = QBrush(Qt::yellow);               // 黄色实心填充
};

#endif // PAINTERAREA_H