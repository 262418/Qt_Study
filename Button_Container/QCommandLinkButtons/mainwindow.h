#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCommandLinkButton>     // 命令链接按钮类
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
private:
    QCommandLinkButton *qclb;
private slots:
    void qclbClicked();
};
#endif // MAINWINDOW_H
