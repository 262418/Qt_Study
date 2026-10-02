#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>          // 对话框基类
#include <QGridLayout>      // 网格布局
#include <QLineEdit>        // 单行输入框
#include <QPushButton>      // 按钮
#include <QInputDialog>     // 标准输入对话框（本代码核心）

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog() override;

private:
    // ---------- 布局 ----------
    QGridLayout *glayout;

    // ---------- 学号行 ----------
    QPushButton *inputstudentnobutton;         // "学生学号:" 按钮
    QLineEdit   *inputstudentnobuttonLineEdit; // 学号输入框

    // ---------- 姓名行 ----------
    QPushButton *inputstudentnamebutton;
    QLineEdit   *inputstudentnamebuttonLineEdit;

    // ---------- 性别行 ----------
    QPushButton *inputstudentsexbutton;
    QLineEdit   *inputstudentsexbuttonLineEdit;

    // ---------- 成绩行 ----------
    QPushButton *inputstudentscorebutton;
    QLineEdit   *inputstudentscorebuttonLineEdit;

private slots:
    void modifyno();       // 修改学号
    void modifysex();      // 修改性别
};
#endif // DIALOG_H