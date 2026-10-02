#include "dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    // 设置窗口大小和标题
    resize(260, 110);
    setWindowTitle("标准对话框");

    // ==================== 主布局 ====================
    glayout = new QGridLayout(this);   // 直接成为 Dialog 的布局

    // ==================== 学号行 ====================
    inputstudentnobutton = new QPushButton;
    inputstudentnobutton->setText("学生学号:");
    inputstudentnobuttonLineEdit = new QLineEdit("20221001");
    // 这里用构造函数直接设初始文字

    // ==================== 姓名行 ====================
    inputstudentnamebutton = new QPushButton;
    inputstudentnamebutton->setText("学生姓名:");
    inputstudentnamebuttonLineEdit = new QLineEdit("A");

    // ==================== 性别行 ====================
    inputstudentsexbutton = new QPushButton;
    inputstudentsexbutton->setText("学生性别:");
    inputstudentsexbuttonLineEdit = new QLineEdit("男");

    // ==================== 成绩行 ====================
    inputstudentscorebutton = new QPushButton;
    inputstudentscorebutton->setText("学生成绩:");
    inputstudentscorebuttonLineEdit = new QLineEdit("90");

    // ==================== 布局摆放 ====================
    // addWidget(控件, 行, 列)
    glayout->addWidget(inputstudentnobutton,          0, 0);
    glayout->addWidget(inputstudentnobuttonLineEdit,  0, 1);
    glayout->addWidget(inputstudentnamebutton,        1, 0);
    glayout->addWidget(inputstudentnamebuttonLineEdit,1, 1);
    glayout->addWidget(inputstudentsexbutton,         2, 0);
    glayout->addWidget(inputstudentsexbuttonLineEdit, 2, 1);
    glayout->addWidget(inputstudentscorebutton,       3, 0);
    glayout->addWidget(inputstudentscorebuttonLineEdit,3, 1);

    // ==================== 信号槽连接 ====================
    // 只有学号和性别按钮能点击
    connect(inputstudentnobutton, SIGNAL(clicked()), this, SLOT(modifyno()));
    connect(inputstudentsexbutton, SIGNAL(clicked()), this, SLOT(modifysex()));
}

Dialog::~Dialog() = default;

// ==================== 修改学号 ====================
void Dialog::modifyno()
{
    bool isbool;   // 用来接收"用户是否点了确定"

    // 弹出文本输入对话框
    // getText(父窗口, 标题, 提示文字, 回显模式, 初始文本, &ok)
    QString strText = QInputDialog::getText(
        this,                                    // 父窗口
        "标准输入对话框",                       // 标题
        "请输入学号:",                          // 提示文字
        QLineEdit::Normal,                       // 回显模式（普通）
        inputstudentnobuttonLineEdit->text(),    // 初始文本 = 当前输入框内容
        &isbool                                  // 输出：用户是否确定
        );

    // 用户确定 + 输入非空 → 才更新
    if (isbool && !strText.isEmpty()) {
        inputstudentnobuttonLineEdit->setText(strText);
    }
}

// ==================== 修改性别 ====================
void Dialog::modifysex()
{
    // 准备下拉选项
    QStringList strSexItems;
    strSexItems << "男" << "女";

    bool isbool;

    // 弹出下拉选择对话框
    // getItem(父窗口, 标题, 提示文字, 选项列表, 默认索引, 是否可编辑, &ok)
    QString strsexItem = QInputDialog::getItem(
        this,              // 父窗口
        "标准输入对话框",   // 标题
        "请选择性别:",      // 提示文字
        strSexItems,        // 下拉选项
        0,                  // 默认选中第 0 项（"男"）
        false,              // 不允许编辑（只能选）
        &isbool             // 输出：用户是否确定
        );

    // 用户确定 + 选项非空 → 才更新
    if (isbool && !strsexItem.isEmpty()) {
        inputstudentsexbuttonLineEdit->setText(strsexItem);
    }
}