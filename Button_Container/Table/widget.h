#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTabWidget>       // 标签页控件
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget() override;
private:
    QTabWidget * tabWidgetUI;
private slots:
    void MsgCommit();
};
#endif // WIDGET_H
