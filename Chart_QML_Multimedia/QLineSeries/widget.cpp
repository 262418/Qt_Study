#include "widget.h"
#include "ui_widget.h"

// ==================== 构造函数 ====================
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 调用自己写的函数来画图
    myselfLineSeriesFunc();
}

// ==================== 析构函数 ====================
Widget::~Widget()
{
    delete ui;
}

// ==================== 绘制折线图的核心逻辑 ====================
void Widget::myselfLineSeriesFunc()
{
    // ---------- 1. 实例化图表 QChart 对象 ----------
    QChart *chart = new QChart();
    chart->setTitle("全球各国军费增长折线图");   // 设置标题

    // 把图表交给界面上的视图显示
    ui->graphicsView->setChart(chart);

    // ---------- 2. 设置 X 轴 ----------
    QValueAxis *axisX = new QValueAxis();
    axisX->setTitleText("年份");        // X 轴标题
    axisX->setRange(2017, 2021);        // X 轴范围：2017年~2021年
    axisX->setLineVisible(true);        // 显示轴线
    axisX->setGridLineVisible(false);   // 隐藏网格线（背景的竖线）

    // ---------- 3. 设置 Y 轴 ----------
    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("军费（万亿:美元）"); // Y 轴标题
    axisY->setRange(2000, 10000);           // Y 轴范围：2000~10000
    axisY->setTickCount(5);                 // Y 轴分成 5 个刻度
    axisY->setLineVisible(true);            // 显示轴线
    axisY->setGridLineVisible(false);       // 隐藏网格线（背景的横线）

    // ---------- 4. 绘制折线图（序列1：中国） ----------
    QLineSeries *sris1 = new QLineSeries;
    sris1->setName("中国");                     // 图例名字
    sris1->setColor(QColor(255, 0, 0));         // 红色

    // 添加数据点 (年份, 金额)
    sris1->append(2017, 5000);
    sris1->append(2018, 6500);
    sris1->append(2019, 4900);
    sris1->append(2020, 8000);
    sris1->append(2021, 9000);

    // ---------- 5. 绘制折线图（序列2：美国） ----------
    QLineSeries *sris2 = new QLineSeries;
    sris2->setName("美国");
    sris2->setColor(QColor(0, 255, 0));         // 绿色

    sris2->append(2017, 6500);
    sris2->append(2018, 7000);
    sris2->append(2019, 6900);
    sris2->append(2020, 9000);
    sris2->append(2021, 9800);

    // ---------- 6. 绘制折线图（序列3：俄罗斯） ----------
    QLineSeries *sris3 = new QLineSeries;
    sris3->setName("俄罗斯");
    sris3->setColor(QColor(0, 0, 255));         // 蓝色

    sris3->append(2017, 4000);
    sris3->append(2018, 8000);
    sris3->append(2019, 7900);
    sris3->append(2020, 10000);
    sris3->append(2021, 9500);

    // ---------- 7. 把 3 条折线加到图表中 ----------
    chart->addSeries(sris1);
    chart->addSeries(sris2);
    chart->addSeries(sris3);

    // ---------- 8. 将坐标轴绑定到序列上 ----------
    // 注意：这里 3 条线共用同一个 X 轴和 Y 轴
    // 1. 先把坐标轴加到图表中（指定位置：底部和左侧）
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    // 2. 然后把坐标轴附加（attach）到每一条折线上
    // sris1 附加坐标轴
    sris1->attachAxis(axisX);
    sris1->attachAxis(axisY);

    // sris2 附加坐标轴
    sris2->attachAxis(axisX);
    sris2->attachAxis(axisY);

    // sris3 附加坐标轴
    sris3->attachAxis(axisX);
    sris3->attachAxis(axisY);
}