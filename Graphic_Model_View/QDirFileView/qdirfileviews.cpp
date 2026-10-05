#include "qdirfileviews.h"

QDirFileViews::QDirFileViews(QWidget *parent)
    : QDialog(parent)
{
    resize(500, 350);
    setWindowTitle("QDir类综合控件应用测试");

    // ==================== 创建控件 ====================
    filelineedit = new QLineEdit("/");       // 初始路径是根目录
    filelistwidget = new QListWidget;

    // ==================== 布局 ====================
    glayout = new QVBoxLayout(this);          // glayout 是垂直布局，不是网格
    glayout->addWidget(filelineedit);
    glayout->addWidget(filelistwidget);

    // ==================== 信号槽 ====================
    // ---------- 路径框回车 ----------
    connect(filelineedit, SIGNAL(returnPressed()),
            this, SLOT(dispdir(QDir)));

    // ---------- 列表项双击 ----------
    connect(filelistwidget, SIGNAL(itemDoubleClicked(QListWidgetItem *)),
            this, SLOT(dispdirshow(QListWidgetItem *)));

    // ==================== 初始加载根目录 ====================
    QString root = "/";
    QDir rootDir(root);
    QStringList strlist;
    strlist << "*";                          // 过滤：所有文件

    // entryInfoList 获取目录下所有文件的 QFileInfo 列表
    QFileInfoList list = rootDir.entryInfoList(strlist);

    dispfileinfolist(list);                    // 显示到列表
}

QDirFileViews::~QDirFileViews() = default;

// 显示文件/目录列表
void QDirFileViews::dispfileinfolist(QFileInfoList list)
{
    filelistwidget->clear();                 // 清空原有内容

    for (unsigned int i = 0; i < list.count(); i++) {
        QFileInfo tempfileinfo = list.at(i);

        if (tempfileinfo.isDir()) {
            // ---------- 目录：用目录图标 ----------
            QIcon ico("d:/dir.jpg");          // 硬编码路径
            QString filename = tempfileinfo.fileName();
            QListWidgetItem *temp = new QListWidgetItem(ico, filename);
            filelistwidget->addItem(temp);
        }
        else if (tempfileinfo.isFile()) {
            // ---------- 文件：用文件图标 ----------
            QIcon ico("d:/file.jpg");
            QString filename = tempfileinfo.fileName();
            QListWidgetItem *temp = new QListWidgetItem(ico, filename);
            filelistwidget->addItem(temp);
        }
    }
}

// 刷新目录（显示指定目录的内容）
void QDirFileViews::dispdir(QDir dir)
{
    QStringList strlist;
    strlist << "*";

    // entryInfoList(名字过滤, 属性过滤, 排序)
    QFileInfoList fileinfolist = dir.entryInfoList(
        strlist,
        QDir::AllEntries,          // 显示所有条目（文件+目录）
        QDir::DirsFirst            // 目录排前面
        );

    dispfileinfolist(fileinfolist);
}

// 双击列表项（进入子目录）
void QDirFileViews::dispdirshow(QListWidgetItem *item)
{
    QDir dir;
    QString str = item->text();          // 双击项的名字

    dir.setPath(filelineedit->text());     // 从路径框取当前目录
    dir.cd(str);                            // 进入子目录

    filelineedit->setText(dir.absolutePath());   // 更新路径框
    dispdir(dir);                            // 刷新列表
}