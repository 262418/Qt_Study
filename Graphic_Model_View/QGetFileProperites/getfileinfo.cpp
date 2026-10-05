#include "getfileinfo.h"

GetFileInfo::GetFileInfo(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("获取文件属性项目实战模块");

    // ==================== 创建控件 ====================
    // ---------- 第 0 行：文件路径 ----------
    labelfilename = new QLabel("文件路径名称：");
    qlineeditfilename = new QLineEdit;
    qpushbuttongetfilename = new QPushButton("打开文件...");

    // ---------- 第 1 行：文件大小 ----------
    labelfilesize = new QLabel("文件容量大小：");
    qlineeditfilesize = new QLineEdit;
    // 应该设为只读，防止用户误改
    // qlineeditfilesize->setReadOnly(true);

    // ---------- 第 2 行：创建时间 ----------
    labelfilecreatetime = new QLabel("文件创建时间：");
    qlineeditfilecreatetime = new QLineEdit;

    // ---------- 第 3 行：修改时间 ----------
    labelfilemodifytime = new QLabel("文件修改时间：");
    qlineeditfilemodifytime = new QLineEdit;

    // ---------- 第 4 行：访问时间 ----------
    labelfileaccesstime = new QLabel("文件访问时间：");
    qlineeditfileaccesstime = new QLineEdit;

    // ---------- 文件属性区 ----------
    qlabelfileattribute = new QLabel("文件属性");

    qcheckboxisfile     = new QCheckBox("文件");
    qcheckboxishide     = new QCheckBox("隐藏属性");
    qcheckboxisreadable = new QCheckBox("只读属性");
    qcheckboxiswritable = new QCheckBox("只写属性");
    qcheckboxisexecute  = new QCheckBox("执行权限");

    qpushbuttongetfileattributeinfo = new QPushButton(
        "获取文件属性的全部数据信息..."
        );

    // ==================== 布局：网格 ====================
    QGridLayout *glayout = new QGridLayout;
    // 没传父对象，后面通过 vlayout->addLayout 加入

    // 第 0 行：文件路径 + 打开按钮
    glayout->addWidget(labelfilename,           0, 0);
    glayout->addWidget(qlineeditfilename,        0, 1);
    glayout->addWidget(qpushbuttongetfilename,   0, 2);

    // 第 1~4 行：大小、时间（跨 2 列）
    glayout->addWidget(labelfilesize,            1, 0);
    glayout->addWidget(qlineeditfilesize,         1, 1, 1, 2);

    glayout->addWidget(labelfilecreatetime,      2, 0);
    glayout->addWidget(qlineeditfilecreatetime,   2, 1, 1, 2);

    glayout->addWidget(labelfilemodifytime,      3, 0);
    glayout->addWidget(qlineeditfilemodifytime,   3, 1, 1, 2);

    glayout->addWidget(labelfileaccesstime,      4, 0);
    glayout->addWidget(qlineeditfileaccesstime,   4, 1, 1, 2);

    // ==================== 布局：水平 ====================
    // ---------- "文件属性" 标题行 ----------
    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(qlabelfileattribute);
    hlayout->addStretch();   // 弹簧，把标题推到左边

    // ---------- 5 个复选框 ----------
    QHBoxLayout *hlayoutat = new QHBoxLayout;
    hlayoutat->addWidget(qcheckboxisfile);
    hlayoutat->addWidget(qcheckboxishide);
    hlayoutat->addWidget(qcheckboxisreadable);
    hlayoutat->addWidget(qcheckboxiswritable);
    hlayoutat->addWidget(qcheckboxisexecute);

    // ---------- 获取按钮 ----------
    QHBoxLayout *hlayoutgetbtn = new QHBoxLayout;
    hlayoutgetbtn->addWidget(qpushbuttongetfileattributeinfo);

    // ==================== 布局：垂直（主布局） ====================
    QVBoxLayout *vlayout = new QVBoxLayout(this);
    // 传 this 使其成为 Dialog 的顶层布局

    vlayout->addLayout(glayout);          // 上面 5 行
    vlayout->addLayout(hlayout);           // "文件属性" 标题
    vlayout->addLayout(hlayoutat);          // 5 个复选框
    vlayout->addLayout(hlayoutgetbtn);      // 获取按钮

    // ==================== 信号槽 ====================
    connect(qpushbuttongetfilename, SIGNAL(clicked()),
            this, SLOT(getfilepathandname()));

    connect(qpushbuttongetfileattributeinfo, SIGNAL(clicked()),
            this, SLOT(getfileattributeinfo()));
}

GetFileInfo::~GetFileInfo()
{
}

// 弹文件对话框选文件
void GetFileInfo::getfilepathandname()
{
    QString filepathname = QFileDialog::getOpenFileName(
        this,                    // 父窗口
        "打开文件对话框",         // 标题
        "/",                     // 初始目录
        "files(*)"
        );

    qlineeditfilename->setText(filepathname);
    // 用户取消时 filepathname 为空，会清空输入框
}

// 获取文件属性
void GetFileInfo::getfileattributeinfo()
{
    QString strfile = qlineeditfilename->text();

    // ---------- 创建 QFileInfo ----------
    QFileInfo qfi(strfile);

    // ==================== 读取各种属性 ====================
    // ---------- 大小 ----------
    qint64 filesize = qfi.size();                    // 字节数

    // ---------- 时间 ----------
    QDateTime createtime = qfi.birthTime();           // 创建时间
    QDateTime lastmodifytime = qfi.lastModified();     // 最后修改
    QDateTime lastaccesstime = qfi.lastRead();          // 最后访问

    // ---------- 布尔属性 ----------
    bool bfile    = qfi.isFile();           // 是普通文件
    bool bhide    = qfi.isHidden();          // 隐藏
    bool bread    = qfi.isReadable();        // 可读
    bool bwrite   = qfi.isWritable();        // 可写
    bool bexecute = qfi.isExecutable();      // 可执行

    // ==================== 更新 UI ====================
    // ---------- 文本框 ----------
    qlineeditfilesize->setText(QString::number(filesize));
    qlineeditfilecreatetime->setText(createtime.toString());
    qlineeditfilemodifytime->setText(lastmodifytime.toString());
    qlineeditfileaccesstime->setText(lastaccesstime.toString());
    // 应该用 qlineeditfilesize->setText(QString::number(filesize) + " 字节");

    // ---------- 复选框：三元表达式 ----------
    qcheckboxisfile->setCheckState(bfile    ? Qt::Checked : Qt::Unchecked);
    qcheckboxishide->setCheckState(bhide    ? Qt::Checked : Qt::Unchecked);
    qcheckboxisreadable->setCheckState(bread ? Qt::Checked : Qt::Unchecked);
    qcheckboxiswritable->setCheckState(bwrite ? Qt::Checked : Qt::Unchecked);
    qcheckboxisexecute->setCheckState(bexecute ? Qt::Checked : Qt::Unchecked);
}