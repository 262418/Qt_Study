#include "widget.h"
#include "ui_widget.h"

// ==================== 构造函数 ====================
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    // 1. 创建样条曲线对象
    //    QSplineSeries 会自动把数据点连成平滑的曲线（不像 QLineSeries 是折线）
    QSplineSeries *s1 = new QSplineSeries();

    // 2. 往曲线里添加数据点 (x, y)
    s1->append(0, 5);
    s1->append(1, 3);
    s1->append(2, 5);
    s1->append(3, 9);
    s1->append(4, 6);
    s1->append(5, 16);
    s1->append(6, 10);
    s1->append(7, 12);
    s1->append(8, 17);
    s1->append(9, 19);

    // 3. 获取界面上已有的图表对象
    QChart *ct = ui->chartview->chart();

    // 4. 隐藏图例（图表旁边的比例说明）
    ct->legend()->hide();

    // 5. 把曲线加到图表里
    ct->addSeries(s1);

    // 6. 设置图表标题
    ct->setTitle("曲线图表标题--自定义");

    // 7. 根据已有数据自动创建默认的 X 轴和 Y 轴
    //    （会自动根据数据范围调整）
    ct->createDefaultAxes();

    // 8. 手动设置 Y 轴范围
    //    axes(Qt::Vertical) 获取垂直轴列表，.first() 取第一个（Y轴）
    ct->axes(Qt::Vertical).first()->setRange(0, 20);
}
// ==================== 析构函数 ====================
Widget::~Widget()
{
    delete ui;
}