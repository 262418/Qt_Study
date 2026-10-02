#include "dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("QFileDialog测试");

    // ==================== 第 0 行：文件选择 ====================
    FileNameLabel    = new QLabel("文件名称");
    FileNameLineEdit = new QLineEdit;
    FileButton       = new QPushButton("选择...");

    // ==================== 第 1 行：文件大小 ====================
    FileSizeLabel    = new QLabel("文件大小:");
    FileSizeLineEdit = new QLineEdit;

    // ==================== 第 2 行：按钮 ====================
    GetFileInfoButton = new QPushButton("获取文件大小信息");

    // ==================== 网格布局（上两行） ====================
    QGridLayout *glayout = new QGridLayout;

    glayout->addWidget(FileNameLabel,    0, 0);        // 第0行第0列
    glayout->addWidget(FileNameLineEdit, 0, 1);        // 第0行第1列
    glayout->addWidget(FileButton,       0, 2);        // 第0行第2列

    glayout->addWidget(FileSizeLabel,    1, 0);        // 第1行第0列
    glayout->addWidget(FileSizeLineEdit, 1, 1, 1, 2);  // 第1行第1列，跨2列

    // ==================== 按钮行 ====================
    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(GetFileInfoButton);
    // 这里只有一个按钮，也可以加 stretch 让它靠右

    // ==================== 主布局（垂直） ====================
    QVBoxLayout *vlayout = new QVBoxLayout(this);   // 直接成为 Dialog 的布局
    vlayout->addLayout(glayout);                    // 上面两行
    vlayout->addLayout(hlayout);                    // 下面按钮行

    // ==================== 信号槽 ====================
    connect(FileButton, SIGNAL(clicked()), this, SLOT(GetFileInfoFunc()));
    connect(GetFileInfoButton, SIGNAL(clicked()), this, SLOT(GetFileSizeFunc()));
}

Dialog::~Dialog() = default;

// ==================== 打开文件对话框选文件 ====================
void Dialog::GetFileInfoFunc()
{
    // 弹出文件对话框
    // getOpenFileName(父窗口, 标题, 初始目录, 文件过滤器)
    QString strFileName = QFileDialog::getOpenFileName(
        this,          // 父窗口
        "打开",         // 标题
        "/",           // 初始目录（根目录）
        "Files(*.*)"     // 过滤器写法不规范（见下方分析）
        );

    // 把选中的文件路径填入输入框
    // 如果用户取消，strFileName 是空字符串，会清空输入框
    FileNameLineEdit->setText(strFileName);
}

// ==================== 读取文件大小 ====================
void Dialog::GetFileSizeFunc()
{
    // 从输入框取文件路径
    QString strFileNames = FileNameLineEdit->text();

    // QFileInfo：读取文件的各种信息（大小、修改时间、类型等）
    QFileInfo fileinfo(strFileNames);

    // 获取文件大小（字节数）
    // qint64 是 Qt 的 64 位整数类型（可表示超大文件）
    qint64 FileSize = fileinfo.size();

    // 转成字符串显示
    FileSizeLineEdit->setText(QString::number(FileSize));
}