#ifndef QDIRFILEVIEWS_H
#define QDIRFILEVIEWS_H

#include <QDialog>              // 对话框基类
#include <QListWidget>           // 列表框
#include <QListWidgetItem>
#include <QLineEdit>             // 单行输入框
#include <QDir>                  // 目录操作
#include <QFileInfoList>          // 文件信息列表
#include <QVBoxLayout>            // 垂直布局
#include <QStringList>

class QDirFileViews : public QDialog
{
    Q_OBJECT

public:
    QDirFileViews(QWidget *parent = nullptr);
    ~QDirFileViews();

private:
    QLineEdit *filelineedit;         // 显示/输入当前目录路径
    QListWidget *filelistwidget;      // 显示目录内容
    QVBoxLayout *glayout;             // 主布局

public:
    void dispfileinfolist(QFileInfoList list);

public slots:
    void dispdir(QDir dir);              // 刷新目录
    void dispdirshow(QListWidgetItem *item);   // 双击响应
};
#endif