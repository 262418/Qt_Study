#include "dialog.h"
#include <QGridLayout>             // 网格布局管理器
const static double PI = 3.1415;   // 定义圆周率常量
// 构造函数：初始化界面
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)              // 调用基类构造函数
{
    // ---------- 创建控件 ----------
    // 创建第一个标签（提示用户输入球的半径）
    lab1 = new QLabel(this);       // this 表示父对象是 Dialog，自动管理内存
    lab1->setText(tr("请输入球的半径"));
    // tr() 是 Qt 的国际化函数，用于翻译字符串

    // 创建第二个标签（显示结果）
    lab2 = new QLabel(this);

    // 创建编辑框接收用户输入的半径
    lEdit = new QLineEdit(this);

    // 创建按钮
    pbt = new QPushButton(this);
    pbt->setText(tr("计算圆球的体积"));

    // ---------- 布局管理 ----------
    // 创建网格布局，父对象是 this，自动成为 Dialog 的布局
    QGridLayout *mLay = new QGridLayout(this);
    mLay->addWidget(lab1, 0, 0);   // 第 0 行第 0 列：提示标签
    mLay->addWidget(lEdit, 0, 1);  // 第 0 行第 1 列：输入框
    mLay->addWidget(lab2, 1, 0);   // 第 1 行第 0 列：结果标签
    mLay->addWidget(pbt, 1, 1);    // 第 1 行第 1 列：按钮

    // ---------- 信号槽连接 ----------
    // 当输入框文本改变时，自动调用 CalcBallVolume()
    // 旧式语法 SIGNAL/SLOT（Qt4 风格），现在推荐用新式语法（见下方说明）
    connect(lEdit, SIGNAL(textChanged(QString)),
            this,  SLOT(CalcBallVolume()));
    /*connect(pbt, &QPushButton::clicked,
            this,  &Dialog::CalcBallVolume);*/
}

Dialog::~Dialog() = default;       // 析构函数用默认实现
// 子控件都是 new 出来的，父对象 this 销毁时会自动 delete

// 计算球体积的槽函数
void Dialog::CalcBallVolume()
{
    bool isLoop;                   // 用于判断转换是否成功（名字应为 ok，此处沿用原代码）
    QString tempstr;               // 临时字符串
    QString valuestr = lEdit->text();   // 获取输入框内容

    // 把字符串转成整数；isLoop 会被设为 true/false 表示成功与否
    int valueInt = valuestr.toInt(&isLoop);

    // 计算球体积公式：V = 4/3 * π * r³
    // 4.0/3.0 用浮点除法，避免整数除法变成 1
    double volume = 4.0 / 3.0 * PI * valueInt * valueInt * valueInt;

    // 把结果显示到 lab2 上
    // setNum(double) 会把数字转成字符串并返回引用
    lab2->setText(tempstr.setNum(volume));
}