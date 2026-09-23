#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>        // 主窗口基类
#include <QComboBox>          // 下拉框控件
#include <QFontComboBox>      // 字体选择下拉框
#include <QLabel>             // 文字标签
#include <QLineEdit>          // 单行输入框
#include <QPushButton>        // 按钮
#include <QPlainTextEdit>     // 多行纯文本编辑框
#include <QRadioButton>       // 单选按钮
#include <QSpinBox>           // 数字微调框
#include <QTimeEdit>          // 时间编辑框
#include <QDateEdit>          // 日期编辑框
#include <QDateTimeEdit>      // 日期+时间编辑框
#include <QScrollBar>         // 滚动条
#include <QKeySequenceEdit>   // 快捷键录制框
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
private:
    Ui::MainWindow *ui;              // 界面对象，用来访问 .ui 里拖的控件
    QComboBox *combobox;             // 城市下拉框
    QFontComboBox *fontcombobox;     // 字体选择框
    QLabel *qlabels;                 // 显示字体示例
    QLabel *qlabely;                 // 显示输入框内容
    QLineEdit *lineedit;             // 文本输入框
    QPushButton *pushbutton;         // "点击我"按钮
    QPlainTextEdit *plainedit;       // 多行文本框
    QRadioButton *radiobutton;       // "只读模式"单选按钮
    QSpinBox *spinbox;               // 透明度调节框
    QDateTimeEdit *dte;              // 日期+时间
    QTimeEdit *te;                   // 时间
    QDateEdit *de;                   // 日期
    QScrollBar *hscrollbar;          // 水平滚动条
    QScrollBar *vscrollbar;          // 垂直滚动条
    QKeySequenceEdit *kse;           // 快捷键录制框
private slots:
    void comboboxIndex(int);                       // 下拉框选中变化时触发
    void fontcomboboxFunc(QFont);                  // 字体变化时触发
    void pushbuttonclicked();                      // "点击我"按钮点击时触发
    void radiobuttonclicked();                     // "只读模式"单选按钮点击时触发
    void spinboxValueChanged(int);                 // 透明度数值变化时触发
    void keyseqeditChanged(const QKeySequence &);  // 快捷键变化时触发

};
#endif // MAINWINDOW_H
