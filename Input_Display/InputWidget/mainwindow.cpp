#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>         // 消息对话框
#include <QDir>                // 目录操作
#include <QTextStream>         // 文本流，用于读文件
#include <QCoreApplication>    // 应用程序核心，取程序路径
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setGeometry(300,200,1000,600);        // 窗口位置和大小
    combobox=new QComboBox(this);               //下拉框
    combobox->setGeometry(10,10,200,30);        // 位置(10,10)，大小200x30
    combobox->addItem("北京市");
    combobox->addItem("上海市");
    combobox->addItem("重庆市");
    combobox->addItem("天津市");
    combobox->addItem("香港");
    combobox->addItem("澳门");
    combobox->addItem("台湾");
    connect(combobox,SIGNAL(currentIndexChanged(int)),this,SLOT(comboboxIndex(int)));

    fontcombobox=new QFontComboBox(this);  // 字体选择框
    qlabels=new QLabel(this);              // 文字标签
    fontcombobox->setGeometry(10,50,200,30);
    qlabels->setGeometry(10,90,300,50);
    connect(fontcombobox,SIGNAL(currentFontChanged(QFont)),this,SLOT(fontcomboboxFunc(QFont)));

    lineedit=new QLineEdit(this);          // 单行输入框
    lineedit->setGeometry(10,150,200,30);
    pushbutton=new QPushButton(this);      // 按钮
    pushbutton->setGeometry(220,150,100,30);
    pushbutton->setText("点击我");          // 按钮文字
    qlabely=new QLabel(this);              // 显示结果的标签
    qlabely->setGeometry(10,200,400,30);
    qlabely->setText("你输入的内容为:");
    connect(pushbutton,SIGNAL(clicked()),this,SLOT(pushbuttonclicked()));

    plainedit=new QPlainTextEdit(this);
    plainedit->setGeometry(10,250,400,200);
    radiobutton=new QRadioButton(this);
    radiobutton->setGeometry(300,220,200,30);
    radiobutton->setText("只读模式");
    QDir::setCurrent(QCoreApplication::applicationDirPath());  // 把当前目录设为程序所在目录
    QFile fe("moc_mainwindow.cpp");        // Qt 的 moc（元对象编译器）自动生成的文件，里面包含 Q_OBJECT 宏展开的代码。程序运行时用 QDir::setCurrent 把工作目录切到 exe 所在目录，才能找到它。
    fe.open(QFile::ReadOnly|QFile::Text);  // 只读+文本方式打开
    QTextStream strin(&fe);                // 绑定文本流
    plainedit->insertPlainText(strin.readAll());  // 全部读出，插入文本框
    connect(radiobutton,SIGNAL(clicked()),this,SLOT(radiobuttonclicked()));

    this->setStyleSheet("QMainWindow{background-color:""rgba(100,200,100,100%)}");
    spinbox=new QSpinBox(this);
    spinbox->setGeometry(440,250,150,30);
    spinbox->setRange(0,100);              // 范围 0~100
    spinbox->setSingleStep(10);            // 每次加减10
    spinbox->setValue(100);                // 初始值100
    spinbox->setSuffix("%不透明度");        // 后缀文字
    connect(spinbox,SIGNAL(valueChanged(int)),this,SLOT(spinboxValueChanged(int)));
    // connect(spinbox,&QSpinBox::valueChanged,this,&MainWindow::spinboxValueChanged);

    dte=new QDateTimeEdit(QDateTime::currentDateTime(),this);  // 日期+时间，初始为当前时间
    dte->setGeometry(440,290,200,30);
    te=new QTimeEdit(QTime::currentTime(),this);               // 时间，初始为当前时间
    te->setGeometry(440,330,200,30);
    de=new QDateEdit(QDate::currentDate(),this);               // 日期，初始为当前日期
    de->setGeometry(440,370,200,30);

    hscrollbar=new QScrollBar(Qt::Horizontal,this);  // 水平滚动条
    hscrollbar->setGeometry(0,500,1000,30);
    vscrollbar=new QScrollBar(Qt::Vertical,this);    // 垂直滚动条
    vscrollbar->setGeometry(970,0,30,500);

    kse=new QKeySequenceEdit(this);
    kse->setGeometry(400,530,200,30);
    connect(kse,SIGNAL(keySequenceChanged(const QKeySequence &)),
            this,SLOT(keyseqeditChanged(const QKeySequence &)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::comboboxIndex(int index){
    qDebug()<<"你选择的区别是"<<combobox->itemText(index);  // 控制台输出调试信息
    QMessageBox mybox(QMessageBox::Question,"信息",combobox->itemText(index),
                      QMessageBox::Yes|QMessageBox::No);     // 创建问答对话框
    mybox.exec();                                            // 显示对话框（阻塞）
}
void MainWindow::fontcomboboxFunc(QFont font){
    qlabels->setFont(font);      // 把标签字体设为选中的字体
    QString qStr="ABCBA";
    qlabels->setText(qStr);      // 标签显示 "ABCBA"
}
void MainWindow::pushbuttonclicked(){
    QString qStr;
    qStr="你输入的内容为:"+lineedit->text();  // 拼接字符串
    qlabely->setText(qStr);                   // 显示到标签
    lineedit->clear();                        // 清空输入框
}
void MainWindow::radiobuttonclicked(){
    if(radiobutton->isChecked()){        // 如果被选中
        plainedit->setReadOnly(true);    // 文本框设为只读
    }else{
        plainedit->setReadOnly(false);   // 否则可编辑
    }
}
void MainWindow::spinboxValueChanged(int x){
    double dx=(double)x/100;         // 转成 0.0~1.0
    this->setWindowOpacity(dx);      // 设置窗口透明度
}
void MainWindow::keyseqeditChanged(const QKeySequence &key){
    if(key==QKeySequence(tr("Ctrl+Q"))){   // 如果录的是 Ctrl+Q
        this->close();                      // 关闭窗口
    }else{
        qDebug()<<key.toString();          // 否则打印出来
    }
}






















