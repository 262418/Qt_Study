#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>       // 工具栏类
#include <QToolButton>    // 工具按钮类
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
private:
    QToolBar *tbar;
    QToolButton *tbutton;
};
#endif // MAINWINDOW_H
