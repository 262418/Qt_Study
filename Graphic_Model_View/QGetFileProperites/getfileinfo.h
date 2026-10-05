#ifndef GETFILEINFO_H
#define GETFILEINFO_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QFileDialog>      // 文件选择对话框
#include <QFileInfo>        // 文件信息类
#include <QDateTime>        // 日期时间
#include <QHBoxLayout>
#include <QVBoxLayout>

class GetFileInfo : public QDialog
{
    Q_OBJECT

public:
    GetFileInfo(QWidget *parent = nullptr);
    ~GetFileInfo();

private:
    // ---------- 文件路径行 ----------
    QLabel *labelfilename;
    QLineEdit *qlineeditfilename;
    QPushButton *qpushbuttongetfilename;

    // ---------- 文件大小 ----------
    QLabel *labelfilesize;
    QLineEdit *qlineeditfilesize;

    // ---------- 创建时间 ----------
    QLabel *labelfilecreatetime;
    QLineEdit *qlineeditfilecreatetime;

    // ---------- 修改时间 ----------
    QLabel *labelfilemodifytime;
    QLineEdit *qlineeditfilemodifytime;

    // ---------- 访问时间 ----------
    QLabel *labelfileaccesstime;
    QLineEdit *qlineeditfileaccesstime;

    // ---------- 文件属性 ----------
    QLabel *qlabelfileattribute;

    QCheckBox *qcheckboxisfile;       // 是否文件
    QCheckBox *qcheckboxishide;       // 是否隐藏
    QCheckBox *qcheckboxisreadable;   // 是否可读
    QCheckBox *qcheckboxiswritable;   // 是否可写
    QCheckBox *qcheckboxisexecute;    // 是否可执行

    QPushButton *qpushbuttongetfileattributeinfo;

private slots:
    void getfilepathandname();        // 弹文件对话框
    void getfileattributeinfo();      // 读文件属性
};
#endif