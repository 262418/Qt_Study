#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
private:
    QPushButton *pb1,*pb2;
private slots:
    void pushbutton1_clicked();
    void pushbutton2_clicked();
};
#endif // MAINWINDOW_H
