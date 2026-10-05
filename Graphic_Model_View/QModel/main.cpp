#include "mainwindow.h"           // ⚠️ 没用到，可以删除

#include <QApplication>
#include <QAbstractItemModel>      // 模型基类（未直接用）
#include <QAbstractItemView>        // 视图基类（用于设置选择模式）
#include <QItemSelectionModel>      // 选择模型（用于同步选择）
#include <QSplitter>                // 可拖动分割器
#include <QFileSystemModel>         // 文件系统模型（核心）
#include <QTreeView>
#include <QListView>
#include <QTableView>
#include <QHeaderView>              // 表头（未直接用）

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // MainWindow w;               // 注释掉了，没用
    // w.show();

    // ==================== 创建模型 ====================
    QFileSystemModel model;                        // 栈上对象
    model.setRootPath(QDir::currentPath());        // 设置根目录为当前工作目录
    // QDir::currentPath() 返回程序运行目录
    // 可以改成 QDir::homePath() 显示用户主目录

    // ==================== 创建三个视图 ====================
    QTreeView tree;            // 树形视图（显示目录层级）
    QListView list;             // 列表视图（显示当前目录内容）
    QTableView table;           // 表格视图（显示详细属性）

    // ==================== 三个视图共享同一个模型 ====================
    tree.setModel(&model);      // 一个模型可以给多个视图使用
    list.setModel(&model);
    table.setModel(&model);

    // ==================== 配置树形视图 ====================
    tree.setColumnWidth(0, 400);
    // 第 0 列（名称列）宽度 400 像素

    tree.setSelectionMode(QAbstractItemView::MultiSelection);
    // 允许多选（Ctrl+点击 或 拖动）

    // ==================== 同步选择模型 ====================
    list.setSelectionModel(tree.selectionModel());
    table.setSelectionModel(tree.selectionModel());
    // 目的：让三个视图共享同一个 selectionModel
    // 效果：在树里选中一个文件，列表和表格里也同步高亮

    // ==================== 连接双击信号 ====================
    // 在树里双击文件夹 → 列表和表格切换到该文件夹
    QObject::connect(&tree, SIGNAL(doubleClicked(QModelIndex)),
                     &list,  SLOT(setRootIndex(QModelIndex)));
    QObject::connect(&tree, SIGNAL(doubleClicked(QModelIndex)),
                     &table, SLOT(setRootIndex(QModelIndex)));

    // ==================== 布局：QSplitter ====================
    QSplitter *qsp = new QSplitter;
    // 没传父对象（会成为独立窗口）

    qsp->addWidget(&tree);
    qsp->addWidget(&list);
    qsp->addWidget(&table);

    qsp->show();
    qsp->setWindowTitle("模型（Model）--测试操作");

    return a.exec();
}