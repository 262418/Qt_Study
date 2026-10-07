#ifndef QJSONOPER_H
#define QJSONOPER_H

#include <QDialog>   // 对话框基类

QT_BEGIN_NAMESPACE
namespace Ui { class QJsonOper; }
QT_END_NAMESPACE

// QJsonOper 类：继承自 QDialog（对话框窗口）
class QJsonOper : public QDialog
{
    Q_OBJECT   // 使用信号与槽必须加的宏

public:
    QJsonOper(QWidget *parent = nullptr);   // 构造函数
    ~QJsonOper();                           // 析构函数

private slots:
    // 命名规则 on_控件名_信号名()，Qt 会自动连接，无需写 connect
    void on_pushButtonWriteJson_clicked();   // "写入JSON"按钮点击
    void on_pushButtonReadJson_clicked();    // "读取JSON"按钮点击

private:
    Ui::QJsonOper *ui;   // .ui 界面对象，通过 ui->xxx 访问控件
};

#endif // QJSONOPER_H