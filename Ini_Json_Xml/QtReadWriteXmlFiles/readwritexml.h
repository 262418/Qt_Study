#ifndef READWRITEXML_H
#define READWRITEXML_H

#include <QDialog>

// QDomDocument 是 Qt 封装的操作 XML 文件的类（注意：不是 QDomComment）
// 项目中常用来存储配置数据信息
#include <QDomDocument>   // 操作整个 XML 文档
#include <QDir>           // 目录操作
#include <QFile>          // 文件操作
#include <QDebug>         // 调试输出
#include <QMessageBox>    // 消息弹窗

QT_BEGIN_NAMESPACE
namespace Ui { class ReadWriteXml; }
QT_END_NAMESPACE

// ReadWriteXml 类：继承自 QDialog（对话框窗口）
class ReadWriteXml : public QDialog
{
    Q_OBJECT   // 使用信号与槽必须加的宏

public:
    ReadWriteXml(QWidget *parent = nullptr);   // 构造函数
    ~ReadWriteXml();                           // 析构函数

private:
    Ui::ReadWriteXml *ui;        // .ui 界面对象，通过 ui->xxx 访问控件

    QFile m_qfiles;              // 文件对象，用于打开/读写 XML 文件
    QString strcurrentfilepath;  // 当前文件所在目录，如 "d:/xmlfiles"
    QString strcurrentfilename;  // 当前文件名，如 "/factoryworkersxml.xml"

public:
    bool openxmlfiles(QString filenamepath);     // 打开指定文件，成功返回 true
    void writexmlfiles();                        // 把界面输入框内容写入 XML
    void readxmlfiles();                         // 从 XML 读取内容显示到界面
    void readrootxml(QDomNodeList sonnodelist);  // 遍历子节点，填充只读输入框

private slots:
    // 命名规则 on_控件名_信号名()，Qt 会自动连接，无需写 connect
    void on_pushButton_WriteXml_clicked();   // "写入"按钮点击时触发
    void on_pushButton_ReadXml_clicked();    // "读取"按钮点击时触发
};

#endif // READWRITEXML_H