#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPushButton>      // 按钮
#include <QFrame>           // 框架（用来显示颜色）
#include <QColorDialog>     // 颜色对话框
#include <QGridLayout>      // 网格布局
class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog() override;
private:
    QGridLayout *glayout;
    QPushButton *colorbutton;
    QFrame *colorFrame;
private slots:
    void dispcolorFunc();
};
#endif // DIALOG_H
