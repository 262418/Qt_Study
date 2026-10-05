#include <QApplication>
#include "modelextended.h"
#include <QTableView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // ---------- 创建模型 ----------
    ModelExtended modelExts;   // 栈对象，自动析构

    // ---------- 创建视图 ----------
    QTableView view;
    view.setModel(&modelExts);                            // 绑定模型
    view.setWindowTitle("ModelExtended模型扩展--测试操作");
    view.resize(500, 300);
    view.show();

    return a.exec();
}