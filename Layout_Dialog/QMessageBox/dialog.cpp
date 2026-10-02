#include "dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    resize(320, 150);                          // 设置窗口大小

    // ==================== 主布局 ====================
    glayout = new QGridLayout(this);           // 直接成为 Dialog 的布局

    // ==================== 创建控件 ====================
    displabel = new QLabel("请你选择一个消息框");

    questionbutton    = new QPushButton("QuestionMsg");
    informationbutton = new QPushButton("InformationMsg");
    warningbutton     = new QPushButton("WarningMsg");
    criticalbutton    = new QPushButton("CriticalMsg");
    aboutbutton       = new QPushButton("AboutMsg");
    aboutqtbutton     = new QPushButton("AboutqtMsg");

    // ==================== 布局摆放 ====================
    // addWidget(控件, 行, 列, 跨行, 跨列)
    glayout->addWidget(displabel,        0, 0, 1, 2);   // 第0行跨2列（占满整行）
    glayout->addWidget(questionbutton,   1, 0);
    glayout->addWidget(informationbutton,1, 1);
    glayout->addWidget(warningbutton,    2, 0);
    glayout->addWidget(criticalbutton,   2, 1);
    glayout->addWidget(aboutbutton,      3, 0);
    glayout->addWidget(aboutqtbutton,    3, 1);

    // ==================== 信号槽连接 ====================
    connect(questionbutton,    SIGNAL(clicked()), this, SLOT(displayquestionMsg()));
    connect(informationbutton, SIGNAL(clicked()), this, SLOT(displayinformationMsg()));
    connect(warningbutton,     SIGNAL(clicked()), this, SLOT(displaywarningMsg()));
    connect(criticalbutton,    SIGNAL(clicked()), this, SLOT(displaycriticalMsg()));
    connect(aboutbutton,       SIGNAL(clicked()), this, SLOT(displayaboutMsg()));
    connect(aboutqtbutton,     SIGNAL(clicked()), this, SLOT(displayaboutqtMsg()));
}

Dialog::~Dialog() = default;

// ==================== Question 消息框 ====================
void Dialog::displayquestionMsg()
{
    displabel->setText("Question Message Box");

    // question() 返回值：用户点了哪个按钮
    // 参数：父窗口, 标题, 内容, 按钮组合, 默认按钮
    switch (QMessageBox::question(
        this,
        "Question消息框",
        "你是否想退出?",
        QMessageBox::Ok | QMessageBox::Cancel,
        QMessageBox::Ok))
    {
    case QMessageBox::Ok:
        displabel->setText("你选择了QuestionMsg命令按钮中的button/Ok!");
        break;
    case QMessageBox::Cancel:
        displabel->setText("你选择了QuestionMsg命令按钮中的button/Cancel!");
        break;
    default:
        break;
    }
    return;
}

// ==================== Information 消息框 ====================
void Dialog::displayinformationMsg()
{
    displabel->setText("Information Message Box");

    // information() 的用法和 question() 完全一样，只是图标不同
    switch (QMessageBox::information(
        this,
        "Information消息框",
        "你是否想退出?",
        QMessageBox::Ok | QMessageBox::Cancel,
        QMessageBox::Ok))
    {
    case QMessageBox::Ok:
        displabel->setText("你选择了InformationMsg命令按钮中的button/Ok!");
        break;
    case QMessageBox::Cancel:
        displabel->setText("你选择了InformationMsg命令按钮中的button/Cancel!");
        break;
    default:
        break;
    }
    return;
}

// ==================== Warning 消息框 ====================
void Dialog::displaywarningMsg()
{
    displabel->setText("Warning Message Box");

    // 这个用了 Save / Discard / Cancel 三种按钮
    switch (QMessageBox::warning(
        this,
        "Warning消息框",
        "是否删除数据库?",
        QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
        QMessageBox::Save))
    {
    case QMessageBox::Save:
        displabel->setText("你选择了WarningMsg命令按钮中的button/Save!");
        break;
    case QMessageBox::Cancel:
        displabel->setText("你选择了WarningMsg命令按钮中的button/Cancel!");
        break;
    case QMessageBox::Discard:
        displabel->setText("你选择了WarningMsg命令按钮中的button/Discard!");
        break;
    default:
        break;
    }
    return;
}

// ==================== Critical 消息框 ====================
void Dialog::displaycriticalMsg()
{
    displabel->setText("Critical Message Box");

    // critical() 也返回用户点的按钮，但这里没接返回值
    // 常用于"严重错误"提示
    QMessageBox::critical(
        this,
        "Critical消息框",
        "数据库文件备份错误请检查"
        );

    return;
}

// ==================== About 消息框 ====================
void Dialog::displayaboutMsg()
{
    displabel->setText("About Message Box");

    // about() 是"关于本程序"对话框
    // 只有一个确定按钮，返回 void
    QMessageBox::about(
        this,
        "About消息框",
        "测试Qt about消息框"
        );

    return;
}

// ==================== AboutQt 消息框 ====================
void Dialog::displayaboutqtMsg()
{
    displabel->setText("About Qt Message Box");

    // aboutQt() 显示 Qt 版本信息
    // 由 Qt 自己弹出，不用自定义内容
    QMessageBox::aboutQt(
        this,
        "About Qt消息框测试"
        );

    return;
}