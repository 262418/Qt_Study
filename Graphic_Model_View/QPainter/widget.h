#ifndef WIDGET_H
#define WIDGET_H

#include "painterarea.h"
#include <QWidget>

// 前向声明：减少头文件依赖，加快编译
class QLabel;
class QComboBox;
class QPushButton;
class QSpinBox;
class QGridLayout;

// ============================================================================
// Widget —— 主窗口
// 左侧绘图区，右侧控制面板（形状/颜色/宽度等）
// ============================================================================
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget() override;

private slots:
    void onShapeChanged(int index);           // 形状下拉框变化
    void onPenColorClicked();                  // "画笔颜色"按钮
    void onBrushColorClicked();                // "填充颜色"按钮
    void onPenWidthChanged(int width);         // 画笔宽度变化

private:
    // ---------- UI 控件 ----------
    PainterArea *paintArea;         // 绘图区
    QLabel *shapeLabel;              // "绘制形状:" 标签
    QComboBox *shapeCombo;           // 形状下拉框

    QLabel *penColorLabel;           // "画笔颜色:" 标签
    QPushButton *penColorBtn;        // 画笔颜色按钮
    QLabel *brushColorLabel;         // "填充颜色:" 标签
    QPushButton *brushColorBtn;      // 填充颜色按钮

    QLabel *penWidthLabel;           // "画笔宽度:" 标签
    QSpinBox *penWidthSpin;          // 画笔宽度微调框

    QGridLayout *controlLayout;      // 右侧控制面板布局
};
#endif // WIDGET_H