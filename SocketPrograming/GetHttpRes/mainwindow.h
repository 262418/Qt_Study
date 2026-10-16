#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QUrl>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_GetData_clicked();   // 获取数据
    void onReplyFinished();                 // 响应完成

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *mgr;
};

#endif // MAINWINDOW_H