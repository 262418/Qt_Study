#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QGridLayout>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog() override;

private:
    // ---------- 布局 ----------
    QGridLayout *glayout;

    // ---------- 5 组"标签 + 值标签" ----------
    QLabel *labelgeometry;         // "函数geometry():"
    QLabel *labelgeometryvalue;    // geometry() 的值
    QLabel *labelwidth;            // "函数width():"
    QLabel *labelwidthvalue;       // width() 的值
    QLabel *labelheight;           // "函数height():"
    QLabel *labelheightvalue;      // height() 的值
    QLabel *labelrect;             // "函数rect()"
    QLabel *labelrectvalue;        // rect() 的值
    QLabel *labelsize;             // "函数size():"
    QLabel *labelsizevalue;        // size() 的值

    // ---------- 事件重写 ----------
    // 覆写 QWidget 的两个事件处理函数
    void resizeEvent(QResizeEvent *);   // 窗口大小变化时调用
    void moveEvent(QMoveEvent *);        // 窗口移动时调用

public:
    // 更新所有标签的函数（public，方便外部调用）
    void UpdateLabelFunc();
};
#endif // DIALOG_H