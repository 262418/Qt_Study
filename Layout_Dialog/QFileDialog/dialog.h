#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>           // 标签
#include <QLineEdit>        // 输入框
#include <QPushButton>      // 按钮
#include <QHBoxLayout>      // 水平布局
#include <QVBoxLayout>      // 垂直布局
#include <QFileDialog>      // 文件选择对话框（本代码核心）

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog() override;

private:
    QLabel *FileNameLabel;              // "文件名称" 标签
    QLineEdit *FileNameLineEdit;        // 文件路径输入框
    QPushButton *FileButton;            // "选择..." 按钮

    QLabel *FileSizeLabel;              // "文件大小:" 标签
    QLineEdit *FileSizeLineEdit;        // 大小显示框

    QPushButton *GetFileInfoButton;     // "获取文件大小信息" 按钮

private slots:
    void GetFileInfoFunc();             // 弹文件对话框
    void GetFileSizeFunc();             // 读取文件大小
};
#endif