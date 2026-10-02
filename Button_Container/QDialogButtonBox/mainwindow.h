#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialogButtonBox>     // 对话框按钮盒
#include <QPushButton>          // 普通按钮（用来自定义按钮）
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
private:
    QDialogButtonBox *qdbb;
    QPushButton *qpb;
private slots:
    // 槽函数：接收被点击的按钮指针
    // QAbstractButton 是所有按钮的基类（QPushButton、QToolButton 等的父类）
    void qdbbqpbClicked(QAbstractButton *);
};
#endif // MAINWINDOW_H
