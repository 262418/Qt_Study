#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCharts>   // Qt 图表模块

// ==================== 构造函数 ====================
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 1. 创建图表视图对象
    //    QChartView 是一个 Widget，负责把图表显示出来
    QChartView *chartview = new QChartView(this);

    // 创建图表对象（数据、坐标轴、标题都在这里）
    QChart *chart = new QChart();
    chart->setTitle("图表测试--正弦余弦曲线程序");

    // 2. 将图表添加到图表视图
    chartview->setChart(chart);

    // 3. 将图表视图展示到窗口中间
    //    因为 MainWindow 是主窗口，setCentralWidget 会让视图铺满中间
    this->setCentralWidget(chartview);

    // 4. 创建曲线（折线序列）
    //    QLineSeries 用来画折线图/曲线图
    QLineSeries *s1 = new QLineSeries();
    QLineSeries *s2 = new QLineSeries();

    s1->setName("正弦曲线");   // 图例中的名字
    s2->setName("余弦曲线");

    // 5. 将创建的曲线添加到图表
    chart->addSeries(s1);
    chart->addSeries(s2);

    // 6. 为曲线序列添加对应的数值
    qreal t = 0, y1, y2, iv = 0.1;   // t 是 X 轴，iv 是步长
    int cnt = 100;                   // 总点数

    for (int i = 0; i < cnt; i++)
    {
        y1 = qSin(t);        // 计算正弦值
        s1->append(t, y1);   // 追加点到正弦曲线

        y2 = qCos(t );       // 计算余弦值（严格来说这里写的是 sin(t+20)，不是 cos）
        s2->append(t, y2);   // 追加点到余弦曲线

        t = t + iv;          // X 轴每次增加 0.1
    }

    // 7. 创建坐标轴
    QValueAxis *ax = new QValueAxis;   // X 轴
    ax->setRange(0, 10);               // 设置 X 轴范围 0~10
    ax->setTitleText("times(secs)");   // X 轴标题

    QValueAxis *ay = new QValueAxis;   // Y 轴
    ay->setRange(-2, 2);               // 设置 Y 轴范围 -2~2
    ay->setTitleText("values");        // Y 轴标题

    // 8. 将坐标轴附加到曲线上
    chart->setAxisX(ax, s1);
    chart->setAxisY(ay, s1);

    chart->setAxisX(ax, s2);
    chart->setAxisY(ay, s2);
}

// ==================== 析构函数 ====================
MainWindow::~MainWindow()
{
    delete ui;
}