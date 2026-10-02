#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QListView>            // 列表视图（显示数据）
#include <QStringListModel>     // 字符串列表模型（数据源）
#include <QMessageBox>          // 消息框

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;                   // Qt Designer 生成的 UI 类前向声明
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget() override;

private:
    Ui::Widget *ui;             // UI 对象（来自 .ui 文件）
    QListView *qlv;             // 列表视图

private slots:
    // 槽函数带参数：接收被点击项的 QModelIndex
    void SlotClickedFunc(const QModelIndex &index);
};
#endif