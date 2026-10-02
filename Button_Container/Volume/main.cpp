#include "dialog.h"

#include <QApplication>    // 每个 Qt GUI 程序都必须有 QApplication

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);  // 创建应用程序对象，管理事件循环

    Dialog w;                    // 创建对话框对象（此时构造函数运行，界面已构建）
    w.setWindowTitle("计算球的体积");  // 设置窗口标题
    w.show();                    // 显示窗口（默认是隐藏的）

    return QApplication::exec(); // 进入事件循环，等待用户操作
}