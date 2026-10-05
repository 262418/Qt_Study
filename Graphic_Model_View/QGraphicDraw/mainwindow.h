#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QComboBox>
#include <QToolButton>
#include <QSpinBox>
#include <QGridLayout>      // 未使用
#include <QColorDialog>
#include <QToolBar>
#include "drawwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void CreateToolBarFunc();   // 创建工具栏

private:
    DrawWidget *drawWidget;         // 中央绘图区

    QLabel *labelstyle;              // "线形风格" 标签
    QComboBox *comboboxlabelstyle;   // 线形下拉框
    QLabel *labelwidth;              // "线形宽度:" 标签
    QSpinBox *spinboxlabelwidth;     // 线宽微调框
    QToolButton *colorbutton;        // 颜色按钮
    QToolButton *clearbutton;        // 清除按钮

private slots:
    void disstyle();                 // 线形变化
    void discolor();                 // 颜色变化
};
#endif