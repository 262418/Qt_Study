#include "mainwindow.h"
#include <QApplication>
// ==================== 主函数 ====================
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // ---------- 1. 创建数据集 ----------
    // QBarSet 代表一组柱子（同一颜色的数据）
    QBarSet *ba = new QBarSet("bar");   // 图例名称叫 "bar"

    // 使用 << 运算符往数据集中依次添加 5 个数值
    *ba << 560 << 710 << 599 << 688 << 701;

    // ---------- 2. 创建柱状图序列 ----------
    // QStackedBarSeries 表示“堆叠柱状图”（多组数据叠在一起）
    // 如果想并排显示，用 QBarSeries；如果想横向，用 QHorizontalBarSeries
    QStackedBarSeries *sris = new QStackedBarSeries();
    sris->append(ba);   // 把数据集加进序列里

    // ---------- 3. 创建图表并添加序列 ----------
    QChart *chart = new QChart();
    chart->addSeries(sris);
    chart->setTitle("某某学校实验班高考成绩分数");

    // ---------- 4. 创建 X 轴（分类轴） ----------
    // QBarCategoryAxis 用于显示文字类别（如人名、月份）
    QStringList strlist = {"小王", "小李", "小吴", "小张", "小赵"};

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(strlist);             // 添加 5 个分类
    axisX->setTitleText("考生姓名");

    // 把 X 轴加到图表里，并放在底部
    chart->addAxis(axisX, Qt::AlignBottom);

    // ---------- 5. 创建 Y 轴（数值轴） ----------
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 750);            // 高考总分 750
    axisY->setTitleText("高考总分阶梯");

    // 把 Y 轴加到图表里，并放在左侧
    chart->addAxis(axisY, Qt::AlignLeft);

    // ---------- 6. 把坐标轴绑定到数据序列上 ----------
    // 非常重要！不加这两句，坐标轴不会显示刻度
    sris->attachAxis(axisX);
    sris->attachAxis(axisY);

    // ---------- 7. 图例设置 ----------
    chart->legend()->setVisible(false);          // 隐藏图例（这个程序不需要）
    chart->legend()->setAlignment(Qt::AlignBottom); // 把图例放到下方（但上面已隐藏，这句实际不起作用）

    // ---------- 8. 创建图表视图 ----------
    QChartView *chartview = new QChartView(chart);

    // ---------- 9. 显示到主窗口 ----------
    MainWindow w;
    w.setWindowTitle("高考成绩--柱状图表展示");
    w.setCentralWidget(chartview);      // 把图表视图放进窗口
    w.resize(800, 500);
    w.show();

    return a.exec();
}