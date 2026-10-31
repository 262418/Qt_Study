#include "mainwindow.h"
#include <QApplication>

// ==================== 主函数 ====================
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // ---------- 1. 创建饼图序列对象 ----------
    // QPieSeries 表示整个饼图
    QPieSeries *sris = new QPieSeries();

    // ---------- 2. 添加数据（比例） ----------
    // append("标签文字", 数值)
    // 数值会自动被计算成百分比比例
    sris->append("70分以下：30%", 30);
    sris->append("70分-85分：20%", 40);
    sris->append("86分-99分：25%", 25);
    sris->append("100分：5%", 5);

    // ---------- 3. 设置标签可见 ----------
    // 让饼图旁边显示文字标签
    sris->setLabelsVisible(true);   // 括号里要传 true，不传会报错

    // ---------- 4. 获取各个扇区（切片） ----------
    // slices() 返回所有扇区的列表，at(0) 取第一个
    QPieSlice *sred   = sris->slices().at(0);
    QPieSlice *sgreen = sris->slices().at(1);
    QPieSlice *sblue  = sris->slices().at(2);
    QPieSlice *sblack = sris->slices().at(3);

    // ---------- 5. 设置每个扇区的颜色 ----------
    // QColor(R, G, B, A) —— R/G/B 是红绿蓝，A 是透明度
    sred->setColor(QColor(255, 0, 0, 255));     // 红色
    sgreen->setColor(QColor(0, 255, 0, 255));   // 绿色
    sblue->setColor(QColor(0, 0, 255, 255));    // 蓝色
    sblack->setColor(QColor(0, 0, 0, 255));     // 黑色

    // ---------- 6. 创建图表并添加序列 ----------
    QChart *chart = new QChart();
    chart->addSeries(sris);
    chart->setTitle("饼图形状--班级考试百分制整数比例");

    // ---------- 7. 创建图表视图 ----------
    QChartView *chartview = new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);   // 建议加抗锯齿

    // ---------- 8. 显示到主窗口 ----------
    MainWindow w;
    w.setCentralWidget(chartview);
    w.resize(600, 600);
    w.show();

    return a.exec();
}